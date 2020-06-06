#ifndef ADMINACCOUNT
#define ADMINACCOUNT

#include "books.h"
#include "structs.h"

bool addBooks(bookList* lib, book* newBook) {
    bookList* curr = lib;
    while (true) {
        if (curr->book != NULL) {
            if (bookCompare(*curr->book, *newBook) == 1) {
                printf("Duplict bookID Detected: %d, and That's NOT Allowed.\n", newBook->bookID);
                return false;
            }

            if (bookCompare(*curr->book, *newBook) == 2) {
                printf("Same Books with Different bookID, Conflicts with Existing Books(bookID %d).\n",
                       curr->book->bookID);
                return false;
            }

            if (bookCompare(*curr->book, *newBook) == 0) {
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
        }
        if (curr->next == NULL)
            break;
        curr = curr->next;
    }
    bookList* newNode = (bookList*)malloc(sizeof(bookList));
    curr->next = newNode;
    newNode->book = newBook;
    newNode->next = NULL;
    return true;
}

bool removeBook(bookList* booklist, int bookID) {
    bookList* curr = booklist;
    while (curr->next != NULL) {
        if (curr->book != NULL && curr->book->bookID == bookID) {
            if (curr->book->remainNum != curr->book->totalNum) {
                printf("Book(bookID %d) Found, But Cannot Be Removed\n", bookID);
                printf("Because %d of Them Are Being Borrowed\n", curr->book->totalNum - curr->book->remainNum);
                return false;
            }
            printf("Book(bookID %d) Found. Details Are As Follows.\n", bookID);
            printlnSheetTitle();
            printlnBook(*searchBookByBookID(booklist, bookID));

            bookList* former = booklist;
            while (former->next != curr) {
                former = former->next;
            }
            former->next = former->next->next;
            free(curr);
            printf("Book(bookID %d) Successfully Removed\n", bookID);
            return false;
        }
        curr = curr->next;
    }
    printf("Book(bookID %d) Not Found.\n", bookID);
    return false;
}

bool addStuAccount(stuList* stulist, student* newStuAcc) {
    stuList* curr = stulist;
    while (curr->next != NULL) {
        curr = curr->next;
        if (curr->stu->stuID == newStuAcc->stuID) {
            printf("Student with Same stuID Already Exists.\nFailed to Add This Student.\n");
            return false;
        }
        if (strcmp(curr->stu->name, newStuAcc->name) == 0) {
            printf("Student with Same Name Already Exists.\nFailed to Add This Student.\n");
            return false;
        }
    }
    stuList* newNode = (stuList*)malloc(sizeof(stuList));
    newNode->stu = newStuAcc;
    newNode->next = NULL;
    curr->next = newNode;
    return true;
}

bool removeStuAccount(stuList* stulist, int stuID) {
    stuList* curr = stulist;
    while (curr->next != NULL) {
        if (curr->stu != NULL && curr->stu->stuID == stuID) {
            if (curr->stu->borrowingBookNum != 0) {
                printf("This Student Account(stuID %d) Cannot Be Removed,\n", stuID);
                printf("Because This Account Owns %d Unreturned Book(s)\n", curr->stu->borrowingBookNum);
                return false;
            }
            stuList* former = stulist;
            while (former->next != curr) {
                former = former->next;
            }
            former->next = former->next->next;
            free(curr);
            printf("Student Account(stuID %d) Successfully Removed\n", stuID);
            return true;
        }
        curr = curr->next;
    }
    printf("Student with stuID: %d Not Found.\n", stuID);
    return false;
}

bool exportToFileSystem(bookList* booklist, stuList* stulist, int bookNum, int stuNum) {
    FILE *bookFile, *stuFile;
    bookFile = fopen("book.libdata", "w+");
    stuFile = fopen("stu.libdata", "w+");

    if (bookFile == NULL || stuFile == NULL) {
        printf("Cannot Open Output File\n");
        return false;
    }

    fprintf(bookFile, "Senren*Banka\n%d\n", bookNum);
    bookList* currBook = booklist->next;
    for (int i = 0; i < bookNum; i++) {
        fprintf(bookFile, "%d\t%s\t%d\t", currBook->book->bookID, currBook->book->name, currBook->book->authorNum);
        for (int authorCnt = 0; authorCnt < currBook->book->authorNum; authorCnt++) {
            fprintf(bookFile, "%s,", currBook->book->author[authorCnt]);
        }
        fprintf(bookFile, "\t");
        fprintf(bookFile, "%d\t%d\t", currBook->book->totalNum, currBook->book->remainNum);
        for (int i = 0; i < currBook->book->totalNum - currBook->book->remainNum; i++) {
            fprintf(bookFile, "%d,", currBook->book->borrowingStuID[i]);
        }
        fprintf(bookFile, "\n");
        currBook = currBook->next;
    }
    fclose(bookFile);

    fprintf(stuFile, "YuzuSoft\n%d\n", stuNum);
    stuList* currStu = stulist->next;
    for (int i = 0; i < stuNum; i++) {
        fprintf(stuFile, "%d\t%s\t", currStu->stu->stuID, currStu->stu->name);
        fprintf(stuFile, "%d\t", currStu->stu->borrowingBookNum);
        for (int borrowingNum = 0; borrowingNum < currStu->stu->borrowingBookNum;borrowingNum++) {
            fprintf(stuFile, "%d,", currStu->stu->borrowingBooks[borrowingNum]);
        }
        fprintf(stuFile, "\n");
        currStu = currStu->next;
    }
    fclose(stuFile);

    return true;
}

#endif
