//Employee Record Mnagemnt System
//main.c
//written by leonotieno27
//Gmail: leonowino99@gmail.com

/*A console-based application to manage employee records for a small company.
It allows users to:
    1.Add new employee records.
    2.View all employee records.
    3.Update employee details.
    4.Delete employee records.
    5.Save and load data to/from a binary file for persistence.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"

// Function prototypes
void welcomeScreen();
void addNewEmployee();
void viewEmployees();
void updateDetails();
void deleteDetails();

// File pointers
FILE *fptr;
FILE *tempFile;

// Main function
int main() {
    welcomeScreen();
    return 0;
}

// Welcome screen
void welcomeScreen() {
    int choice;

    puts("\t\t*********************************");
    puts("\t\tEMPLOYEE RECORD MANAGEMENT SYSTEM");
    puts("\t\t*********************************\n");
    puts("Welcome,\n");
    puts("1. Add New Employee.");
    puts("2. View Employee Records.");
    puts("3. Update Employee Details.");
    puts("4. Delete Employee Records.");
    puts("5. Exit.");

    printf("\nChoose an action (use the numbers): ");
    scanf(" %d", &choice);

    switch (choice) {
        case 1: addNewEmployee(); break;
        case 2: viewEmployees(); break;
        case 3: updateDetails(); break;
        case 4: deleteDetails(); break;
        case 5: exit(0);
        default: puts("Invalid choice. Try again."); welcomeScreen();
    }
}

// Add new employee
void addNewEmployee() {
    struct employeeinfo employee;
    int choice;

    fptr = fopen("database.txt", "ab");  // Binary mode for appending
    if (fptr == NULL) {
        perror("Error opening file");
        return;
    }

    do {
        printf("\nEnter Employee ID: ");
        scanf("%d", &employee.id);
        getchar();  // Clear newline
        printf("Enter Employee Name: ");
        fgets(employee.name, 50, stdin);
        employee.name[strcspn(employee.name, "\n")] = '\0';  // Remove newline
        printf("Enter Job Position: ");
        fgets(employee.job, 50, stdin);
        employee.job[strcspn(employee.job, "\n")] = '\0';
        printf("Enter Salary: ");
        scanf("%f", &employee.salary);

        fwrite(&employee, sizeof(struct employeeinfo), 1, fptr);  // Write to file
        printf("Employee record added.\n");

        printf("Add another employee? (Y/N): ");
        scanf(" %d", &choice);

    } while (toupper(choice) == 'Y');

    fclose(fptr);

    puts("\n 1.Back to Main Menu.");
    puts("2.Exit");
    scanf(" %d", &choice);
    if(choice == 1){
        system("clear");
        welcomeScreen();
    }else if(choice == 2){
        exit(1);
    }else{
        exit(1);
    }
}

// View employees
void viewEmployees() {
    int choice;
    struct employeeinfo employee;

    fptr = fopen("database.txt", "rb");
    if (fptr == NULL) {
        perror("Error opening file");
        return;
    }

    puts("\nEmployee Records:");
    while (fread(&employee, sizeof(struct employeeinfo), 1, fptr)) {
        printf("ID: %d, Name: %s, Job: %s, Salary: %.2f\n", employee.id, employee.name, employee.job, employee.salary);
    }

    fclose(fptr);

   puts("\n1.Back to Main Menu.");
    puts("2.Exit");
    scanf(" %d", &choice);
    if(choice == 1){
        system("clear");
        welcomeScreen();
    }else if(choice == 2){
        exit(1);
    }else{
        exit(1);
    }
}

// Update employee details
void updateDetails() {
    int choice;
    struct employeeinfo employee;
    int updateId, found = 0;

    fptr = fopen("database.txt", "rb");
    tempFile = fopen("tempFile.txt", "wb");
    if (fptr == NULL || tempFile == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\nEnter ID of the employee to update: ");
    scanf("%d", &updateId);

    while (fread(&employee, sizeof(struct employeeinfo), 1, fptr)) {
        if (employee.id == updateId) {
            found = 1;
            printf("Enter New Employee Name: ");
            getchar();
            fgets(employee.name, 50, stdin);
            employee.name[strcspn(employee.name, "\n")] = '\0';
            printf("Enter New Job Position: ");
            fgets(employee.job, 50, stdin);
            employee.job[strcspn(employee.job, "\n")] = '\0';
            printf("Enter New Salary: ");
            scanf("%f", &employee.salary);
        }
        fwrite(&employee, sizeof(struct employeeinfo), 1, tempFile);
    }

    fclose(fptr);
    fclose(tempFile);

    remove("database.txt");
    rename("tempFile.txt", "database.txt");

    if (found) {
        puts("Employee details updated.");
    } else {
        puts("Employee not found.");
    }


    puts("\n1.Back to Main Menu.");
    puts("2.Exit");
    scanf(" %d", &choice);
    if(choice == 1){
        system("clear");
        welcomeScreen();
    }else if(choice == 2){
        exit(1);
    }else{
        exit(1);
    }
}

// Delete employee
void deleteDetails() {
    int choice;
    struct employeeinfo employee;
    int deleteId, found = 0;

    fptr = fopen("database.txt", "rb");
    tempFile = fopen("tempFile.txt", "wb");
    if (fptr == NULL || tempFile == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\nEnter ID of the employee to delete: ");
    scanf("%d", &deleteId);

    while (fread(&employee, sizeof(struct employeeinfo), 1, fptr)) {
        if (employee.id == deleteId) {
            found = 1;
            printf("Deleting employee ID: %d\n", deleteId);
            continue;  // Skip this record
        }
        fwrite(&employee, sizeof(struct employeeinfo), 1, tempFile);
    }

    fclose(fptr);
    fclose(tempFile);

    remove("database.txt");
    rename("tempFile.txt", "database.txt");

    if (found) {
        puts("Employee record deleted.");
    } else {
        puts("Employee not found.");
    }


    puts("\n1.Back to Main Menu.");
    puts("2.Exit");
    scanf(" %d", &choice);
    if(choice == 1){
        system("clear");
        welcomeScreen();
    }else if(choice == 2){
        exit(1);
    }else{
        exit(1);
    }
}
