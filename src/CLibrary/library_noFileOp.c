#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "adminAccount.h"
#include "books.h"
#include "stuAccount.h"

//打印全部的图书
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

//初始化图书链表
bookList* initializeBookList(void) {
    bookList* head = (bookList*)malloc(sizeof(bookList));
    head->book = NULL;
    head->next = NULL;
    return head;
}

//初始化学生链表
stuList* initializeStuList(void) {
    stuList* head = (stuList*)malloc(sizeof(stuList));
    head->stu = NULL;
    head->next = NULL;
    return head;
}

//显示学生的欢迎菜单
void showStudentMenu(student* currStudent) {
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
}

//显示管理员的欢迎菜单
void showAdminMenu(void) {
    printf("┌-----| Welcome to use C Library written by HorizonChaser |-----┐\n");
    printf("├---------------------------------------------------------------┤\n");
    printf("|[NOTICE]Input the number ahead of the function as your choice  |\n");
    printf("├---------------------------------------------------------------┤\n");
    printf("|         Currently Logged in as Administrator Account          |\n");
    printf("├---------------------------------------------------------------┤\n");
    printf("|         1. Add A Book To The Library                          |\n");
    printf("|         2. Delete A Book From The Library                     |\n");
    printf("|         3. List All Students And Their Borrowing Books        |\n");
    printf("|         4. Add A Student Account                              |\n");
    printf("|         5. Delete A Student Account                           |\n");
    printf("|         6. Search A Book by bookID                            |\n");
    printf("|         7. Search A Book by Book Name                         |\n");
    printf("|         8. List All Existing Books in the Library             |\n");
    printf("|         9. View Borrower List of An Existing Book             |\n");
    printf("|         10.Change Info of An Existing Book                    |\n");
    printf("|         11.Change Name of An Student Account                  |\n");
    printf("|         12.Exit the C Library                                 |\n");
    printf("└---------------------------------------------------------------┘\n");
}

//退出并致谢
void exitLibrary(void) {
    printf("-----------------------| Acknowledgement |------------------------\n");
    printf("Thanks for using this C Library Simulator written by HorizonChaser\n");
    printf("Powered by C11, VSCode, Win10 Prof.1909 and Persistance(坚持)\n");
    printf("Institude of C.S.    侯文轩        19030100207\n");
    printf("Finished at 2020/06/07, One Year After The Examination\n");
    exit(0);
}

//暂停控制台, 避免输出被覆盖
void pauseConsole(void) {
    printf("[Press ENTER To Continue]\n");
    getchar();
    getchar();
}

int main(int argc, char* argv[]) {
    //初始化两个链表
    bookList* booklist = initializeBookList();
    stuList* stulist = initializeStuList();
    int choice = -1;

    //预先添加好图书
    book* book2 = initializeBook("Head First Java", 1001, 20);
    book* book1 = initializeBook("Design Patterns", 1002, 30);
    student* stu1 = initializeStuAccount(1909, "Stable");
    student* stu2 = initializeStuAccount(2004, "Preview");

    //模拟图书馆操作
    addBooks(booklist, book1);
    addBooks(booklist, book2);
    addStuAccount(stulist, stu1);
    addStuAccount(stulist, stu2);
    borrowBook(booklist, 1001, stu1);
    borrowBook(booklist, 1002, stu1);
    borrowBook(booklist, 1002, stu2);

    //使用到的变量
    char* newBookName = (char*)malloc(20 * sizeof(char));
    char* newStuName = (char*)malloc(20 * sizeof(char));
    int newBookID = -1, newBookAmount = -1;
    int deleteBookID = -1;
    int newStuID = -1;
    int deleteStuID = -1;
    int bookIDToBeSearched = -1;
    int bookIDToBeChanged = -1;
    int stuIDToBeChanged = -1;
    int bookIDToViewBorrowers = -1;
    char* bookNameToBeSearched = (char*)malloc(20 * sizeof(char));
    stuList* curr = stulist->next;

//Debug用
#define DEBUG
#ifdef DEBUG
    //因为在VSCode中编译选项和运行时的参数是在settings.json里面预先规定好的
    //因此难以方便地指定参数, 所以在这里指定好
    argv[1] = "-a";
    argv[2] = "admin";
    argc = 3;
#endif

//将输出代码页切换到UTF-8, 避免乱码
//但是GDB下执行这俩命令会出现异常, 所以放到预处理里面
#ifndef DEBUG
    system("chcp 65001");
    system("cls");
#endif

    if (argc < 3) {  //参数数量不足
        printf("Missing Necessary Arguments\n");
        printf("Usage:  Libsim -a/-u USERNAME\n");
        printf("    -a          Login as Administrator\n");
        printf("    -u          Login as User(or Student)\n");
        printf("    USERNAME    User Name\n");
        return -1;
    }

    if (strcmp(argv[1], "-a") == 0) {
        if (strcmp(argv[2], "admin") != 0) {  //管理员用户名不正确
            printf("Admin Name Incorrect.\nFailed to Login\n");
            return -1;
        }
        while (true) {
            showAdminMenu();
            printf("Please Input Your Choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    printf("Please Input The Book Name(Max Length 20 chars): ");
                    scanf("%s", newBookName);
                    printf("Please Input The Book ID(ID > 0): ");
                    scanf("%d", &newBookID);
                    printf("Please Input Amount of The Book: ");
                    scanf("%d", &newBookAmount);
                    book* newBook = initializeBook(newBookName, newBookID, newBookAmount);
                    if (addBooks(booklist, newBook) == true) {
                        printf("Siccessfully Added Books to The Library\n");
                    } else {
                        printf("Failed to Add Books\n");
                    }
                    pauseConsole();
                    break;

                case 2:
                    printf("Please Input The bookID of The Book Being Deleted: ");
                    scanf("%d", &deleteBookID);
                    removeBook(booklist, deleteBookID);
                    pauseConsole();
                    break;

                case 3:
                    while (true) {
                        if (curr == NULL || curr->stu == NULL) {
                            break;
                        }
                        printf("\n");
                        printAllBorringBooks(curr->stu, booklist);
                        curr = curr->next;
                    }
                    pauseConsole();
                    break;

                case 4:
                    printf("Please Input The Student Name(Max Length 20 chars): ");
                    scanf("%s", newStuName);
                    printf("Please Input The Student ID(ID > 0): ");
                    scanf("%d", &newStuID);
                    student* newStuAccount = initializeStuAccount(newStuID, newStuName);
                    if (addStuAccount(stulist, newStuAccount) == true) {
                        printf("Successfully Added Student Account\n");
                    } else {
                        printf("Failed to Add Student Account\n");
                    }
                    pauseConsole();
                    break;

                case 5:
                    printf("Please Input The ID of The Student To Be Deleted: ");
                    scanf("%d", &deleteStuID);
                    if (removeStuAccount(stulist, deleteStuID) == false) {
                        printf("Failed to Delete This Student Account\n");
                    } else {
                        printf("Successfully Deleted This Student Account\n");
                    }
                    pauseConsole();
                    break;

                case 6:
                    printf("Please Input The ID of The Book To Be Searched: ");
                    scanf("%d", &bookIDToBeSearched);
                    if (searchBookByBookID(booklist, bookIDToBeSearched) == NULL) {
                        printf("Book with Given ID Not Found: %d", bookIDToBeSearched);
                    } else {
                        printf("Book with ID: %d Found. Details Are As Follows.\n", bookIDToBeSearched);
                        printlnSheetTitle();
                        printlnBook(*searchBookByBookID(booklist, bookIDToBeSearched));
                    }
                    pauseConsole();
                    break;

                case 7:
                    printf("Please Input The Name of The Book To Be Searched: ");
                    scanf("%s", bookNameToBeSearched);
                    searchBookByName(booklist, bookNameToBeSearched);
                    pauseConsole();
                    break;

                case 8:
                    printlnSheetTitle();
                    printallBook(booklist);
                    pauseConsole();
                    break;

                case 9:
                    printf("Please Input The ID of The Book: ");
                    scanf("%d", &bookIDToViewBorrowers);
                    if (searchBookByBookID(booklist, bookIDToViewBorrowers) == NULL) {
                        printf("Book with Given BookID Not Found: %d\n", bookIDToViewBorrowers);
                    } else {
                        viewBorrowers(stulist, searchBookByBookID(booklist, bookIDToViewBorrowers));
                    }
                    pauseConsole();
                    break;

                case 10:
                    printf("Please Input The ID of The Book You Want To Change: ");
                    scanf("%d", &bookIDToBeChanged);
                    if (searchBookByBookID(booklist, bookIDToBeChanged) == NULL) {
                        printf("Book with Given ID Not Found: %d", bookIDToBeChanged);
                        printf("Failed to Change Book Info\n");
                    } else {
                        if (editBookInfo(searchBookByBookID(booklist, bookIDToBeChanged)) == true) {
                            printf("Successfully Changed Book Info\n");
                        } else {
                            printf("Failed to Change Book Info\n");
                        }
                    }
                    pauseConsole();
                    break;

                case 11:
                    printf("Please Input The ID of The Student You Want To Change: ");
                    scanf("%d", &stuIDToBeChanged);
                    if(searchStuAccountByStuID(stulist, stuIDToBeChanged) == NULL) {
                        printf("Student with Given ID Not Found: %d\n", stuIDToBeChanged);
                        printf("Failed To Change Student Info\n");
                    } else {
                        if(editStuInfo(stulist, searchStuAccountByStuID(stulist, stuIDToBeChanged)) == true) {
                            printf("Successfully Changed Student Info\n");
                        } else {
                            printf("Failed to Change Student Info\n");
                        }
                    }
                    pauseConsole();
                    break;

                case 12:
                    exitLibrary();
                    pauseConsole();
                    break;

                default:
                    printf("Unrecongized Command: %d\n", choice);
                    pauseConsole();
                    break;
            }
        }
    }

    if (strcmp(argv[1], "-u") == 0) {
        int inBorrowBookID = -1, inReturnBookID = -1;
        student* currStudent = searchStuAccountByStuID(stulist, atoi(argv[2]));  //根据参数查找对应ID的学生账号
        if (currStudent == NULL) {
            printf("Student with Given stuID Not Found\nFailed to Login\n");
            exit(0);
        }
        while (true) {
            showStudentMenu(currStudent);
            printf("Please Input Your Choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    printf("Please Input ID of The Book You Want To Borrow: ");
                    scanf("%d", &inBorrowBookID);
                    if (borrowBook(booklist, inBorrowBookID, currStudent) == false) {
                        printf("Failed to Borrow Book\n");
                    }
                    pauseConsole();
                    break;

                case 2:
                    printf("Please Input ID of The Book You Want To Return: ");
                    scanf("%d", &inReturnBookID);
                    if (returnBook(booklist, inReturnBookID, currStudent) == false) {
                        printf("Failed to Return Book\n");
                    }
                    pauseConsole();
                    break;

                case 3:
                    printAllBorringBooks(currStudent, booklist);
                    pauseConsole();
                    break;

                case 4:
                    printf("Please Input The ID of The Book To Be Searched: ");
                    scanf("%d", &bookIDToBeSearched);
                    if (searchBookByBookID(booklist, bookIDToBeSearched) == NULL) {
                        printf("Book with Given ID Not Found: %d", bookIDToBeSearched);
                    } else {
                        printf("Book with ID: %d Found. Details Are As Follows.\n", bookIDToBeSearched);
                        printlnSheetTitle();
                        printlnBook(*searchBookByBookID(booklist, bookIDToBeSearched));
                    }
                    pauseConsole();
                    break;

                case 5:
                    printf("Please Input The Name of The Book To Be Searched: ");
                    scanf("%s", bookNameToBeSearched);
                    searchBookByName(booklist, bookNameToBeSearched);
                    pauseConsole();
                    break;

                case 6:
                    printlnSheetTitle();
                    printallBook(booklist);
                    pauseConsole();
                    break;

                case 7:
                    exitLibrary();
                    break;
            }
        }
    }
    return 0;
}