#ifndef BOOKS
#define BOOKS

#include "structs.h"

book* initializeBook(const char* name, int bookID, int totalNum) {
    if (strlen(name) > 20) {
        printf("Book Name Length Limit Exceeded\n");
        return NULL;
    }

    book* newBook = (book*)malloc(sizeof(book));
    strcpy(newBook->name, name);
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
    printf("\n");
}

void printlnSheetTitle(void) {
    printf("bookID\tRemain\tTotal\tName\t\n");
    printf("-----------------------------------------\n");
}

int bookCompare(book a, book b) {
    if (a.bookID == b.bookID && strcmp(a.name, b.name) == 0)
        return 0;
    if (a.bookID == b.bookID)
        return 1;
    if (strcmp(a.name, b.name) == 0)
        return 2;
    return -1;
}

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

#endif