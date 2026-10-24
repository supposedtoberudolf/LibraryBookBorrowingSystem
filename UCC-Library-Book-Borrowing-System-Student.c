#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#define BOOK_QUANTITY 12
#define STUDENT_COUNT 6

typedef struct {
    
    int ID;
    char title[70];
    int year;
    char author[90];
    char status[20];

} Book;

typedef struct {
    
    char ID[10];
    char name[30];
    char program[6];
    char yearSec[5];
    
} Student;

void printLoadingDots(const char *message, int dotCount, int delayMs) {
    
    printf("\n%s", message);

    for (int i = 0; i < dotCount; i++) {
        Sleep(delayMs);
        printf(" .");
    }
    printf("\n");
}

int clearBuffer() {

    int extra = 0;                    

    while (getchar() != '\n') {
        extra = 1;                    
    }

    return extra;
}

int displayMainMenu() {

    int choice = 0;
    int result = 0;
    int extra = 0;

    do
    {
        printf("+-----------------------------------------------------------------------+\n");
        printf("|            ----- UCC LIBRARY BOOK BORROWING SYSTEM -----              |\n");
        printf("+-----------------------------------------------------------------------+\n");
        printf("|                                                                       |\n");
        printf("|        [1] CHECK LIBRARY BOOKS              [3] EXIT                  |\n");
        printf("|                                                                       |\n");
        printf("|        [2] BORROW BOOKS                                               |\n");
        printf("|                                                                       |\n");
        printf("+-----------------------------------------------------------------------+\n");

        printf("\nSELECT FROM (1-3): ");
        result = scanf("%d", &choice);
        extra = clearBuffer();

        if (result != 1 || extra == 1) {
            system("cls");
            printf("\nINPUT MUST CONTAIN NUMBER ONLY\nPLEASE TRY AGAIN\n\n");
        }
        else if (choice > 3 || choice < 1) {
            system("cls");
            printf("\nINVALID SELECTION!\nPLEASE TRY AGAIN\n\n");
        }
        else break;

    } while (1);
    
    return choice;
}

void displayBooks(Book books[10]) {

    system("cls");
    printf("+-----------------------------------------------------------------------+\n");
    printf("|                        LIBRARY BOOK CATALOG                           |\n");
    printf("+-----------------------------------------------------------------------+\n");
    for (int i = 0; i < BOOK_QUANTITY; i++) {
        printf("+-----------------------------------------------------------------------+\n");
        printf("BOOK ID  : [%d]\nTITLE    : %s\nAUTHOR   : %s\nYEAR     : %d\nSTATUS   : %s\n", books[i].ID, books[i].title, books[i].author, books[i].year, books[i].status);
        printf("+-----------------------------------------------------------------------+\n");
        printf("\n");
    }

    printf("\nPRESS ANYTHING TO RETURN TO MAIN MENU");
    getch();
    printLoadingDots("\nLOADING", 4, 500);
    system("cls");
}

void borrowBook(Book books[10], Student student[STUDENT_COUNT]) {

    int index = 0, choice = 0, isAvailable = 0, isFound = 0, isBack = 0;
    int isValid = 0, isVerified = 0, isCancelled = 0, isStudentFound = 0;
    int studentIndex = 0, attempts = 0, length = 0;
    int result[4] = {0};
    int extra[4] = {0};
    char confirm = '\0';   
    char verify = '\0';
    char studentID[10] = "";

    do
    {
        isBack = 0;
        isAvailable = 0;
        isCancelled = 0;
        isVerified = 0;
        attempts = 0;

        system("cls");
        printf("+-----------------------------------------------------------------------+\n");
        printf("|                            LIBRARY BOOKS                              |\n");
        printf("+-----------------------------------------------------------------------+\n");
        for (int i = 0; i < BOOK_QUANTITY; i++) {
            printf("+-----------------------------------------------------------------------+\n");
            printf("BOOK ID  : [%d]\nTITLE    : %s\nAUTHOR   : %s\nYEAR     : %d\nSTATUS   : %s\n", books[i].ID, books[i].title, books[i].author, books[i].year, books[i].status);
            printf("+-----------------------------------------------------------------------+\n");
            printf("\n");
        }
        
        do
        {
            printf("\nENTER THE ID OF THE BOOK YOU WANT TO BORROW (0 TO CANCEL): ");
            result[0] = scanf("%d", &choice);
            extra[0] = clearBuffer();

            isFound = 0;
            for (int i = 0; i < BOOK_QUANTITY; i++) {
                if (choice == books[i].ID) isFound = 1;
            }

                if (result[0] != 1 || extra[0] == 1) {
                    printf("\nINPUT MUST CONTAIN NUMBER ONLY\nPLEASE TRY AGAIN\n");
                    printLoadingDots("LOADING", 4, 500);
                }
                else if (choice == 0) {
                    printLoadingDots("LOADING", 4, 500);
                    system("cls");
                    break;
                }
                else if (isFound == 0) {
                    printf("\nINVALID BOOK ID\nPLEASE TRY AGAIN\n");
                    printLoadingDots("LOADING", 4, 500);
                }    
                else break;

        } while (1);
        
        if (isFound == 1) {

            for (int i = 0; i < BOOK_QUANTITY; i++) {
                if (choice == books[i].ID) {
                    if (strcmp(books[i].status, "AVAILABLE") == 0) {
                        isAvailable = 1;
                        index = i;
                    }
                    
                }
                
            }

            printLoadingDots("LOADING", 4, 500);

            if (isAvailable == 0) {
                printf("\nSORRY, THE BOOK IS UNAVAILABLE, PLEASE TRY AGAIN LATER.\n");
                printf("\nPRESS ANYTHING TO RETURN TO MAIN MENU");
                getch();
                printLoadingDots("LOADING", 4, 500);
                system("cls");
            }
            else {

                printf("\nBOOK IS AVAILABLE\n");
                printLoadingDots("LOADING", 4, 500);

                do
                {
                    system("cls");

                    do
                    {
                        printf("+-----------------------------------------------------------------------+\n");
                        printf("|                         STUDENT VERIFICATION                          |\n");
                        printf("+-----------------------------------------------------------------------+\n");

                        printf("\nPLEASE ENTER YOUR STUDENT NUMBER TO CONTINUE BORROWING (FOR EX. 20260077) | (0 TO CANCEL): ");
                        studentID[0] = '\0';
                        result[2] = scanf("%9s", studentID);
                        extra[2] = clearBuffer();

                        isValid = 1;
                        length = 0;
                        for (int i = 0; studentID[i] != '\0'; i++) {
                            length++;
                            if (studentID[i] < '0' || studentID[i] > '9') isValid = 0;
                        }

                        if (result[2] != 1 || extra[2] == 1) {
                            system("cls");
                            printf("\nSTUDENT NUMBER MUST BE 8 DIGITS\nPLEASE TRY AGAIN\n\n");
                        }
                        else if (strcmp(studentID, "0") == 0) {
                            isCancelled = 1;
                            break;
                        }
                        else if (isValid == 0 || length != 8) {
                            system("cls");
                            printf("\nSTUDENT NUMBER MUST BE 8 DIGITS\nPLEASE TRY AGAIN\n\n");
                        }
                        else {
                            isStudentFound = 0;
                            for (int i = 0; i < STUDENT_COUNT; i++) {
                                if (strcmp(studentID, student[i].ID) == 0) {
                                    isStudentFound = 1;
                                    studentIndex = i;
                                }
                            }

                            if (isStudentFound == 1) break;

                            attempts++;
                            system("cls");
                            if (attempts == 3) {
                                printf("\nTOO MANY FAILED ATTEMPTS\n");
                                isCancelled = 1;
                                break;
                            }
                            printf("\nSTUDENT NUMBER NOT FOUND\nPLEASE CHECK YOUR STUDENT NUMBER AND TRY AGAIN\n");
                            printf("ATTEMPTS LEFT: %d\n\n", 3 - attempts);
                        }

                    } while (1);

                    if (isCancelled == 1) {
                        printLoadingDots("RETURNING TO MAIN MENU", 4, 500);
                        system("cls");
                        break;
                    }

                    system("cls");

                    do
                    {
                        printf("+-----------------------------------------------------------------------+\n");
                        printf("|                         STUDENT INFORMATION                           |\n");
                        printf("+-----------------------------------------------------------------------+\n");
                        printf("|                                                                       |\n");
                        printf("|  NAME    : %-58.58s |\n", student[studentIndex].name);
                        printf("|  STUD. ID: %-58s |\n", student[studentIndex].ID);
                        printf("|  YEAR/SEC: %-58.58s |\n", student[studentIndex].yearSec);
                        printf("|  PROGRAM : %-58.58s |\n", student[studentIndex].program);
                        printf("|                                                                       |\n");
                        printf("+-----------------------------------------------------------------------+\n");

                        printf("\nIS THIS YOU?\n");
                        printf("PRESS [Y] TO CONFIRM(N TO ENTER AGAIN): ");
                        result[3] = scanf(" %c", &verify);
                        extra[3] = clearBuffer();
                        verify = toupper(verify);

                        if (result[3] != 1 || extra[3] == 1) {
                            system("cls");
                            printf("\nPLEASE ENTER Y OR N ONLY\nPLEASE TRY AGAIN\n\n");
                        }
                        else if (verify == 'N') break;

                        else if (verify != 'Y') {
                            system("cls");
                            printf("\nINVALID INPUT\nPLEASE TRY AGAIN\n\n");
                        }
                        else {
                            isVerified = 1;
                            break;
                        }

                    } while (1);

                } while (isVerified == 0);

                if (isCancelled == 0) {

                    system("cls");

                    do
                    {
                        
                        printf("+-----------------------------------------------------------------------+\n");
                        printf("|                        BORROWING  CONFIRMATION                        |\n");
                        printf("+-----------------------------------------------------------------------+\n");
                        printf("|                               DETAILS                                 |\n");
                        printf("|                                                                       |\n");
                        printf("|  NAME    : %-58.58s |\n", student[studentIndex].name);
                        printf("|  STUD. ID: %-58s |\n", student[studentIndex].ID);
                        printf("|  YEAR/SEC: %-58.58s |\n", student[studentIndex].yearSec);
                        printf("|  PROGRAM : %-58.58s |\n", student[studentIndex].program);
                        printf("|  BOOK ID : %-58d |\n", books[index].ID);                                           
                        printf("|  TITLE   : %-58.58s |\n", books[index].title);
                        printf("|  AUTHOR  : %-58.58s |\n", books[index].author);
                        printf("|  YEAR    : %-58d |\n", books[index].year);
                        printf("|                                                                       |\n");
                        printf("+-----------------------------------------------------------------------+\n");

                        printf("\nPRESS [Y] TO CONFIRM(N TO GO BACK): ");
                        result[1] = scanf(" %c", &confirm);
                        extra[1] = clearBuffer();
                        confirm = toupper(confirm);

                        if (result[1] != 1 || extra[1] == 1) {
                            system("cls");
                            printf("\nPLEASE ENTER Y OR N ONLY\nPLEASE TRY AGAIN\n\n");
                        }
                        else if (confirm == 'N') {
                            system("cls");
                            printLoadingDots("RETURNING TO BOOK SELECTION", 4, 500);
                            system("cls");
                            isBack = 1;
                            break;
                        }
                        else if ((confirm != 'Y')) {
                            system("cls");
                            printf("\nINVALID INPUT\nPLEASE TRY AGAIN\n\n");
                        }
                        else {
                            strcpy(books[index].status, "UNAVAILABLE");
                            printLoadingDots("PROCESSING YOUR REQUEST", 4, 500);
                            system("cls");
                            printf("+-----------------------------------------------------------------------+\n");
                            printf("|                YOU HAVE SUCCESSFULLY BORROWED A BOOK                  |\n");
                            printf("+-----------------------------------------------------------------------+\n");
                            printf("|                               DETAILS                                 | \n");
                            printf("|                                                                       | \n");
                            printf("|  NAME    : %-58.58s |\n", student[studentIndex].name);
                            printf("|  STUD. ID: %-58s |\n", student[studentIndex].ID);
                            printf("|  YEAR/SEC: %-58.58s |\n", student[studentIndex].yearSec);
                            printf("|  PROGRAM : %-58.58s |\n", student[studentIndex].program);
                            printf("|  BOOK ID : %-58d |\n", books[index].ID);                                           
                            printf("|  TITLE   : %-58.58s |\n", books[index].title);
                            printf("|  AUTHOR  : %-58.58s |\n", books[index].author);
                            printf("|  YEAR    : %-58d |\n", books[index].year);
                            printf("|                                                                       | \n");
                            printf("+-----------------------------------------------------------------------+\n");

                            printf("\nPRESS ANYTHING TO CONTINUE");
                            getch();
                            printLoadingDots("\nLOADING", 4, 500);
                            system("cls");
                            break;
                        }

                    } while (1);

                }

            }
     
        }

    } while (isBack == 1);
   
}

int main() {
    
    Book books[BOOK_QUANTITY] = {
        {
            .ID = 101,
            .title = "The C Programming Language (Second Edition)",
            .author = "Brian W. Kernighan and Dennis M. Ritchie",
            .year = 1988,
            .status = "AVAILABLE"
        },
        {
            .ID = 102,
            .title = "The C Programming Language (Second Edition)",
            .author = "Brian W. Kernighan and Dennis M. Ritchie",
            .year = 1988,
            .status = "AVAILABLE"
        },
        {
            .ID = 103,
            .title = "The C Programming Language (Second Edition)",
            .author = "Brian W. Kernighan and Dennis M. Ritchie",
            .year = 1988,
            .status = "AVAILABLE"
        },
        {
            .ID = 201,
            .title = "Introduction to Programming Using Java",
            .author = "David J. Eck",
            .year = 2006,
            .status = "AVAILABLE"
        },
        {
            .ID = 301,
            .title = "Fundamentals of Database Management Systems (Third Edition)",
            .author = "Mark L. Gillenson",
            .year = 2023,
            .status = "AVAILABLE"
        },
        {
            .ID = 401,
            .title = "Calculus and Analytic Geometry (Ninth Edition)",
            .author = "George B. Thomas, Ross L. Finney, and Maurice D. Weir",
            .year = 1996,
            .status = "AVAILABLE"
        },
        {
            .ID = 501,
            .title = "Cybersecurity Fundamentals",
            .author = "Dr. Sarita Devanand Sanap",
            .year = 2026,
            .status = "AVAILABLE"
        },
        {
            .ID = 601,
            .title = "Philippine Medical Technology Laws and Bioethics",
            .author = "Sally C. Suba and Giovanni De Jesus Milanez",
            .year = 2017,
            .status = "AVAILABLE"
        },
        {
            .ID = 701,
            .title = "National Service Training Program: Civic Welfare Training Services",
            .author = "Arnold L. Espinas, Miguel R. Santos, and Marilyn T. de Jesus",
            .year = 2011,
            .status = "AVAILABLE"
        },
        {
            .ID = 801,
            .title = "Discrete Mathematics and Its Applications",
            .author = "Kenneth H. Rosen",
            .year = 2019,
            .status = "AVAILABLE"
        },
        {
            .ID = 901,
            .title = "Computer Science: An Overview",
            .author = "J. Glenn Brookshear and Dennis Brylow",
            .year = 2019,
            .status = "AVAILABLE"
        },
        {
            .ID = 1001,
            .title = "The Finance Book",
            .author = "Stuart Warner and Si Hussain",
            .year = 2017,
            .status = "AVAILABLE"
        },
    };

    Student student[STUDENT_COUNT] = {
        {
            .ID = "20260068",
            .name = "Rheyniel G. Santos",
            .program = "BSIT",
            .yearSec = "2-A"
        },
        {
            .ID = "20260079",
            .name = "Rudolf L. Victoria",
            .program = "BSCS",
            .yearSec = "1-A"
        },
        {
            .ID = "20260724",
            .name = "Jasmine L. Navarro",
            .program = "BSEMC",
            .yearSec = "1-B"
        },
        {
            .ID = "20260725",
            .name = "Yohan B. Escaño",
            .program = "BSEMC",
            .yearSec = "2-B"
        },
        {
            .ID = "20260369",
            .name = "Nostalgia L. Aguirre",
            .program = "BSIS",
            .yearSec = "1-A"
        },
        {
            .ID = "20260699",
            .name = "Joshua Daniel B. Dominno",
            .program = "BSCS",
            .yearSec = "1-A"
        }
    };

    int choice = 0;
    
    do
    {
        choice = displayMainMenu();

            if (choice == 1) displayBooks(books); 

            else if (choice == 2) borrowBook(books, student);

    } while (choice != 3);
    
    system("cls");  
    printf("THANK YOU FOR USING UCC LIBRARY! GOODBYE.\n\n");

    return 0;
}
