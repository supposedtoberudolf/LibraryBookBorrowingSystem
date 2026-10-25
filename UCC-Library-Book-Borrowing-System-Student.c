#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

#define BOOK_QUANTITY 12
#define STUDENT_COUNT 6

typedef struct {
    char accessionNo[8];
    char ddc[15];
    char callNo[25];
    char title[80];
    int year;
    char author[100];
    char status[20];
} Book;

typedef struct {
    char ID[11];
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

    do {
        printf("+-----------------------------------------------------------------------+\n");
        printf("|               ----- LIBRARY BOOK BORROWING SYSTEM -----               |\n");
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
            printf("\nINPUT MUST CONTAIN NUMBER ONLY. PLEASE TRY AGAIN.\n\n");
        }
        else if (choice > 3 || choice < 1) {
            system("cls");
            printf("\nINVALID SELECTION. PLEASE TRY AGAIN.\n\n");
        }
        else {
            break;
        }

    } while (1);

    return choice;
}

void displayBooks(Book books[BOOK_QUANTITY]) {
    system("cls");

    printf("+-----------------------------------------------------------------------+\n");
    printf("|                        LIBRARY BOOK CATALOG                           |\n");
    printf("+-----------------------------------------------------------------------+\n");

    for (int i = 0; i < BOOK_QUANTITY; i++) {
        printf("|                                                                       |\n");
        printf("|  ACCESSION NO.: %-54s|\n", books[i].accessionNo);
        printf("|  DDC          : %-54s|\n", books[i].ddc);
        printf("|  CALL NO.     : %-54s|\n", books[i].callNo);
        printf("|  TITLE        : %-54.54s|\n", books[i].title);
        printf("|  AUTHOR       : %-54.54s|\n", books[i].author);
        printf("|  YEAR         : %-54d|\n", books[i].year);
        printf("|  STATUS       : %-54s|\n", books[i].status);
        printf("|                                                                       |\n");
        printf("+-----------------------------------------------------------------------+\n");
    }

    printf("\nPRESS ANYTHING TO RETURN TO MAIN MENU");
    getch();
    printLoadingDots("\nLOADING", 4, 500);
    system("cls");
}

void borrowBook(Book books[BOOK_QUANTITY], Student student[STUDENT_COUNT]) {
    int index = 0, isAvailable = 0, isFound = 0, isBack = 0;
    int isValid = 0, isVerified = 0, isCancelled = 0, isStudentFound = 0;
    int isBookConfirmed = 0;
    int studentIndex = 0, attempts = 0, length = 0;
    int result[5] = {0};
    int extra[5] = {0};

    char confirm = '\0';
    char verify = '\0';
    char bookVerify = '\0';
    char studentID[11] = "";
    char accessionNo[8] = "";

    do {
        isBack = 0;
        isAvailable = 0;
        isCancelled = 0;
        isVerified = 0;
        isBookConfirmed = 0;
        attempts = 0;

        system("cls");

        printf("+-----------------------------------------------------------------------+\n");
        printf("|                            LIBRARY BOOKS                              |\n");
        printf("+-----------------------------------------------------------------------+\n");

        for (int i = 0; i < BOOK_QUANTITY; i++) {
            printf("|                                                                       |\n");
            printf("|  ACCESSION NO.: %-54s|\n", books[i].accessionNo);
            printf("|  DDC          : %-54s|\n", books[i].ddc);
            printf("|  CALL NO.     : %-54s|\n", books[i].callNo);
            printf("|  TITLE        : %-54.54s|\n", books[i].title);
            printf("|  AUTHOR       : %-54.54s|\n", books[i].author);
            printf("|  YEAR         : %-54d|\n", books[i].year);
            printf("|  STATUS       : %-54s|\n", books[i].status);
            printf("|                                                                       |\n");
            printf("+-----------------------------------------------------------------------+\n");
        }

        do {
            printf("\nENTER THE ACCESSION NUMBER OF THE BOOK YOU WANT TO BORROW (0 TO CANCEL): ");

            accessionNo[0] = '\0';
            result[0] = scanf("%7s", accessionNo);
            extra[0] = clearBuffer();

            isFound = 0;

            if (strcmp(accessionNo, "0") != 0) {
                for (int i = 0; i < BOOK_QUANTITY; i++) {
                    if (strcmp(accessionNo, books[i].accessionNo) == 0) {
                        isFound = 1;
                        index = i;
                        break;
                    }
                }
            }

            if (result[0] != 1 || extra[0] == 1) {
                printf("\nINVALID ACCESSION NUMBER. PLEASE TRY AGAIN.\n");
                printLoadingDots("LOADING", 4, 500);
            }
            else if (strcmp(accessionNo, "0") == 0) {
                printLoadingDots("LOADING", 4, 500);
                system("cls");
                break;
            }
            else if (isFound == 0) {
                printf("\nINVALID ACCESSION NUMBER. PLEASE TRY AGAIN.\n");
                printLoadingDots("LOADING", 4, 500);
            }
            else {
                break;
            }

        } while (1);

        if (isFound == 1) {
            isAvailable = 0;

            if (strcmp(books[index].status, "AVAILABLE") == 0) {
                isAvailable = 1;
            }

            printLoadingDots("LOADING", 4, 500);

            if (isAvailable == 0) {
                printf("\nSORRY, THE BOOK IS UNAVAILABLE. PLEASE TRY AGAIN LATER.\n");
                printf("\nPRESS ANYTHING TO RETURN TO MAIN MENU");
                getch();

                printLoadingDots("\nLOADING", 4, 500);
                system("cls");
            }
            else {
                printf("\nBOOK IS AVAILABLE.\n");
                printLoadingDots("LOADING", 4, 500);
                system("cls");

                do {
                    printf("+-----------------------------------------------------------------------+\n");
                    printf("|                          BOOK INFORMATION                             |\n");
                    printf("+-----------------------------------------------------------------------+\n");
                    printf("|                                                                       |\n");
                    printf("|  ACCESSION NO.: %-54s|\n", books[index].accessionNo);
                    printf("|  DDC          : %-54s|\n", books[index].ddc);
                    printf("|  CALL NO.     : %-54s|\n", books[index].callNo);
                    printf("|  TITLE        : %-54.54s|\n", books[index].title);
                    printf("|  AUTHOR       : %-54.54s|\n", books[index].author);
                    printf("|  YEAR         : %-54d|\n", books[index].year);
                    printf("|  STATUS       : %-54s|\n", books[index].status);
                    printf("|                                                                       |\n");
                    printf("+-----------------------------------------------------------------------+\n");

                    printf("\nIS THIS THE BOOK YOU WANT TO BORROW?\n");
                    printf("PRESS [Y] TO CONFIRM (N TO CHOOSE AGAIN): ");

                    result[4] = scanf(" %c", &bookVerify);
                    extra[4] = clearBuffer();
                    bookVerify = toupper((unsigned char)bookVerify);

                    if (result[4] != 1 || extra[4] == 1) {
                        system("cls");
                        printf("\nPLEASE ENTER Y OR N ONLY. PLEASE TRY AGAIN.\n\n");
                    }
                    else if (bookVerify == 'N') {
                        system("cls");
                        printLoadingDots("RETURNING TO BOOK SELECTION", 4, 500);
                        system("cls");

                        isBack = 1;
                        break;
                    }
                    else if (bookVerify != 'Y') {
                        system("cls");
                        printf("\nINVALID INPUT. PLEASE TRY AGAIN.\n\n");
                    }
                    else {
                        isBookConfirmed = 1;
                        break;
                    }

                } while (1);

                if (isBookConfirmed == 1) {
                    do {
                        system("cls");

                        do {
                            printf("+-----------------------------------------------------------------------+\n");
                            printf("|                         STUDENT VERIFICATION                          |\n");
                            printf("+-----------------------------------------------------------------------+\n");

                            printf("\nPLEASE ENTER YOUR STUDENT NUMBER TO CONTINUE BORROWING\n");
                            printf("(FOR EX. 20260143-N) | (0 TO CANCEL): ");

                            studentID[0] = '\0';
                            result[2] = scanf("%10s", studentID);
                            extra[2] = clearBuffer();

                            if (strcmp(studentID, "0") == 0) {
                                isCancelled = 1;
                                break;
                            }

                            length = strlen(studentID);
                            isValid = 1;

                            if (length != 10) {
                                isValid = 0;
                            }
                            else {
                                for (int i = 0; i < 8; i++) {
                                    if (!isdigit((unsigned char)studentID[i])) {
                                        isValid = 0;
                                    }
                                }

                                if (studentID[8] != '-') {
                                    isValid = 0;
                                }

                                studentID[9] = toupper((unsigned char)studentID[9]);

                                if (studentID[9] != 'N') {
                                    isValid = 0;
                                }
                            }

                            if (result[2] != 1 || extra[2] == 1 || isValid == 0) {
                                attempts++;
                                system("cls");

                                if (attempts == 5) {
                                    printf("\nTOO MANY FAILED ATTEMPTS.\n");
                                    printf("THE SYSTEM WILL NOW TERMINATE.\n");

                                    printLoadingDots("TERMINATING SYSTEM", 4, 500);

                                    system("cls");
                                    printf("THANK YOU FOR USING UCC LIBRARY. GOODBYE.\n\n");

                                    exit(0);
                                }

                                printf("\nINVALID STUDENT NUMBER FORMAT. PLEASE TRY AGAIN.\n");
                                printf("PLEASE USE FORMAT: 20260143-N\n");
                                printf("ATTEMPTS LEFT: %d\n\n", 5 - attempts);
                            }
                            else {
                                isStudentFound = 0;

                                for (int i = 0; i < STUDENT_COUNT; i++) {
                                    if (strcmp(studentID, student[i].ID) == 0) {
                                        isStudentFound = 1;
                                        studentIndex = i;
                                        break;
                                    }
                                }

                                if (isStudentFound == 1) {
                                    break;
                                }

                                attempts++;
                                system("cls");

                                if (attempts == 5) {
                                    printf("\nTOO MANY FAILED ATTEMPTS.\n");
                                    printf("THE SYSTEM WILL NOW TERMINATE.\n");

                                    printLoadingDots("TERMINATING SYSTEM", 4, 500);

                                    system("cls");
                                    printf("THANK YOU FOR USING UCC LIBRARY. GOODBYE.\n\n");

                                    exit(0);
                                }

                                printf("\nSTUDENT NUMBER NOT FOUND. PLEASE TRY AGAIN.\n");
                                printf("PLEASE CHECK YOUR STUDENT NUMBER.\n");
                                printf("ATTEMPTS LEFT: %d\n\n", 5 - attempts);
                            }

                        } while (1);

                        if (isCancelled == 1) {
                            printLoadingDots("RETURNING TO MAIN MENU", 4, 500);
                            system("cls");
                            break;
                        }

                        system("cls");

                        do {
                            printf("+-----------------------------------------------------------------------+\n");
                            printf("|                         STUDENT INFORMATION                           |\n");
                            printf("+-----------------------------------------------------------------------+\n");
                            printf("|                                                                       |\n");
                            printf("|  NAME         : %-54.54s|\n", student[studentIndex].name);
                            printf("|  STUD. ID     : %-54s|\n", student[studentIndex].ID);
                            printf("|  YEAR/SEC     : %-54.54s|\n", student[studentIndex].yearSec);
                            printf("|  PROGRAM      : %-54.54s|\n", student[studentIndex].program);
                            printf("|                                                                       |\n");
                            printf("+-----------------------------------------------------------------------+\n");

                            printf("\nIS THIS YOU?\n");
                            printf("PRESS [Y] TO CONFIRM (N TO ENTER AGAIN): ");

                            result[3] = scanf(" %c", &verify);
                            extra[3] = clearBuffer();
                            verify = toupper((unsigned char)verify);

                            if (result[3] != 1 || extra[3] == 1) {
                                system("cls");
                                printf("\nPLEASE ENTER Y OR N ONLY. PLEASE TRY AGAIN.\n\n");
                            }
                            else if (verify == 'N') {
                                break;
                            }
                            else if (verify != 'Y') {
                                system("cls");
                                printf("\nINVALID INPUT. PLEASE TRY AGAIN.\n\n");
                            }
                            else {
                                isVerified = 1;
                                break;
                            }

                        } while (1);

                    } while (isVerified == 0);

                    if (isCancelled == 0) {
                        system("cls");

                        do {
                            printf("+-----------------------------------------------------------------------+\n");
                            printf("|                        BORROWING CONFIRMATION                         |\n");
                            printf("+-----------------------------------------------------------------------+\n");
                            printf("|                               DETAILS                                 |\n");
                            printf("|                                                                       |\n");
                            printf("|  NAME         : %-54.54s|\n", student[studentIndex].name);
                            printf("|  STUD. ID     : %-54s|\n", student[studentIndex].ID);
                            printf("|  YEAR/SEC     : %-54.54s|\n", student[studentIndex].yearSec);
                            printf("|  PROGRAM      : %-54.54s|\n", student[studentIndex].program);
                            printf("|  ACCESSION NO.: %-54s|\n", books[index].accessionNo);
                            printf("|  DDC          : %-54s|\n", books[index].ddc);
                            printf("|  CALL NO.     : %-54s|\n", books[index].callNo);
                            printf("|  TITLE        : %-54.54s|\n", books[index].title);
                            printf("|  AUTHOR       : %-54.54s|\n", books[index].author);
                            printf("|  YEAR         : %-54d|\n", books[index].year);
                            printf("|                                                                       |\n");
                            printf("+-----------------------------------------------------------------------+\n");

                            printf("\nPRESS [Y] TO CONFIRM (N TO GO BACK): ");

                            result[1] = scanf(" %c", &confirm);
                            extra[1] = clearBuffer();
                            confirm = toupper((unsigned char)confirm);

                            if (result[1] != 1 || extra[1] == 1) {
                                system("cls");
                                printf("\nPLEASE ENTER Y OR N ONLY. PLEASE TRY AGAIN.\n\n");
                            }
                            else if (confirm == 'N') {
                                system("cls");
                                printLoadingDots("RETURNING TO BOOK SELECTION", 4, 500);
                                system("cls");

                                isBack = 1;
                                break;
                            }
                            else if (confirm != 'Y') {
                                system("cls");
                                printf("\nINVALID INPUT. PLEASE TRY AGAIN.\n\n");
                            }
                            else {
                                strcpy(books[index].status, "UNAVAILABLE");

                                printLoadingDots("PROCESSING YOUR REQUEST", 4, 500);
                                system("cls");

                                printf("+-----------------------------------------------------------------------+\n");
                                printf("|                YOU HAVE SUCCESSFULLY BORROWED A BOOK                  |\n");
                                printf("+-----------------------------------------------------------------------+\n");
                                printf("|                               DETAILS                                 |\n");
                                printf("|                                                                       |\n");
                                printf("|  NAME         : %-54.54s|\n", student[studentIndex].name);
                                printf("|  STUD. ID     : %-54s|\n", student[studentIndex].ID);
                                printf("|  YEAR/SEC     : %-54.54s|\n", student[studentIndex].yearSec);
                                printf("|  PROGRAM      : %-54.54s|\n", student[studentIndex].program);
                                printf("|  ACCESSION NO.: %-54s|\n", books[index].accessionNo);
                                printf("|  DDC          : %-54s|\n", books[index].ddc);
                                printf("|  CALL NO.     : %-54s|\n", books[index].callNo);
                                printf("|  TITLE        : %-54.54s|\n", books[index].title);
                                printf("|  AUTHOR       : %-54.54s|\n", books[index].author);
                                printf("|  YEAR         : %-54d|\n", books[index].year);
                                printf("|                                                                       |\n");
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
        }

    } while (isBack == 1);
}

int main() {
    Book books[BOOK_QUANTITY] = {
        {
            .accessionNo = "0001001",
            .ddc = "005.13",
            .callNo = "005.13-KER-001",
            .title = "The C Programming Language (Second Edition)",
            .author = "Brian W. Kernighan and Dennis M. Ritchie",
            .year = 1988,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0001002",
            .ddc = "005.13",
            .callNo = "005.13-KER-002",
            .title = "The C Programming Language (Second Edition)",
            .author = "Brian W. Kernighan and Dennis M. Ritchie",
            .year = 1988,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0001003",
            .ddc = "005.13",
            .callNo = "005.13-KER-003",
            .title = "The C Programming Language (Second Edition)",
            .author = "Brian W. Kernighan and Dennis M. Ritchie",
            .year = 1988,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0002001",
            .ddc = "150",
            .callNo = "150-MYE-001",
            .title = "Psychology (Twelfth Edition)",
            .author = "David G. Myers and C. Nathan DeWall",
            .year = 2018,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0003001",
            .ddc = "220.6",
            .callNo = "220.6-FEE-001",
            .title = "How to Read the Bible for All Its Worth (Fourth Edition)",
            .author = "Gordon D. Fee and Douglas Stuart",
            .year = 2014,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0004001",
            .ddc = "330",
            .callNo = "330-MAN-001",
            .title = "Principles of Economics (Ninth Edition)",
            .author = "N. Gregory Mankiw",
            .year = 2021,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0005001",
            .ddc = "420.03",
            .callNo = "420.03-CRY-001",
            .title = "The Cambridge Encyclopedia of the English Language (Third Edition)",
            .author = "David Crystal",
            .year = 2018,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0006001",
            .ddc = "515.15",
            .callNo = "515.15-THO-001",
            .title = "Calculus and Analytic Geometry (Ninth Edition)",
            .author = "George B. Thomas Jr., Ross L. Finney, with Maurice D. Weir",
            .year = 1996,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0007001",
            .ddc = "344.041599",
            .callNo = "344.041599-SUB-001",
            .title = "Philippine Medical Technology Laws and Bioethics",
            .author = "Sally C. Suba and Giovanni De Jesus Milanez",
            .year = 2017,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0008001",
            .ddc = "796.3",
            .callNo = "796.3-DK-001",
            .title = "The Sports Book (Fourth Edition)",
            .author = "DK",
            .year = 2013,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0009001",
            .ddc = "823",
            .callNo = "823-TOL-001",
            .title = "The Hobbit",
            .author = "J. R. R. Tolkien",
            .year = 1937,
            .status = "AVAILABLE"
        },
        {
            .accessionNo = "0010001",
            .ddc = "959.9",
            .callNo = "959.9-AGO-001",
            .title = "History of the Filipino People (Eighth Edition)",
            .author = "Teodoro A. Agoncillo",
            .year = 1990,
            .status = "AVAILABLE"
        }
    };

    Student student[STUDENT_COUNT] = {
        {
            .ID = "20260068-N",
            .name = "Rheyniel G. Santos",
            .program = "BSIT",
            .yearSec = "2-A"
        },
        {
            .ID = "20260079-N",
            .name = "Rudolf L. Victoria",
            .program = "BSCS",
            .yearSec = "1-A"
        },
        {
            .ID = "20260724-N",
            .name = "Jasmine L. Navarro",
            .program = "BSEMC",
            .yearSec = "1-B"
        },
        {
            .ID = "20260725-N",
            .name = "Yohan B. Escaño",
            .program = "BSEMC",
            .yearSec = "2-B"
        },
        {
            .ID = "20260369-N",
            .name = "Nostalgia L. Aguirre",
            .program = "BSIS",
            .yearSec = "1-A"
        },
        {
            .ID = "20260699-N",
            .name = "Joshua Daniel B. Dominno",
            .program = "BSCS",
            .yearSec = "1-A"
        }
    };

    int choice = 0;

    do {
        choice = displayMainMenu();

        if (choice == 1) {
            displayBooks(books);
        }
        else if (choice == 2) {
            borrowBook(books, student);
        }

    } while (choice != 3);

    system("cls");
    printf("THANK YOU FOR USING UCC LIBRARY. GOODBYE.\n\n");

    return 0;
}