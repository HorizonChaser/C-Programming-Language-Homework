#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "cmdline.h"

using namespace std;

unsigned char *pBmpBuf; //读入图像数据的指针
int bmpWidth;           //图像的宽
int bmpHeight;          //图像的高
RGBQUAD *pColorTable;   //颜色表指针
int biBitCount;         //图像类型，每像素位数

//显示位图文件头信息
void showBmpHead(BITMAPFILEHEADER pBmpHead)
{
    cout << "\n位图文件头:" << endl;
    cout << "文件大小:" << pBmpHead.bfSize << endl;
    cout << "保留字_1:" << pBmpHead.bfReserved1 << endl;
    cout << "保留字_2:" << pBmpHead.bfReserved2 << endl;
    cout << "实际位图数据的偏移字节数:" << pBmpHead.bfOffBits << endl
         << endl;
}
//显示位图信息头信息
void showBmpInfoHead(BITMAPINFOHEADER pBmpInforHead)
{
    cout << "\n位图信息头:" << endl;
    cout << "结构体的长度:" << pBmpInforHead.biSize << endl;
    cout << "位图宽:" << pBmpInforHead.biWidth << endl;
    cout << "位图高:" << pBmpInforHead.biHeight << endl;
    cout << "biPlanes平面数:" << pBmpInforHead.biPlanes << endl;
    cout << "biBitCount采用颜色位数:" << pBmpInforHead.biBitCount << endl;
    cout << "压缩方式:" << pBmpInforHead.biCompression << endl;
    cout << "biSizeImage实际位图数据占用的字节数:" << pBmpInforHead.biSizeImage << endl;
    cout << "X方向分辨率:" << pBmpInforHead.biXPelsPerMeter << endl;
    cout << "Y方向分辨率:" << pBmpInforHead.biYPelsPerMeter << endl;
    cout << "使用的颜色数:" << pBmpInforHead.biClrUsed << endl;
    cout << "重要颜色数:" << pBmpInforHead.biClrImportant << endl;
}
//-----------------------------------------------------------------------------------------
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool loadBmpFile(char *bmpName)
{
    FILE *fp = fopen(bmpName, "rb"); //二进制读方式打开指定的图像文件
    if (fp == 0)
        return 0;

    //跳过位图文件头结构BITMAPFILEHEADER
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);
    /*
	BITMAPFILEHEADER filehead;
	fread(&filehead, 1, sizeof(BITMAPFILEHEADER), fp);
	showBmpHead(filehead);//显示文件头   
*/

    //定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
    BITMAPINFOHEADER infohead;
    fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp); //获取图像宽、高、每像素所占位数等信息
    bmpWidth = infohead.biWidth;
    bmpHeight = infohead.biHeight;
    biBitCount = infohead.biBitCount; //定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
    showBmpInfoHead(infohead);       //显示信息头

    int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4; //灰度图像有颜色表，且颜色表表项为256
    if (biBitCount == 8)
    {
        //申请颜色表所需要的空间，读颜色表进内存
        pColorTable = new RGBQUAD[256];
        fread(pColorTable, sizeof(RGBQUAD), 256, fp);
    }

    //申请位图数据所需要的空间，读位图数据进内存
    pBmpBuf = new unsigned char[lineByte * bmpHeight];
    fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
    fclose(fp); //关闭文件
    return 1;   //读取文件成功
}

//保存图片
bool saveBmpFile(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{

    //如果位图数据指针为0，则没有数据传入，函数返回
    if (!imgBuf)
        return 0;
    //颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
    int colorTablesize = 0;
    if (biBitCount == 8)
        colorTablesize = 1024;

    //待存储图像数据每行字节数为4的倍数
    int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

    //以二进制写的方式打开文件
    FILE *fp = fopen(bmpName, "wb");

    if (fp == 0)
        return 0;
    //------------------------------------------------------------------------------------------------------------------
    //申请位图文件头结构变量，填写文件头信息
    BITMAPFILEHEADER fileHead;
    fileHead.bfType = 0x4D42; //bmp类型

    //bfSize是图像文件4个组成部分之和
    fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;
    fileHead.bfReserved1 = 0;
    fileHead.bfReserved2 = 0;

    //bfOffBits是图像文件前3个部分所需空间之和
    fileHead.bfOffBits = 54 + colorTablesize;
    //--------------------------------------------------------------------------------------------------------------------
    //写文件头进文件
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

    //申请位图信息头结构变量，填写信息头信息
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

    //写位图信息头进内存
    fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
    //----------------------------------------------------------------------------------------------------------------------
    //如果灰度图像，有颜色表，写入文件
    if (biBitCount == 8)
        fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);

    //写位图数据进文件
    fwrite(imgBuf, height * lineByte, 1, fp);

    //关闭文件
    fclose(fp);
    return 1;
}

void image_scaling_nearest()
{
    char readPath[] = "C:\\VSCode_workspace\\vscode-workspace\\src\\demo.bmp";
    loadBmpFile(readPath);

    unsigned char *imagedata = NULL;     //动态分配存储原图片的像素信息的二维数组
    unsigned char *imagedataScal = NULL; //动态分配存储缩放后的图片的像素信息的二维数组
    imagedata = pBmpBuf;

    float ExpScalValue = 0;                ////期望的缩放倍数（允许小数）
    int FloatToIntwidth, FloatToIntheight; /////小数变成整数(float To Int)
    int RotateAngle = 90;                  //要缩放的角度，默认90

    //图片缩放处理
    cout << "请输入要缩放的倍数:" << endl;
    cin >> ExpScalValue;

    ///如果ExpScalValue含有小数，需要整数化
    ///对期望的缩放结果取整
    FloatToIntwidth = (int)(ExpScalValue * bmpWidth);
    FloatToIntheight = (int)(ExpScalValue * bmpHeight);
    //图像每一行的字节数必须是4的整数倍
    int lineByte2 = (FloatToIntwidth * biBitCount / 8 + 3) / 4 * 4;
    imagedataScal = new unsigned char[lineByte2 * FloatToIntheight]; ///为缩放后图像分配存储空间

    int pre_i, pre_j, after_i, after_j; //缩放前后对应的像素点坐标
    for (int i = 0; i < FloatToIntheight; i++)
    {
        for (int j = 0; j < FloatToIntwidth; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                after_i = i;
                after_j = j;
                pre_i = (int)(after_i / ExpScalValue); //取整，插值方法为：最邻近插值（近邻取样法）
                pre_j = (int)(after_j / ExpScalValue);
                if (pre_i >= 0 && pre_i < bmpHeight && pre_j >= 0 && pre_j < bmpWidth) //在原图范围内
                    *(imagedataScal + i * lineByte2 + j * 4 + k) = *(imagedata + pre_i * bmpWidth * 4 + pre_j * 4 + k);
            }
        }
    }
    //保存bmp图片
    char writePath[] = "111.bmp";
    saveBmpFile(writePath, imagedataScal, FloatToIntwidth, FloatToIntheight, biBitCount, pColorTable);
    printf("缩放变换完成，请查看Scalresult.bmp文件。\n\n");

    //释放内存
    delete[] imagedata;
    delete[] imagedataScal;
}

void image_scaling_doubleline()
{

    char readPath[] = "C:\\VSCode_workspace\\vscode-workspace\\src\\demo.bmp";
    loadBmpFile(readPath);

    unsigned char *imagedata;     //动态分配存储原图片的像素信息的二维数组
    unsigned char *imagedataScal; //动态分配存储缩放后的图片的像素信息的二维数组
    imagedata = pBmpBuf;

    float ExpScalValue = 0;                ////期望的缩放倍数（允许小数）
    int FloatToIntwidth, FloatToIntheight; /////小数变成整数(float To Int)
    int RotateAngle = 90;                  //要缩放的角度，默认90

    //图片缩放处理
    cout << "请输入要缩放的倍数:" << endl;
    cin >> ExpScalValue;

    ///如果ExpScalValue含有小数，需要整数化
    ///对期望的缩放结果取整
    FloatToIntwidth = (int)(ExpScalValue * bmpWidth);
    FloatToIntheight = (int)(ExpScalValue * bmpHeight);
    //图像每一行的字节数必须是4的整数倍
    int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
    int lineByte2 = (FloatToIntwidth * biBitCount / 8 + 3) / 4 * 4;
    imagedataScal = new unsigned char[lineByte2 * FloatToIntheight]; ///为缩放后图像分配存储空间

    /*******************图像处理部分******************/
    /*******************双线性插值******************/
    for (int i = 0; i < FloatToIntheight; i++)
        for (int j = 0; j < FloatToIntwidth; j++)
        {

            float d_original_img_hnum = i / ExpScalValue;
            float d_original_img_wnum = j / ExpScalValue;
            int i_original_img_hnum = d_original_img_hnum;
            int i_original_img_wnum = d_original_img_wnum;
            float distance_to_a_x = d_original_img_wnum - i_original_img_wnum; //在原图像中与a点的水平距离
            float distance_to_a_y = d_original_img_hnum - i_original_img_hnum; //在原图像中与a点的垂直距离

            int original_point_a = i_original_img_hnum * lineByte + i_original_img_wnum * 4;             //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点A
            int original_point_b = i_original_img_hnum * lineByte + (i_original_img_wnum + 1) * 4;       //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点B
            int original_point_c = (i_original_img_hnum + 1) * lineByte + i_original_img_wnum * 4;       //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点C
            int original_point_d = (i_original_img_hnum + 1) * lineByte + (i_original_img_wnum + 1) * 4; //数组位置偏移量，对应于图像的各像素点RGB的起点,相当于点D

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

            int pixel_point = i * lineByte2 + j * 4; //映射尺度变换图像数组位置偏移量
            for (int k = 0; k < 4; k++)
            {

                imagedataScal[pixel_point + k] =
                    imagedata[original_point_a + k] * (1 - distance_to_a_x) * (1 - distance_to_a_y) +
                    imagedata[original_point_b + k] * distance_to_a_x * (1 - distance_to_a_y) +
                    imagedata[original_point_c + k] * distance_to_a_y * (1 - distance_to_a_x) +
                    imagedata[original_point_d + k] * distance_to_a_y * distance_to_a_x;
                /*assert((pixel_point + k)<(lineByte2 * FloatToIntheight));
					assert((original_point_a + k)<(lineByte * bmpHeight));
					assert((original_point_b + k)<(lineByte * bmpHeight));
					assert((original_point_c + k)<(lineByte * bmpHeight));
					assert((original_point_d + k)<(lineByte * bmpHeight));*/
            }
        }
    /*******************双线性插值******************/
    /*******************图像处理部分******************/
    //保存bmp图片
    char writePath[] = "dlbmp.bmp";
    saveBmpFile(writePath, imagedataScal, FloatToIntwidth, FloatToIntheight, biBitCount, pColorTable);
    printf("缩放变换完成，请查看Scalresult.bmp文件。\n\n");
    //释放内存
    delete[] imagedata;
    delete[] imagedataScal;
}

int main()
{
    image_scaling_doubleline();
    return 0;
}