#ifndef STRUCTS
#define STRUCTS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//图书
typedef struct Book {
    char name[20];           //书名
    int bookID;              //ID
    int totalNum;            //总量
    int remainNum;           //余量
    int borrowingStuID[50];  //借书人名单
} book;

//学生
typedef struct Student {
    int stuID;              //学号
    char name[20];          //姓名
    int borrowingBooks[5];  //借书清单
    int borrowingBookNum;   //借书数量
} student;

//学生链表
typedef struct stuList {
    student* stu;
    struct stuList* next;
} stuList;

//图书链表
typedef struct bookList {
    book* book;
    struct bookList* next;
} bookList;

#endif