#ifndef ADMINACCOUNT
#define ADMINACCOUNT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "books.h"
#include "structs.h"

bool addBooks(bookList* lib, book* newBook) {
    bookList* curr = lib;
    while (curr->next != NULL) {
        if (curr->book != NULL && bookCompare(*curr->book, *newBook) == true) {
            printf("Same Book Already Exists. Add to them?(Y/N): ");
            char choice;
            scanf("%c", &choice);
            if (choice == 'Y' || choice == 'y') {
                curr->book->remainNum += newBook->remainNum;
                curr->book->totalNum += newBook->totalNum;
                return true;
            } else
                return false;
        }
        curr = curr->next;
    }
    bookList* newNode = (bookList*)malloc(sizeof(bookList));
    curr->next = newNode;
    newNode->book = newBook;
    newNode->next = NULL;
    return true;
}

#endif
