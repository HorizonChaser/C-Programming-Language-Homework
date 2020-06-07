#ifndef ADMINACCOUNT
#define ADMINACCOUNT

#include "books.h"
#include "structs.h"

///管理员账户的相关函数

//添加一本书
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
                printf("Same Book Already Exists, Casuing Conflicts.\n");
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

//删除一本书, 但是必须没有人在借阅
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
            while (former->next != curr) {//找到这本书在链表上的前一个结点
                former = former->next;
            }
            former->next = former->next->next;//将前一个结点和后一个结点连接起来
            free(curr);//删除当前节点
            printf("Book(bookID %d) Successfully Removed\n", bookID);
            return false;
        }
        curr = curr->next;
    }
    printf("Book(bookID %d) Not Found.\n", bookID);
    return false;
}

//添加一个学生账户
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
    //将新的账户挂到链表最后面
    newNode->stu = newStuAcc;
    newNode->next = NULL;
    curr->next = newNode;
    return true;
}

//删除学生账户, 要求该账户没有在借图书
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
            former->next = former->next->next;//将前后连接起来
            free(curr);//删除结点
            printf("Student Account(stuID %d) Successfully Removed\n", stuID);
            return true;
        }
        curr = curr->next;
    }
    printf("Student with stuID: %d Not Found.\n", stuID);
    return false;
}

//导出到文件系统(由于fscanf()的未知问题, 暂无可配套的import相关函数...)
bool exportToFileSystem(bookList* booklist, stuList* stulist, int bookNum, int stuNum) {
    FILE *bookFile, *stuFile;
    //打开输出文件
    bookFile = fopen("book.libdata", "w+");
    stuFile = fopen("stu.libdata", "w+");

    if (bookFile == NULL || stuFile == NULL) {
        printf("Cannot Open Output File\n");
        return false;
    }

    //校验用文件头, 检测文件是否损坏
    fprintf(bookFile, "Senren*Banka\n%d\n", bookNum);
    bookList* currBook = booklist->next;
    for (int bookCnt = 0; bookCnt < bookNum; bookCnt++) {
        if (currBook == NULL)
            break;
        fprintf(bookFile, "%d\t%s\t", currBook->book->bookID, currBook->book->name);
        fprintf(bookFile, "%d\t%d\t", currBook->book->totalNum, currBook->book->remainNum);
        for (int i = 0; i < currBook->book->totalNum - currBook->book->remainNum; i++) {
            fprintf(bookFile, "%d\t", currBook->book->borrowingStuID[i]);
        }
        //fprintf(bookFile, "\t");
        fprintf(bookFile, "\n");
        currBook = currBook->next;
    }
    fclose(bookFile);

    fprintf(stuFile, "YuzuSoft\n%d\n", stuNum);
    stuList* currStu = stulist->next;
    for (int i = 0; i < stuNum; i++) {
        fprintf(stuFile, "%d\t%s\t", currStu->stu->stuID, currStu->stu->name);
        fprintf(stuFile, "%d\t", currStu->stu->borrowingBookNum);
        for (int borrowingNum = 0; borrowingNum < currStu->stu->borrowingBookNum; borrowingNum++) {
            fprintf(stuFile, "%d\t", currStu->stu->borrowingBooks[borrowingNum]);
        }
        fprintf(stuFile, "\n");
        currStu = currStu->next;
    }
    fclose(stuFile);

    return true;
}

bool importFromFileSystem(bookList* booklist, stuList* stulist) {
    FILE *bookFile, *stuFile;
    bookFile = fopen("book.libdata", "r+");
    stuFile = fopen("stu.libdata", "r+");
    bool fileCorruptFlag = false;

    book* bookBuffer = (book*)malloc(sizeof(book));
    student* stuBuffer = (student*)malloc(sizeof(student));
    char* checkFileHeader = (char*)malloc(20 * sizeof(char));
    int bookNum = 0, stuNum = 0;

    fscanf(bookFile, "%s\n%d\n", checkFileHeader, &bookNum);
    if (strcmp(checkFileHeader, "Senren*Banka") != 0) {
        printf("Corrupted Book Info File, Nothing Will Be Imported\n");
        fileCorruptFlag = true;
    }
    fscanf(stuFile, "%s\n%d\n", checkFileHeader, &stuNum);
    if (strcmp(checkFileHeader, "YuzuSoft") != 0) {
        printf("Corrupted Student Info File, Nothing Will Be Imported\n");
        fileCorruptFlag = true;
    }
    if (fileCorruptFlag)
        return false;

    for (int num = 0; num < bookNum; num++) {
        fscanf(bookFile, "%d\t%s\t", &bookBuffer->bookID, bookBuffer->name);
        fscanf(bookFile, "%d%d", &bookBuffer->totalNum, &bookBuffer->remainNum);
        for (int i = 0; i < bookBuffer->totalNum - bookBuffer->remainNum; i++) {
            fscanf(bookFile, "%d\t", &bookBuffer->borrowingStuID[i]);
        }
        addBooks(booklist, bookBuffer);
        bookBuffer = (book*)malloc(sizeof(book));
    }
    fclose(bookFile);

    for (int num = 0; num < stuNum; num++) {
        stuBuffer->borrowingBookNum = 0;
        for (int borrowTemp = 0; borrowTemp < 5; borrowTemp++) {
            stuBuffer->borrowingBooks[borrowTemp] = 0;
        }
        fscanf(stuFile, "%d\t%s\t%d\t", &stuBuffer->stuID, stuBuffer->name, &stuBuffer->borrowingBookNum);
        for (int borrowingCnt = 0; borrowingCnt < stuBuffer->borrowingBookNum; borrowingCnt++) {
            fscanf(stuFile, "%d", &stuBuffer->borrowingBooks[borrowingCnt]);
            fgetc(stuFile);
        }
        addStuAccount(stulist, stuBuffer);
        stuBuffer = (student*)malloc(sizeof(student));
    }
    fclose(stuFile);
    return true;
}

#endif
