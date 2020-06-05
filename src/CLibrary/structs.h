#ifndef STRUCTS
#define STRUCTS


typedef struct Book {
    char name[20];
    char author[5][20];
    int authorNum;
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