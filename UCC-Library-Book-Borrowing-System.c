#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

typedef struct {
    
    int ID;
    char title[70];
    int year;
    char author[90];
    char status[20];

} Book;

void printLoadingDots(const char *message, int dotCount, int delayMs) {
    
    printf("\n%s", message);
    fflush(stdout);

    for (int i = 0; i < dotCount; i++) {
        Sleep(delayMs);
        printf(" .");
        fflush(stdout);
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
    for (int i = 0; i < 10; i++) {
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

    int index, choice, isAvailable = 0;
    int result[2] = {0};
    int extra[2] = {0};
    char confirm = '\0';   

    system("cls");
    printf("+-----------------------------------------------------------------------+\n");
    printf("|                            LIBRARY BOOKS                              |\n");
    printf("+-----------------------------------------------------------------------+\n");
    for (int i = 0; i < 10; i++) {
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

            if (result[0] != 1 || extra[0] == 1) printf("\nINPUT MUST CONTAIN NUMBER ONLY\nPLEASE TRY AGAIN\n");
            
            else if (choice == 0) {
                printLoadingDots("LOADING", 4, 500);
                system("cls");
                break;
            }
            else if (choice > 10 || choice < 1) {
                printf("\nINVALID BOOK ID\nPLEASE TRY AGAIN");
                Sleep(2000);
                printLoadingDots("LOADING", 4, 500);
            }    
            else break;

    } while (1);
    
    if ((choice <= 10) && (choice >= 1)) {

        for (int i = 0; i < 10; i++) {
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
   
            system("cls");

            do
            {
                
                printf("+-----------------------------------------------------------------------+\n");
                printf("|                        BORROWING  CONFIRMATION                        |\n");
                printf("+-----------------------------------------------------------------------+\n");
                printf("|                               DETAILS                                 | \n");
                printf("|                                                                       | \n");
                printf("|  BOOK ID : %-58d |\n", books[index].ID);                                           
                printf("|  TITLE   : %-58.58s |\n", books[index].title);
                printf("|  AUTHOR  : %-58.58s |\n", books[index].author);
                printf("|  YEAR    : %-58d |\n", books[index].year);
                printf("|                                                                       | \n");
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
                };

            } while (1);

        }
 
    }
   
    
}

int main() {
    
    Book books[10] = {
        {
            .ID = 1,
            .title = "The C Programming Language (Second Edition)",
            .author = "Brian W. Kernighan and Dennis M. Ritchie",
            .year = 1988,
            .status = "AVAILABLE"
        },
        {
            .ID = 2,
            .title = "Introduction to Programming Using Java",
            .author = "David J. Eck",
            .year = 2006,
            .status = "AVAILABLE"
        },
        {
            .ID = 3,
            .title = "Fundamentals of Database Management Systems (Third Edition)",
            .author = "Mark L. Gillenson",
            .year = 2023,
            .status = "AVAILABLE"
        },
        {
            .ID = 4,
            .title = "Calculus and Analytic Geometry (Ninth Edition)",
            .author = "George B. Thomas, Ross L. Finney, and Maurice D. Weir",
            .year = 1996,
            .status = "AVAILABLE"
        },
        {
            .ID = 5,
            .title = "Cybersecurity Fundamentals",
            .author = "Dr. Sarita Devanand Sanap",
            .year = 2026,
            .status = "AVAILABLE"
        },
        {
            .ID = 6,
            .title = "Philippine Medical Technology Laws and Bioethics",
            .author = "Sally C. Suba and Giovanni De Jesus Milanez",
            .year = 2017,
            .status = "AVAILABLE"
        },
        {
            .ID = 7,
            .title = "National Service Training Program: Civic Welfare Training Services",
            .author = "Arnold L. Espinas, Miguel R. Santos, and Marilyn T. de Jesus",
            .year = 2011,
            .status = "AVAILABLE"
        },
        {
            .ID = 8,
            .title = "Discrete Mathematics and Its Applications",
            .author = "Kenneth H. Rosen",
            .year = 2019,
            .status = "AVAILABLE"
        },
        {
            .ID = 9,
            .title = "Computer Science: An Overview",
            .author = "J. Glenn Brookshear and Dennis Brylow",
            .year = 2019,
            .status = "AVAILABLE"
        },
        {
            .ID = 10,
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