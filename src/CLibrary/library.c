#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adminAccount.h"
#include "books.h"
#include "stuAccount.h"

book* initializeBook(const char* name, char* author[], const int authorNum,
                     int bookID, int totalNum);
void printlnBook(const book book);
bool addBooks(bookList* lib, book* newBook);

void printallBook(bookList* booklist) {
    if (booklist == NULL || booklist->next == NULL) {
        printf("No Existing Books\n");
        return;
    }
    bookList* curr = booklist->next;
    while (curr != NULL) {
        printlnBook(*curr->book);
        curr = curr->next;
    }
}

int main(int argc, char* argv[]) {
    char* author[5];
    author[0] = "dsv\0";
    book* book2 = initializeBook("test", author, 1, 10, 20);
    book* book1 = initializeBook("asd", author, 1, 10, 20);

    bookList* booklist = (bookList*)malloc(sizeof(bookList));
    booklist->book = NULL;
    booklist->next = (bookList*)malloc(sizeof(bookList));
    booklist->next->book = book1;
    booklist->next->next = NULL;
    addBooks(booklist, book2);
    printallBook(booklist);
    return 0;
} 