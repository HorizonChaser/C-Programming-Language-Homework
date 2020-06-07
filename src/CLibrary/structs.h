#ifndef STRUCTS
#define STRUCTS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char name[20];
    int bookID;
    int totalNum;
    int remainNum;
    int borrowingStuID[50];
} book;

typedef struct Student {
    int stuID;
    char name[20];
    int borrowingBooks[5];
    int borrowingBookNum;
} student;

typedef struct stuList {
    student* stu;
    struct stuList* next;
} stuList;

typedef struct bookList {
    book* book;
    struct bookList* next;
} bookList;

#endif