#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adminAccount.h"
#include "books.h"
#include "stuAccount.h"

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
    head->stu = NULL;
    head->next = NULL;
    return head;
}

int main(int argc, char* argv[]) {
    char* author[5];
    author[0] = "dsv\0";
    author[1] = "dev2\0";
    book* book2 = initializeBook("test", author, 2, 10, 20);
    book* book1 = initializeBook("asd", author, 1, 11, 20);
    student* stu1 = initializeStuAccount(1002, "tester01");
    student* stu2 = initializeStuAccount(1003, "tester02");

    bookList* booklist = initializeBookList();
    stuList* stulist = initializeStuList();
    addBooks(booklist, book1);
    addBooks(booklist, book2);
    addStuAccount(stulist, stu1);
    addStuAccount(stulist, stu2);
    borrowBook(booklist, 10, stu1);
    borrowBook(booklist, 11, stu1);

    if (argc < 0) {
        printf("Missing Necessary Arguments\n");
        printf("Usage:  Libsim -a/-u USERNAME\n");
        printf("    -a          Login as Administrator\n");
        printf("    -u          Login as User(or Student)\n");
        printf("    USERNAME    User Name\n");
        return -1;
    }

    exportToFileSystem(booklist, stulist, 2, 2);

    student* currStudent = stu1;
    printf("┌-----| Welcome to use C Library written by HorizonChaser |-----┐\n");
    printf("├---------------------------------------------------------------┤\n");
    printf("|[NOTICE]Input the number ahead of the function as your choice  |\n");
    printf("├---------------------------------------------------------------┤\n");
    printf("|       Current Logged in as Student Account, stuID = %-10d|\n", currStudent->stuID);
    printf("├---------------------------------------------------------------┤\n");
    printf("|         1. Borrow A Book From The Library                     |\n");
    printf("|         2. Return A Book to The Library                       |\n");
    printf("|         3. List All Borrowing Books of Yours                  |\n");
    printf("|         4. Search A Book by bookID                            |\n");
    printf("|         5. Search A Book by Book Name                         |\n");
    printf("|         6. List All Existing Books in the Library             |\n");
    printf("|         7. Exit the C Library                                 |\n");
    printf("└---------------------------------------------------------------┘\n");
    return 0;
}