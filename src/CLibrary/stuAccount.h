#ifndef STUACCOUNT
#define STUACCOUNT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

student* initializeStuAccount(int inStuID, char* inName) {
    student* newStuAcc = (student*)malloc(sizeof(student));
    strcpy(newStuAcc->name, inName);
    newStuAcc->stuID = inStuID;
    newStuAcc->borrowingBookNum = 0;
    for (int i = 0; i < 5; i++) {
        newStuAcc->borrowingBooks[i] = 0;
    }
    return newStuAcc;
}

bool borrowBook(bookList* lib, int bookID, student* student) {
    bookList* curr = lib;
    if (lib == NULL || lib->next == NULL) {
        printf("No Existing Books\n");
        return false;
    }
    while (curr != NULL) {
        if (curr->book->bookID == bookID) {
            if (curr->book->remainNum >= 1 && student->borrowingBookNum <= 5) {
                curr->book->remainNum--;
                curr->book->borrowingStuID[curr->book->totalNum -
                                           curr->book->remainNum] =
                    student->stuID;
                student->borrowingBooks[student->borrowingBookNum] = bookID;
                student->borrowingBookNum++;
                printf("Successfully Borrowed Book(bookID %d)\n",
                       curr->book->bookID);
                return true;
            }
            if (curr->book->remainNum <= 0) {
                printf("No Remaining Books with bookID: %d\n",
                       curr->book->bookID);
                return false;
            }
            if (student->borrowingBookNum >= 5) {
                printf(
                    "You Have Reached Book Borrowing Num Limit: 5\n"
                    "Return Some If You Want to Borrow Some New Ones\n");
                return false;
            }
        }
    }
    printf(
        "Book Borrowing Process Failed, "
        "for Book with Given bookID Not Found: %d\n",
        bookID);
    return false;
}

void printAllBorringBooks(student* stu, bookList* booklist) {
    if (stu->borrowingBookNum == 0) {
        printf("You Haven't Borrowed Any Book Yet. Nothing to Show.\n");
        for (int i = 0; i < 5; i++) {
            stu->borrowingBooks[i] = -1;
        }
        return;
    }
    printf("You're Borrowing %d Book(s) Currently. Details Are As Follows.\n", stu->borrowingBookNum);
    printf("bookID\tRemain Num\tTotal Num\tName\tAuthor(s)\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < stu->borrowingBookNum; i++) {
        printlnBook(*searchBookByBookID(booklist, stu->borrowingBooks[i]));
    }
}

#endif