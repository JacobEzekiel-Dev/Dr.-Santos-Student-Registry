#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define NAME_LEN     50
#define MAJOR_LEN    50


int   ids[MAX_STUDENTS];
char  names[MAX_STUDENTS][NAME_LEN];
char  majors[MAX_STUDENTS][MAJOR_LEN];
float gpas[MAX_STUDENTS];
int   credits[MAX_STUDENTS];
int   studentCount = 0;   


void addStudent(void);
void displayAllStudents(void);
void searchByID(void);
void searchByGPA(void);
void searchByMajor(void);
void printStudent(int index);
void clearInputBuffer(void);
void printMenu(void);


int main(void) {
    int choice;

    printf("=========================================\n");
    printf("   Dr. Santos' Student Registry System\n");
    printf("=========================================\n");

    do {
        printMenu();
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addStudent();        break;
            case 2: displayAllStudents();break;
            case 3: searchByID();        break;
            case 4: searchByGPA();       break;
            case 5: searchByMajor();     break;
            case 0: printf("Goodbye, Dr. Santos!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
        printf("\n");

    } while (choice != 0);

    return 0;
}


void printMenu(void) {
    printf("-----------------------------------------\n");
    printf("1. Add new student\n");
    printf("2. Display all students\n");
    printf("3. Search student by ID\n");
    printf("4. Find students with GPA >= threshold\n");
    printf("5. Find students by major (with count)\n");
    printf("0. Exit\n");
    printf("-----------------------------------------\n");
}


void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }
}


void addStudent(void) {
    int idx;

    if (studentCount >= MAX_STUDENTS) {
        printf("Registry is full! Cannot add more than %d students.\n", MAX_STUDENTS);
        return;
    }

    idx = studentCount; 

    printf("Enter Student ID: ");
    scanf("%d", &ids[idx]);
    clearInputBuffer();

    printf("Enter Student Name: ");
    fgets(names[idx], NAME_LEN, stdin);
    names[idx][strcspn(names[idx], "\n")] = '\0'; 

    printf("Enter Major: ");
    fgets(majors[idx], MAJOR_LEN, stdin);
    majors[idx][strcspn(majors[idx], "\n")] = '\0';

    printf("Enter GPA (0.0 - 4.0): ");
    scanf("%f", &gpas[idx]);

    printf("Enter Credits Taken: ");
    scanf("%d", &credits[idx]);
    clearInputBuffer();

    studentCount++;
    printf("Student added successfully! (%d/%d students in registry)\n",
           studentCount, MAX_STUDENTS);
}


void printStudent(int index) {
    printf("ID: %-6d Name: %-20s Major: %-20s GPA: %.2f  Credits: %d\n",
           ids[index], names[index], majors[index], gpas[index], credits[index]);
}


void displayAllStudents(void) {
    if (studentCount == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("\n%-8s %-20s %-20s %-6s %-8s\n",
           "ID", "Name", "Major", "GPA", "Credits");
    printf("-------------------------------------------------------------------\n");

    {
        int i;
        for (i = 0; i < studentCount; i++) {
            printf("%-8d %-20s %-20s %-6.2f %-8d\n",
                   ids[i], names[i], majors[i], gpas[i], credits[i]);
        }
    }
    printf("-------------------------------------------------------------------\n");
    printf("Total students: %d\n", studentCount);
}


void searchByID(void) {
    int targetID;
    int found = 0;

    if (studentCount == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &targetID);
    clearInputBuffer();

    {
        int i;
        for (i = 0; i < studentCount; i++) {
            if (ids[i] == targetID) {
                printf("\nStudent Found:\n");
                printStudent(i);
                found = 1;
                break; 
            }
        }
    }

    if (!found) {
        printf("No student found with ID %d.\n", targetID);
    }
}


void searchByGPA(void) {
    float threshold;
    int found = 0;

    if (studentCount == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("Enter minimum GPA threshold: ");
    scanf("%f", &threshold);
    clearInputBuffer();

    printf("\nStudents with GPA >= %.2f:\n", threshold);
    printf("-------------------------------------------------------------------\n");

    {
        int i;
        for (i = 0; i < studentCount; i++) {
            if (gpas[i] >= threshold) {
                printStudent(i);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No students found with GPA >= %.2f.\n", threshold);
    }
}


void searchByMajor(void) {
    char targetMajor[MAJOR_LEN];
    int count = 0;

    if (studentCount == 0) {
        printf("No students in the registry yet.\n");
        return;
    }

    printf("Enter major to search: ");
    fgets(targetMajor, MAJOR_LEN, stdin);
    targetMajor[strcspn(targetMajor, "\n")] = '\0';

    printf("\nStudents majoring in \"%s\":\n", targetMajor);
    printf("-------------------------------------------------------------------\n");

    {
        int i;
        
        for (i = 0; i < studentCount; i++) {
            if (strcmp(majors[i], targetMajor) == 0) {
                printStudent(i);
                count++;
            }
        }
    }

    if (count == 0) {
        printf("No students found in major \"%s\".\n", targetMajor);
    } else {
        printf("-------------------------------------------------------------------\n");
        printf("Total students in \"%s\": %d\n", targetMajor, count);
    }
}
