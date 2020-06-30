#include "cmdline.h" //Command Line Praser(命令行解析器)
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>

using namespace std;

unsigned char *pBmpBuf; //读入图像数据的指针
int bmpWidth;           //图像的宽
int bmpHeight;          //图像的高
RGBQUAD *pColorTable;   //调色板指针
int biBitCount;         //每像素位数，比如RGB32就是32位(RGBA), RGB24就是24位(RGB)

//输出文件头
void showBmpHead(BITMAPFILEHEADER pBmpHead)
{
    cout << "\nBit Map File Header:" << endl;
    cout << "Size:" << pBmpHead.bfSize << endl;
    cout << "Reversed_1:" << pBmpHead.bfReserved1 << endl;
    cout << "Reversed_2:" << pBmpHead.bfReserved2 << endl;
    cout << "Data Offset:" << pBmpHead.bfOffBits << endl
         << endl;
}

//输出信息头
void showBmpInfoHead(BITMAPINFOHEADER pBmpInforHead)
{
    cout << "\nBit Map Info Header:" << endl;
    cout << "Struct Length:" << pBmpInforHead.biSize << endl;
    cout << "Width:" << pBmpInforHead.biWidth << endl;
    cout << "Height:" << pBmpInforHead.biHeight << endl;
    cout << "Planes:" << pBmpInforHead.biPlanes << endl;
    cout << "Bit Count:" << pBmpInforHead.biBitCount << endl;
    cout << "Compact Method:" << pBmpInforHead.biCompression << endl;
    cout << "Image Size(often 0):" << pBmpInforHead.biSizeImage << endl;
    cout << "X Direction PPM(often 0):" << pBmpInforHead.biXPelsPerMeter << endl;
    cout << "Y Direction PPM(often 0):" << pBmpInforHead.biYPelsPerMeter << endl;
    cout << "Colors Used(often 0):" << pBmpInforHead.biClrUsed << endl;
    cout << "Important Colors(often 0 for all colors):" << pBmpInforHead.biClrImportant << endl;
}

//加载一个BMP位图， 格式限定为RGB32，带Alpha通道
bool loadBmpFile(char *bmpName)
{
    FILE *fp = fopen(bmpName, "rb"); //二进制读
    if (fp == 0)
        return 0;

    //跳过BITMAPFILEHEADER
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);

    //定义BITMAPINFOHEADER, 并存放在infohead中
    BITMAPINFOHEADER infohead;
    fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);

    //获得长宽等信息
    bmpWidth = infohead.biWidth;
    bmpHeight = infohead.biHeight;
    biBitCount = infohead.biBitCount; //定义变量，计算图像每行像素所占的字节数（必须是4的倍数）

    int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4; //灰度图像有调色板，且调色板表项为256

    //申请空间
    pBmpBuf = new unsigned char[lineByte * bmpHeight];
    fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
    fclose(fp); //关闭文件
    return 0;   //读取成功
}

//保存图片
bool saveBmpFile(string bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{
    //如果位图指针为null，直接返回
    if (!imgBuf)
        return 0;

    //调色板大小，彩色图像调色板大小为0
    int colorTablesize = 0;

    //待存储图像数据，每行字节数必须为4的倍数
    int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

    //二进制写打开
    FILE *fp = fopen(bmpName.c_str(), "wb");

    //没成功打开，直接返回
    if (fp == 0)
        return 0;

    //创建BITMAPFILEHEADER并填充
    BITMAPFILEHEADER fileHead;
    fileHead.bfType = 0x4D42; //bmp类型Magic Number
    //bfSize是4个部分之和
    fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;
    fileHead.bfReserved1 = 0;
    fileHead.bfReserved2 = 0;
    //bfOffBits是前3个部分空间之和
    fileHead.bfOffBits = 54 + colorTablesize;
    //写文件头
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

    //创建BITMAPINFOHEADER并填充
    BITMAPINFOHEADER infohead;
    infohead.biBitCount = biBitCount;
    infohead.biClrImportant = 0;
    infohead.biClrUsed = 0;
    infohead.biCompression = 0;
    infohead.biHeight = height;
    infohead.biPlanes = 1;
    infohead.biSize = 40;
    infohead.biSizeImage = lineByte * height;
    infohead.biWidth = width;
    infohead.biXPelsPerMeter = 0;
    infohead.biYPelsPerMeter = 0;

    //写位图信息头
    fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
    //写位图数据
    fwrite(imgBuf, height * lineByte, 1, fp);

    fclose(fp); //关闭文件
    return 0;   //成功输出到了文件
}

//最邻近插值
void nearestBmpScaling(char readPath[], char writePath[], double ScalSize)
{

    loadBmpFile(readPath);

    unsigned char *imagedata = NULL;     //原图片数据，二维数组
    unsigned char *imagedataScal = NULL; //缩放后数据，二维数组
    imagedata = pBmpBuf;

    int expectedWidth, expectedHeight;

    //对期缩放结果取整
    expectedWidth = (int)(ScalSize * bmpWidth);
    expectedHeight = (int)(ScalSize * bmpHeight);

    //每一行的字节数必须是4的整数倍
    int lineByte2 = (expectedWidth * biBitCount / 8 + 3) / 4 * 4;
    imagedataScal = new unsigned char[lineByte2 * expectedHeight]; //为缩放后图像分配内存

    int pre_i, pre_j, after_i, after_j; //缩放前后像素坐标，pre前，after后
    for (int i = 0; i < expectedHeight; i++)
    {
        for (int j = 0; j < expectedWidth; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                after_i = i;
                after_j = j;
                pre_i = (int)(after_i / ScalSize); //取整
                pre_j = (int)(after_j / ScalSize);
                if (pre_i >= 0 && pre_i < bmpHeight && pre_j >= 0 && pre_j < bmpWidth)                                  //在原图范围内
                    *(imagedataScal + i * lineByte2 + j * 4 + k) = *(imagedata + pre_i * bmpWidth * 4 + pre_j * 4 + k); //直接复制, 注意包含Alpha通道!!!
            }
        }
    }

    //保存bmp图片
    saveBmpFile(writePath, imagedataScal, expectedWidth, expectedHeight, biBitCount, pColorTable);

    //析构, 释放内存
    delete[] imagedata;
    delete[] imagedataScal;
}

//双线性插值
void bililinearBmpScaling(char readPath[], char writePath[], double ScalSize)
{

    //加载图片
    loadBmpFile(readPath);

    unsigned char *imagedata;     //原图片数据, 二维数组
    unsigned char *imagedataScal; //结果数据, 二维数组
    imagedata = pBmpBuf;

    int expectedWidth, expectedHeight; //期望大小

    //对期望的结果取整
    expectedWidth = (int)(ScalSize * bmpWidth);
    expectedHeight = (int)(ScalSize * bmpHeight);

    //每一行的字节数必须是4的整数倍
    int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
    int lineByte2 = (expectedWidth * biBitCount / 8 + 3) / 4 * 4;
    imagedataScal = new unsigned char[lineByte2 * expectedHeight]; //为结果分配内存

    //双线性插值, 参见 https://blog.csdn.net/weixin_40647819/article/details/86601070
    for (int i = 0; i < expectedHeight; i++)
        for (int j = 0; j < expectedWidth; j++)
        {

            float d_original_img_hnum = i / ScalSize;
            float d_original_img_wnum = j / ScalSize;
            int i_original_img_hnum = d_original_img_hnum;
            int i_original_img_wnum = d_original_img_wnum;
            float distance_to_a_x = d_original_img_wnum - i_original_img_wnum; //原图与a点水平距离
            float distance_to_a_y = d_original_img_hnum - i_original_img_hnum; //原图与a点垂直距离

            int original_point_a = i_original_img_hnum * lineByte + i_original_img_wnum * 4;             //数组下标的offset,相当于点A
            int original_point_b = i_original_img_hnum * lineByte + (i_original_img_wnum + 1) * 4;       //数组下标的offset,相当于点B
            int original_point_c = (i_original_img_hnum + 1) * lineByte + i_original_img_wnum * 4;       //数组下标的offset,相当于点C
            int original_point_d = (i_original_img_hnum + 1) * lineByte + (i_original_img_wnum + 1) * 4; //数组下标的offset,相当于点D

            if (i_original_img_hnum == bmpHeight - 1)
            {
                original_point_c = original_point_a;
                original_point_d = original_point_b;
            }
            if (i_original_img_wnum == bmpWidth - 1)
            {
                original_point_b = original_point_a;
                original_point_d = original_point_c;
            }

            int pixel_point = i * lineByte2 + j * 4; //缩放后结果数组的下标的offset
            for (int k = 0; k < 4; k++)
            {
                imagedataScal[pixel_point + k] =
                    imagedata[original_point_a + k] * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                    imagedata[original_point_b + k] * distance_to_a_x * (1 - distance_to_a_y) +
                    imagedata[original_point_c + k] * distance_to_a_y * (1 - distance_to_a_x) +
                    imagedata[original_point_d + k] * distance_to_a_y * distance_to_a_x;
            }
        }

    saveBmpFile(writePath, imagedataScal, expectedWidth, expectedHeight, biBitCount, pColorTable);

    //析构释放内存
    delete[] imagedata;
    delete[] imagedataScal;
}

int main(int argc, char *argv[])
{

    cmdline::parser cmd;
    cmd.add("showBMPInfo", 'i', "Show Header Info of the srcFile, it WILL NOT Resize BMPs Specified in Parameters");
    cmd.add<string>("srcFile", 's', "Path to the Source File", true);
    cmd.add<string>("destFile", 'd', "Path to the Destination File", false);
    cmd.add<double>("percentage", 'p', "Scale to Resize in Percentage", false);
    cmd.add<string>("algorithm", 'a', "Algorithm Used to Resize the BMP, bililinear or nearest", false, "bililinear", cmdline::oneof<string>("bililinear", "nearest"));

    cmd.parse_check(argc, argv);

    char srcPath[100], destPath[100];
    strcpy(srcPath, cmd.get<string>("srcFile").c_str());
    strcpy(destPath, cmd.get<string>("destFile").c_str());

    if (cmd.exist("showBMPInfo"))
    {
        loadBmpFile(srcPath);
        FILE *fp = fopen(srcPath, "rb"); //二进制读
        if (fp == 0)
            return 0;

        BITMAPINFOHEADER infohead;
        fseek(fp, sizeof(BITMAPFILEHEADER), 0);
        fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
        showBmpInfoHead(infohead);
        return 0;
    }

    if (cmd.exist("destFile") == false || cmd.exist("percentage") == false)
    {
        cout << "need option: --destFile --percentage" << endl;
        return 0;
    }

    //计时用
    long timer;
    if (cmd.get<string>("algorithm") == "bilinear")
    {
        timer = clock();
        bililinearBmpScaling(srcPath, destPath, cmd.get<double>("percentage") / 100.0);
    }
    else
    {
        timer = clock();
        nearestBmpScaling(srcPath, destPath, cmd.get<double>("percentage") / 100.0);
    }
    cout << "[INFO] Source BMP Successfully Resized to " << cmd.get<double>("percentage") << "% in " << int(((double)(clock() - timer)) / CLOCKS_PER_SEC * 1000) << "ms" << endl;
    return 0;
}