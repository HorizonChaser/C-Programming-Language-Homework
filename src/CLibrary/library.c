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
        if (curr->book != NULL)
            printlnBook(*curr->book);
        curr = curr->next;
    }
}

bookList* initializeBookList(void) {
    bookList* head = (bookList*)malloc(sizeof(bookList));
    head->book = NULL;
    head->next = NULL;
    return head;
}

stuList* initializeStuList(void) {
    stuList* head = (stuList*)malloc(sizeof(stuList));
    head->stu =  NULL;
    head->next = NULL;
    return head;
}

int main(int argc, char* argv[]) {
    char* author[5];
    author[0] = "dsv\0";
    book* book2 = initializeBook("test", author, 1, 10, 20);
    book* book1 = initializeBook("asd", author, 1, 10, 20);
    student* stu1 = initializeStuAccount(1001, "tester01");
    student* stu2 = initializeStuAccount(1002, "tester02");

    bookList* booklist = initializeBookList();
    stuList* stulist = initializeStuList();

    addBooks(booklist, book1);
    addBooks(booklist, book2);
    addStuAccount(stulist, stu1);
    addStuAccount(stulist, stu2);
    printallBook(booklist);
    return 0;
}