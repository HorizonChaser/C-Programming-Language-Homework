#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//以标准RLE算法压缩
//和stdDecompress()的相同之处将不再注释
int stdCompress(char *stcPath, char *destPath) {
    FILE *srcFile, *destFile;//源文件, 目标文件
    unsigned char currChar, seqChar;//当前字节, 顺序上的字节(也就是前面的字节)
    int seqLen;//重复的长度

    //以 读二进制 方式打开文件, 并判断是否失败
    if ((srcFile = fopen(stcPath, "rb")) == NULL) {
        printf("Failed to Open Source File: %s\n", stcPath);
        return -1;
    }

    //以 读写二进制 方式打开文件, 并判断是否失败
    if ((destFile = fopen(destPath, "wb+")) == NULL) {
        printf("Failed to Open Destination File: %s\n", destPath);
        return -1;
    }

    //初始化各个字符的值
    currChar = fgetc(srcFile);
    seqChar = currChar;
    seqLen = 1;

    while (feof(srcFile) == 0) {//到达文件末尾之前
        currChar = fgetc(srcFile);
        if (currChar == seqChar) {//重复
            seqLen++;
        } else {//不重复, 写入长度和顺序字节
            fputc(seqLen, destFile);
            fputc(seqChar, destFile);

            seqChar = currChar;//复位
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
    fopen(destPath, "ab+");//按照 二进制-追加 方式打开destFile

    if (srcLastChar != destLastChar) {//如果不等
        fputc((char)1, destFile);//写入 01 [srcFile最后一个字节]
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
        printf("Failed to Open Source File: %s\n", srcPath);
        return -1;
    }
    if ((destFile = fopen(destPath, "wb")) == NULL) {
        printf("Failed to Open Destination File: %s\n", destPath);
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
    if (argc < 4) {//参数过少
        printf("Missing Necessary Arguments\nUsage: ");
        printf("rle File1 -c/-d File2\nArguments:\n");
        printf("  -c       Compress File by Standard RLE Algorithm\n");
        printf("  -d       Decompress File by Standard RLE Algorithm\n");
        printf("  File1    Source File\n");
        printf("  File2    Destination File");
        return -1;
    }

    if (strcmp(argv[2], "-c") == 0) {
        if (stdCompress(argv[1], argv[3]) != 0) {
            printf("Failed to Compress File");
            return -2;
        }
        printf("Successfully Compressed File");
        return 0;
    } else if (strcmp(argv[2], "-d") == 0) {
        if (stdDecompress(argv[1], argv[3]) != 0) {
            printf("Failed to Decompress File");
            return -2;
        }
        printf("Successfully Decompressed File");
        return 0;
    } else {//未识别的选项(非-c也非-d)
        printf("Unrecongized Argument at argv[2]: %s", argv[2]);
        return -1;
    }

    return 0;
}