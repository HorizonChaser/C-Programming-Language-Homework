#ifndef STUACCOUNT
#define STUACCOUNT

#include "books.h"
#include "structs.h"

student* initializeStuAccount(int inStuID, char* inName) {
    if (inStuID <= 0) {
        printf("Invalid stuID(<=0): %d, It Should Be Above 0\n", inStuID);
        return NULL;
    }
    if (strchr(inName, ' ') != NULL) {
        printf("Invalid Name: %s, SPACE Not Allowed\n", inName);
        return NULL;
    }

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
    bookList* curr = lib->next;
    if (curr == NULL || curr->next == NULL) {
        printf("No Existing Books in The Library\n");
        return false;
    }
    while (curr != NULL) {
        if (curr->book->bookID == bookID) {
            for (int i = 0; i < 5; i++) {
                if (student->borrowingBooks[i] == bookID) {
                    printf("You Have Borrowed The Same Book.\n");
                    return false;
                }
            }

            if (curr->book->remainNum >= 1 && student->borrowingBookNum <= 5) {
                curr->book->remainNum--;
                curr->book->borrowingStuID[curr->book->totalNum -
                                           curr->book->remainNum - 1] =
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
        curr = curr->next;
    }
    printf(
        "Book Borrowing Process Failed, "
        "for Book with Given bookID Not Found: %d\n",
        bookID);
    return false;
}

bool returnBook(bookList* booklist, int BookID, student* stu) {
    for (int i = 0; i < 5; i++) {
        if (stu->borrowingBooks[i] == BookID) {
            stu->borrowingBooks[i] = 0;
            stu->borrowingBookNum--;

            //将这本书从该学生的借书清单中移除, 并去掉中间的空值0

            int newBorrowingBooks[5];
            for (int pos = 0; pos < 5; pos++) {
                newBorrowingBooks[pos] = stu->borrowingBooks[pos];
            }
            int oldArrayPos = 0;
            for (int pos = 0; pos < 5; pos++) {
                if (newBorrowingBooks[pos] != 0) {
                    stu->borrowingBooks[oldArrayPos] = newBorrowingBooks[pos];
                    oldArrayPos++;
                }
            }
            searchBookByBookID(booklist, BookID)->remainNum++;
            printf("Successfully Returned Book(bookID %d)\n", BookID);
            return true;
        }
    }
    printf("You Didn't Borrow Book(bookID %d), or This Book Doesn't Exist.\n", BookID);
    return false;
}

void printAllBorringBooks(student* stu, bookList* booklist) {
    if (stu->borrowingBookNum == 0) {
        printf("Name: %s  Currently Borrowing %d Books\nNothing to Show\n", stu->name, stu->borrowingBookNum);
        for (int i = 0; i < 5; i++) {
            stu->borrowingBooks[i] = -1;
        }
        return;
    }
    printf("Name: %s  Currently Borrowing %d Books\n", stu->name, stu->borrowingBookNum);
    printlnSheetTitle();
    for (int i = 0; i < stu->borrowingBookNum; i++) {
        printlnBook(*searchBookByBookID(booklist, stu->borrowingBooks[i]));
    }
}

student* searchStuAccountByStuID(stuList* stulist, int stuID) {
    stuList* curr = stulist->next;
    while (curr != NULL) {
        if (curr->stu->stuID == stuID)
            return curr->stu;
        curr = curr->next;
    }
    return NULL;
}

void viewBorrowers(stuList* stulist, book* book) {
    if (book->totalNum == book->remainNum) {
        printf("This Book Hasn't Been Borrowed Yet. Nothing to Show.\n");
        return;
    }
    int borrowNum = book->totalNum - book->remainNum;
    printf("stuID\tName\n----------------\n");
    for (int i = 0; i < borrowNum; i++) {
        student* currStudent = searchStuAccountByStuID(stulist, book->borrowingStuID[i]);
        printf("%d\t%s\n", currStudent->stuID, currStudent->name);
    }
}

#endif