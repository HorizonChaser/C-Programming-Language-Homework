#ifndef BOOKS
#define BOOKS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

book* initializeBook(const char* name, char* author[], const int authorNum,
                     int bookID, int totalNum) {
    if (strlen(name) > 20) {
        printf("Book Name Length Limit Exceeded\n");
        return NULL;
    }
    if (authorNum > 5) {
        printf("Author Quantity Limit Exceeded\n");
        return NULL;
    }

    book* newBook = (book*)malloc(sizeof(book));
    strcpy(newBook->name, name);
    for (int i = 0; i < authorNum; i++) {
        strcpy(newBook->author[i], author[i]);
    }
    newBook->authorNum = authorNum;
    newBook->bookID = bookID;
    newBook->totalNum = newBook->remainNum = totalNum;
    for (int i = 0; i < 50; i++) {
        newBook->borrowingStuID[i] = 0;
    }

    return newBook;
}

void printlnBook(const book book) {
    printf("%d\t%d\t%d\t", book.bookID, book.remainNum, book.totalNum);
    printf("%s\t", book.name);
    for (int i = 0; i < book.authorNum; i++) {
        printf("%s", book.author[i]);
        if (i != book.authorNum - 1) printf(", ");
    }
    printf("\n");
}

bool bookCompare(book a, book b) {
    if (a.bookID != b.bookID || a.authorNum != b.authorNum) return false;
    if (strcmp(a.name, b.name) != 0) return false;
    for (int i = 0; i < a.authorNum; i++) {
        if (strcmp(a.author[i], b.author[i]) != 0) return false;
    }
    return true;
}

book* searchBookByName(bookList* lib, char* searchingName) {
    bookList* curr = lib;
    while (curr->next != NULL) {
        if (strcmp(curr->book->name, searchingName) == 0) {
            printf("Book with Name Found. Details Are As Follows.\n");
            printf("bookID\tRemain Num\tTotal Num\tName\tAuthor(s)\n");
            printf(
                "-------------------------------------------------------------"
                "\n");
            printlnBook(*curr->book);
            return curr->book;
        }
    }
    printf("Book with Given Name Not Found: %s", searchingName);
    return NULL;
}

book* searchBookByBookID(bookList* booklist, const int inBookID) {
    bookList* curr = booklist;
    while(curr->next != NULL) {
        if(curr->book->bookID == inBookID) {
            return curr->book;
        }
    }
    return NULL;
}

#endif