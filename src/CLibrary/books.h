#ifndef BOOKS
#define BOOKS

#include "structs.h"

///图书相关函数

//初始化一本书
book* initializeBook(const char* name, int bookID, int totalNum) {
    if (strlen(name) > 20) {
        printf("Book Name Length Limit Exceeded\n");
        return NULL;
    }

    book* newBook = (book*)malloc(sizeof(book));  //分配内存
    strcpy(newBook->name, name);                  //复制名称
    newBook->bookID = bookID;
    newBook->totalNum = newBook->remainNum = totalNum;
    for (int i = 0; i < 50; i++) {
        newBook->borrowingStuID[i] = 0;
    }
    return newBook;
}

//输出一本书的信息
void printlnBook(const book book) {
    printf("%d\t%d\t%d\t", book.bookID, book.remainNum, book.totalNum);
    printf("%s\t", book.name);
    printf("\n");
}

//输出表头
void printlnSheetTitle(void) {
    printf("bookID\tRemain\tTotal\tName\t\n");
    printf("-----------------------------------------\n");
}

//比较两本书
int bookCompare(book a, book b) {
    if (a.bookID == b.bookID && strcmp(a.name, b.name) == 0)
        return 0;
    if (a.bookID == b.bookID)
        return 1;
    if (strcmp(a.name, b.name) == 0)
        return 2;
    return -1;
}

//根据名称搜索书
book* searchBookByName(bookList* lib, char* searchingName) {
    bookList* curr = lib->next;
    while (curr != NULL) {
        if (strcmp(curr->book->name, searchingName) == 0) {
            printf("Book with Name Found. Details Are As Follows.\n");
            printlnSheetTitle();
            printlnBook(*curr->book);
            return curr->book;
        }
        curr = curr->next;
    }
    printf("Book with Given Name Not Found: %s\n", searchingName);
    return NULL;
}

//根据BookID搜索书
book* searchBookByBookID(bookList* booklist, const int inBookID) {
    bookList* curr = booklist->next;
    while (curr != NULL) {
        if (curr->book->bookID == inBookID) {
            return curr->book;
        }
        curr = curr->next;
    }
    return NULL;
}

bool editBookInfo(book* book) {
    printf("Please Select What You Want To Change:\n1.Book Name 2.Book Total Num\nYour Choice: ");
    int choice = -1, deltaAmount = 0;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Please Input The New Name of The Book(Max Length 20 chars): ");
            scanf("%s", book->name);
            return true;
            break;

        case 2:
            printf("Please Input The Amount Add to The Total Num: ");
            scanf("%d", &deltaAmount);
            if(deltaAmount + book->remainNum < 0) {
                printf("Invalid Input: New Remain Num Less Than 0\n");
                return false;
            }
            book->remainNum += deltaAmount;
            book->totalNum += deltaAmount;
            return true;
            break;

        default:
            printf("Unrecongized Invalid Input: %d\n", choice);
            return false;
            break;
    }
    return false;
}

#endif