#include <stdbool.h>  //C里面没有原生的bool, 用这个头文件里的宏定义代替
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//读取整个文件
unsigned char *getFullFileData(char *filePath, int *length) {
    FILE *file;
    unsigned char *data;

    //以 二进制读-拓展 方式打开
    file = fopen(filePath, "rb+");
    if (file == NULL) {  //没有打开文件
        printf("Failed to Open File: %s", filePath);
        return NULL;
    }

    // fseek定位到文件末尾-ftell获得文件长度-rewind回到开头
    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    data = (unsigned char *)malloc((*length + 1) *
                                   sizeof(char));  //分配内存保存数据
    rewind(file);
    *length = fread(data, 1, *length, file);
    data[*length] = '\0';  //加入末尾的结束符
    fclose(file);
    return data;
}

//检查前三个字节是否重复
bool checkRepetition(unsigned char *inStr, int remain) {
    if (remain < 2)
        return false;
    else {
        if (inStr[0] == inStr[1] && inStr[0] == inStr[2])
            return true;
        else
            return false;
    }
}

//获得无重复序列
int getNonRepetitiveSeq(unsigned char *inStr, int remain) {
    if (remain <= 2)
        return remain + 1;
    else {
        int cnt = 0, restCnt = remain;
        unsigned char *currStrPos = inStr;
        while (!checkRepetition(currStrPos, restCnt)) {
            currStrPos++;
            restCnt--;
            cnt++;
            if (cnt >= 128) return cnt;
            if (restCnt == 0) return cnt + 1;
        }
        return cnt;
    }
}

//增强的RLE压缩算法 - 压缩部分
//和标准RLE区别在于,对于每一个length-data块,我们把length的最高位作为标志位
//如果标志位为1,则说明这个data重复X次(X = length & 255, 即最高位置零)
//写入时按照length = (X - 1) | 128, data不变的格式(length最高位置一,
//后七位表示(重复次数-1), 因为data自己就是一次)
//如果标志位为零,则说明接下来的length个字节各不重复
int enhancedCompress(char *inPath, char *outPath) {
    //获得文件长度, 分配内存作为缓冲区
    int inFileLength = 0;
    unsigned char *inData = getFullFileData(
        inPath, &inFileLength);  //输入数据, 也是"当前处理的位置"
    unsigned char *outBuf =
        (unsigned char *)malloc((inFileLength * 1.2) * sizeof(unsigned char));
    unsigned char *outBufPos = outBuf;

    //剩余未处理的长度, 输出缓冲区剩余长度(计算写入输出文件的大小)
    int remain = inFileLength - 1;
    int outRemain = inFileLength * 1.2;
    int byteCnt = -1;           //重复字节计数
    int seqLenReachedFlag = 0;  //达到重复上限标志
    while (remain >= 0) {
        seqLenReachedFlag = 0;
        byteCnt = -1;
        if (checkRepetition(inData, remain)) {  //检查重复
            while (remain >= 0) {
                if (byteCnt == 127) break;  //达到重复上限制

                if (*inData == *(inData + 1)) {  //重复
                    remain--;                    //剩余长度-1
                    byteCnt++;                   //重复计数+1
                    inData++;  //输入数据向后移动一个字节
                } else {
                    byteCnt++;
                    if (byteCnt == 127) {
                        seqLenReachedFlag = 1;
                    }
                    break;
                }
            }

            if (outRemain < 2) return -1;  //输出缓冲区不足, 返回-1
            *outBuf = byteCnt | 128;       //最高位置一
            outBuf++;                      //输出缓冲区指针向下移
            *outBuf = *inData;             //直接写入当前字节
            outBuf++;                      //再下移
            outRemain -= 2;                //输出缓冲区剩余长度-2

            if (byteCnt != 127 || seqLenReachedFlag == 1) {
                inData++;
                remain--;
            }

        } else {
            if (checkRepetition(inData, remain)) continue;
            int num =
                getNonRepetitiveSeq(inData, remain);  //获得一个无重复序列的长度

            if (outRemain < (num + 1)) return -1;  //输出缓冲区不足, 返回-1
            *outBuf = num - 1;  //写入无重复序列的长度(第二种情况)
            outBuf++;           //下移
            for (int i = 0; i < num; i++) {  //写入无重复序列
                *outBuf = *(inData + i);
                outBuf++;
            }
            inData += num;         //数据指针下移
            remain -= num;         //剩余长度减少
            outRemain -= num + 1;  //可用输出缓冲区长度减少
        }
    }

    //打开文件
    FILE *outFile = fopen(outPath, "wb+");

    //判断是否打开
    if (outFile == NULL) {
        printf("Failed to Open Output File: %s", outPath);
        exit(-3);
    }

    //写入并关闭文件
    fwrite(outBufPos, 1, (inFileLength * 1.2) - outRemain, outFile);
    fclose(outFile);
    return 0;
}

//增强的RLE压缩算法 - 解压部分
//和上面的增强RLE算法 - 压缩部分反过来
//对于每一个length - data块, 检查length最高位是不是1
//如果是,将后面的字节重复(X+1)次
//如果不是,将后面X个字节直接写到输出中
//重复点不再赘述
int enhancedDecompress(char *inPath, char *outPath) {
    int inFileLength = 0;
    unsigned char *inData = getFullFileData(inPath, &inFileLength);
    unsigned char *outBuf =
        (unsigned char *)malloc((inFileLength * 1.2) * sizeof(unsigned char));
    unsigned char *outBufPos = outBuf;
    unsigned char temp;  //临时字符,一般是重复的那个字节
    int outRemain = inFileLength * 1.2;
    int inRemain = inFileLength;
    int byteChecker;

    while (inRemain >= 0) {
        byteChecker = *inData + 1;
        if (byteChecker > 129) {  //最高位为一
            if ((outRemain - byteChecker + 128) < 0)
                return -1;  //缓冲区长度不足
            temp = *(inData + 1);
            for (int i = 0; i < byteChecker - 128; i++) {  //写入重复字节
                *outBuf = temp;
                outBuf++;
            }
            inData += 2;
            inRemain -= 2;
            outRemain -= byteChecker - 128;

        } else {
            if ((outRemain - byteChecker) < 0) return -1;
            inData++;
            for (int i = 0; i < byteChecker; i++) {
                *outBuf = *inData;
                outBuf++;
                inData++;
            }
            inRemain -= 1 + byteChecker;
            outRemain -= byteChecker;
        }
    }

    FILE *outFile = fopen(outPath, "wb+");

    //判断是否打开
    if (outFile == NULL) {
        printf("Failed to Open Output File: %s", outPath);
        exit(-3);
    }

    fwrite(outBufPos, 1, (inFileLength * 1.2) - outRemain, outFile);
    fclose(outFile);

    return 0;
}

//以标准RLE算法压缩
//和stdDecompress()的相同之处将不再注释
int stdCompress(char *stcPath, char *destPath) {
    FILE *srcFile, *destFile;  //源文件, 目标文件
    unsigned char currChar, seqChar;  //当前字节, 顺序上的字节(也就是前面的字节)
    int seqLen;                       //重复的长度

    //以 读二进制 方式打开文件, 并判断是否失败
    if ((srcFile = fopen(stcPath, "rb")) == NULL) {
        printf("Failed to Open Source File: %s.", stcPath);
        return -1;
    }

    //以 读写二进制 方式打开文件, 并判断是否失败
    if ((destFile = fopen(destPath, "wb+")) == NULL) {
        printf("Failed to Open Destination File: %s.", destPath);
        return -1;
    }

    //初始化各个字符的值
    currChar = fgetc(srcFile);
    seqChar = currChar;
    seqLen = 1;

    while (feof(srcFile) == 0) {  //到达文件末尾之前
        currChar = fgetc(srcFile);
        if (currChar == seqChar) {  //重复
            seqLen++;
        } else {  //不重复, 写入长度和顺序字节
            fputc(seqLen, destFile);
            fputc(seqChar, destFile);

            seqChar = currChar;  //复位
            seqLen = 1;
        }
    }

    /*
     * 2020-05-31 更新
     * 不知道为什么bmp文件的最后一个FF字节会丢失,而txt等文件不会
     * 经测试,已排除与文件长度的奇偶性的关系
     * 猜想可能是由于 0xFF == -1, 导致文件提前结束
     * (但是feof()并不依靠这个) ,因此目前暂时原因未知
     * 一个workaround是检测两个文件的最后一个字节是否一样
     * 如果不一样则在destFile末尾写入 01 [srcFile最后一个字节]
     * */

    //定位到最后一个字节
    fseek(srcFile, -1L, SEEK_END);
    fseek(destFile, -1L, SEEK_END);

    //获得最后一个字节
    unsigned char srcLastChar = fgetc(srcFile), destLastChar = fgetc(destFile);
    fclose(destFile);
    fopen(destPath, "ab+");  //按照 二进制-追加 方式打开destFile

    if (srcLastChar != destLastChar) {  //如果不等
        fputc((char)1, destFile);       //写入 01 [srcFile最后一个字节]
        fputc(srcLastChar, destFile);
    }

    //关闭文件
    fclose(srcFile);
    fclose(destFile);
    return 0;
}

//以标准RLE算法解压缩
//和stdCompress()的相同之处将不再注释, 请参见上面的stdCompress()
int stdDecompress(char *srcPath, char *destPath) {
    FILE *srcFile, *destFile;
    unsigned char currChar;
    int seqLen;

    if ((srcFile = fopen(srcPath, "rb")) == NULL) {
        printf("Failed to Open Source File: %s.", srcPath);
        return -1;
    }
    if ((destFile = fopen(destPath, "wb")) == NULL) {
        printf("Failed to Open Destination File: %s.", destPath);
        return -1;
    }

    while (feof(srcFile) == 0) {
        seqLen = fgetc(srcFile);
        currChar = fgetc(srcFile);
        for (int i = 0; i < seqLen; i++) {
            fputc(currChar, destFile);
        }
    }

    fclose(srcFile);
    fclose(destFile);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {  //参数过少
        printf("Missing Necessary Arguments\nUsage: ");
        printf("rle_enhanced File1 -c/-d File2 [options]\nArguments:\n");
        printf("  -c       Compress File\n");
        printf("  -d       Decompress File\n");
        printf("  File1    Source File\n");
        printf("  File2    Destination File\n");
        printf("Options(-s is DEFAULT):\n");
        printf("  -s       [DEFAULT] Using Standard RLE Algorithm\n");
        printf("           (Recommend to Save as *.rle File)\n");
        printf("  -e       Using Enhanced RLE Algorithm\n");
        printf("           (Recommend to Save as *.erle File)\n");
        return -1;
    }

    if (strcmp(argv[2], "-c") == 0) {  //解压
        if (argc < 5 ||
            strcmp(argv[4], "-s") == 0) {  //未指定算法, 或指定标准RLE算法
            if (stdCompress(argv[1], argv[3]) != 0) {
                printf("Failed to Compress File via Standard RLE Algorithm");
                return -2;
            }
            printf("Successfully Compressed File via Standard RLE Algorithm");
            return 0;
        } else if (strcmp(argv[4], "-e") == 0) {  //指定增强RLE算法
            if (enhancedCompress(argv[1], argv[3]) != 0) {
                printf("Failed to Compress File via Enhanced RLE Algorithm");
                return -2;
            }
            printf("Successfully Compressed File via Enhanced RLE Algorithm");
            return 0;
        }
    } else if (strcmp(argv[2], "-d") == 0) {
        if (argc < 5 || strcmp(argv[4], "-s") == 0) {  //解压, 和上面一样
            if (stdDecompress(argv[1], argv[3]) != 0) {
                printf("Failed to Decompress File via Standard RLE Algorithm");
                return -2;
            }
            printf("Successfully Decompressed File via Standard RLE Algorithm");
            return 0;
        } else if (strcmp(argv[4], "-e") == 0) {
            if (enhancedDecompress(argv[1], argv[3]) != 0) {
                printf("Failed to Compress File via Enhanced RLE Algorithm");
                return -2;
            }
            printf("Successfully Compressed File via Enhanced RLE Algorithm");
            return 0;
        }
    } else {  //未识别的选项(非-c也非-d)
        printf("Unrecongized Argument at argv[2]: %s", argv[2]);
        return -1;
    }
    return 0;
}