#ifndef BOOKS
#define BOOKS

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

void printlnSheetTitle(void) {
    printf("bookID\tRemain\tTotal\tName\tAuthor(s)\n");
    printf("-----------------------------------------\n");
}

bool compareAuthors(book a, book b) {
    if (a.authorNum != b.authorNum)
        return false;
    for (int i = 0; i < a.authorNum; i++) {
        if (strcmp(a.author[i], b.author[i]) != 0)
            return false;
    }
    return true;
}

int bookCompare(book a, book b) {
    if (a.bookID == b.bookID && strcmp(a.name, b.name) == 0 && compareAuthors(a, b) == true)
        return 0;
    if (a.bookID == b.bookID)
        return 1;
    if (strcmp(a.name, b.name) == 0 && compareAuthors(a, b) == true)
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
    printf("Book with Given Name Not Found: %s", searchingName);
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