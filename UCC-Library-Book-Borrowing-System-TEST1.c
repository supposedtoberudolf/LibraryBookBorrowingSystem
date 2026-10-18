#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#define BOOK_QUANTITY 12

typedef struct {
    
    int ID;
    char title[70];
    int year;
    char author[90];
    char status[20];

} Book;

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

void borrowBook(Book books[10]) {

    int index = 0, choice = 0, isAvailable = 0, isFound = 0, isValid = 0, isEditing = 0;
    int result[7] = {0};
    int extra[7] = {0};
    int studentID = 0;
    char confirm = '\0';   
    char editChoice = '\0';
    char borrower[50];
    char yearSection[10];
    char program[10];

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

            if (result[0] != 1 || extra[0] == 1) printf("\nINPUT MUST CONTAIN NUMBER ONLY\nPLEASE TRY AGAIN\n");
            
            else if (choice == 0) {
                printLoadingDots("LOADING", 4, 500);
                system("cls");
                break;
            }
            else if (isFound == 0) {
                printf("\nINVALID BOOK ID\nPLEASE TRY AGAIN");
                Sleep(2000);
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

            do
            {
                isEditing = 0;

                system("cls");

                do
                {
                    printf("+-----------------------------------------------------------------------+\n");
                    printf("|                         STUDENT INFORMATION                           |\n");
                    printf("+-----------------------------------------------------------------------+\n");

                    printf("\nENTER YOUR FULL NAME: ");
                    borrower[0] = '\0';
                    result[2] = scanf(" %49[^\n]", borrower);
                    extra[2] = clearBuffer();

                    isValid = 1;
                    for (int i = 0; borrower[i] != '\0'; i++) {
                        if (borrower[i] >= '0' && borrower[i] <= '9') isValid = 0;
                    }

                    if (result[2] != 1 || extra[2] == 1) {
                        system("cls");
                        printf("\nNAME MUST NOT EXCEED 49 CHARACTERS\nPLEASE TRY AGAIN\n\n");
                    }
                    else if (isValid == 0) {
                        system("cls");
                        printf("\nNAME MUST NOT CONTAIN NUMBERS\nPLEASE TRY AGAIN\n\n");
                    }
                    else break;

                } while (1);

                system("cls");

                do
                {
                    printf("+-----------------------------------------------------------------------+\n");
                    printf("|                         STUDENT INFORMATION                           |\n");
                    printf("+-----------------------------------------------------------------------+\n");

                    printf("\nENTER YOUR STUDENT ID (EXAMPLE: 20260079): ");
                    result[6] = scanf("%d", &studentID);
                    extra[6] = clearBuffer();

                    if (result[6] != 1 || extra[6] == 1) {
                        system("cls");
                        printf("\nINPUT MUST CONTAIN NUMBER ONLY\nPLEASE TRY AGAIN\n\n");
                    }
                    else if (studentID < 10000000 || studentID > 99999999) {
                        system("cls");
                        printf("\nSTUDENT ID MUST BE 8 DIGITS\nPLEASE TRY AGAIN\n\n");
                    }
                    else break;

                } while (1);

                system("cls");

                do
                {
                    printf("+-----------------------------------------------------------------------+\n");
                    printf("|                         STUDENT INFORMATION                           |\n");
                    printf("+-----------------------------------------------------------------------+\n");

                    printf("\nENTER YOUR YEAR AND SECTION (EXAMPLE: 1-A): ");
                    yearSection[0] = '\0';
                    result[3] = scanf("%10s", yearSection);
                    extra[3] = clearBuffer();

                    if (result[3] != 1 || extra[3] == 1) {
                        system("cls");
                        printf("\nYEAR AND SECTION MUST NOT EXCEED 10 CHARACTERS\nPLEASE TRY AGAIN\n\n");
                    }
                    else {
                        for (int i = 0; yearSection[i] != '\0'; i++) {
                            yearSection[i] = toupper(yearSection[i]);
                        }
                        break;
                    }

                } while (1);

                system("cls");

                do
                {
                    printf("+-----------------------------------------------------------------------+\n");
                    printf("|                         STUDENT INFORMATION                           |\n");
                    printf("+-----------------------------------------------------------------------+\n");

                    printf("\nENTER YOUR PROGRAM (EXAMPLE: BSCS): ");
                    program[0] = '\0';
                    result[4] = scanf("%10s", program);
                    extra[4] = clearBuffer();

                    if (result[4] != 1 || extra[4] == 1) {
                        system("cls");
                        printf("\nPROGRAM MUST NOT EXCEED 10 CHARACTERS\nPLEASE TRY AGAIN\n\n");
                    }
                    else {
                        for (int i = 0; program[i] != '\0'; i++) {
                            program[i] = toupper(program[i]);
                        }
                        break;
                    }

                } while (1);

                system("cls");

                do
                {
                    printf("+-----------------------------------------------------------------------+\n");
                    printf("|                         INFORMATION SUMMARY                           |\n");
                    printf("+-----------------------------------------------------------------------+\n");
                    printf("|                                                                       |\n");
                    printf("|  NAME    : %-58.58s |\n", borrower);
                    printf("|  STUD. ID: %-58d |\n", studentID);
                    printf("|  YEAR/SEC: %-58.58s |\n", yearSection);
                    printf("|  PROGRAM : %-58.58s |\n", program);
                    printf("|                                                                       |\n");
                    printf("+-----------------------------------------------------------------------+\n");

                    printf("\nDO YOU WANT TO EDIT YOUR INFORMATION?\n");
                    printf("PRESS [Y] TO EDIT(N TO CONTINUE): ");
                    result[5] = scanf(" %c", &editChoice);
                    extra[5] = clearBuffer();
                    editChoice = toupper(editChoice);

                    if (result[5] != 1 || extra[5] == 1) {
                        system("cls");
                        printf("\nPLEASE ENTER Y OR N ONLY\nPLEASE TRY AGAIN\n\n");
                    }
                    else if (editChoice == 'Y') {
                        isEditing = 1;
                        break;
                    }
                    else if (editChoice != 'N') {
                        system("cls");
                        printf("\nINVALID INPUT\nPLEASE TRY AGAIN\n\n");
                    }
                    else break;

                } while (1);

            } while (isEditing == 1);

            system("cls");

            do
            {
                
                printf("+-----------------------------------------------------------------------+\n");
                printf("|                        BORROWING  CONFIRMATION                        |\n");
                printf("+-----------------------------------------------------------------------+\n");
                printf("|                               DETAILS                                 |\n");
                printf("|                                                                       |\n");
                printf("|  NAME    : %-58.58s |\n", borrower);
                printf("|  STUD. ID: %-58d |\n", studentID);
                printf("|  YEAR/SEC: %-58.58s |\n", yearSection);
                printf("|  PROGRAM : %-58.58s |\n", program);
                printf("|  BOOK ID : %-58d |\n", books[index].ID);                                           
                printf("|  TITLE   : %-58.58s |\n", books[index].title);
                printf("|  AUTHOR  : %-58.58s |\n", books[index].author);
                printf("|  YEAR    : %-58d |\n", books[index].year);
                printf("|                                                                       |\n");
                printf("+-----------------------------------------------------------------------+\n");

                printf("\nPRESS [Y] TO CONFIRM(N TO CANCEL): ");
                result[1] = scanf(" %c", &confirm);
                extra[1] = clearBuffer();
                confirm = toupper(confirm);

                if (result[1] != 1 || extra[1] == 1) {
                    system("cls");
                    printf("\nPLEASE ENTER Y OR N ONLY\nPLEASE TRY AGAIN\n\n");
                }
                else if (confirm == 'N') {
                    system("cls");
                    printLoadingDots("RETURNING TO MAIN MENU", 4, 500);
                    system("cls");
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
                    printf("|  NAME    : %-58.58s |\n", borrower);
                    printf("|  STUD. ID: %-58d |\n", studentID);
                    printf("|  YEAR/SEC: %-58.58s |\n", yearSection);
                    printf("|  PROGRAM : %-58.58s |\n", program);
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

    int choice = 0;
    
    do
    {
        choice = displayMainMenu();

            if (choice == 1) displayBooks(books); 

            else if (choice == 2) borrowBook(books);

    } while (choice != 3);
    
    system("cls");  
    printf("THANK YOU FOR USING UCC LIBRARY! GOODBYE.\n\n");

    return 0;
}