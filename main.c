//Employee Record Managemnt System
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
void backtoMenu();
void checkPassword();
void sortbyId();

// File pointers
FILE *fptr;
FILE *tempFile;
FILE *ps;

// Main function
int main() {
    checkPassword();
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

//back to menu function
void backtoMenu(){
    int choice;

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
    void backtoMenu();
}

// View employees
void viewEmployees() {
    int sort;
    struct employeeinfo employee;

    fptr = fopen("database.txt", "rb");
    if (fptr == NULL) {
        perror("Error opening file");
        return;
    }
    system("clear");
    puts("\nEmployee Records: ");
    while (fread(&employee, sizeof(struct employeeinfo), 1, fptr)) { //store each record 1 at a time at employee then use it.
        printf("ID: %d, Name: %s, Job: %s, Salary: %.2f\n", employee.id, employee.name, employee.job, employee.salary);
    }

    puts("Press 1 to sort the list.");
    scanf("%d", &sort);
    if(sort == 1){
        sortbyId();
    }
    else{
        viewEmployees();
    }

    fclose(fptr);
    void backtoMenu();
}

// Update employee details
void updateDetails() {
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

    while (fread(&employee, sizeof(struct employeeinfo), 1, fptr)) { //if id match, replace structure with new
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

    void backtoMenu();
}

// Delete employee
void deleteDetails() {
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

    while (fread(&employee, sizeof(struct employeeinfo), 1, fptr)) { //can't manipulate directly in c replace with new file
        if (employee.id == deleteId) {                                //skipping the deleted record and rename file
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

    void backtoMenu();
}

//checkpassword
void checkPassword() {
    char pPassword[20];
    char pConfirmPassword[20];
    int flag = 0;

    puts("\t\t*********************************");
    puts("\t\tEMPLOYEE RECORD MANAGEMENT SYSTEM");
    puts("\t\t*********************************\n");
    puts("\nTo Login:");

    ps = fopen("ps.txt", "rb");
    if (ps == NULL) {
        ps = fopen("ps.txt", "ab");
        if (ps == NULL) {
            puts("Error opening file for writing password.");
            return;
        }

        puts("Enter new password: ");
        fgets(pPassword, sizeof(pPassword), stdin);
        pPassword[strcspn(pPassword, "\n")] = '\0';

        puts("Confirm Password: ");
        fgets(pConfirmPassword, sizeof(pConfirmPassword), stdin); //get password from input
        pConfirmPassword[strcspn(pConfirmPassword, "\n")] = '\0'; //delete newline char or enter

        int passLength = strlen(pPassword);
        int confirmLength = strlen(pConfirmPassword);

        if (passLength != confirmLength) {                    //checking length first of two passwords
            puts("Passwords don't match in length.");
            checkPassword();
            return;
        }

        for (int i = 0; i < passLength; i++) {            //checking character by character if they are similar
            if (pPassword[i] != pConfirmPassword[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            fprintf(ps, "%s", pPassword); // Save the password to the file
            puts("Password set successfully.");
            fclose(ps);
            system("clear");
            welcomeScreen();
        } else {
            puts("Passwords do not match!");
            fclose(ps);
            checkPassword();
        }

    } else {
        char storedPassword[20];
        puts("Enter password: ");
        fgets(pPassword, sizeof(pPassword), stdin);  //stdin = take input and store in npassword
        pPassword[strcspn(pPassword, "\n")] = '\0';

        fgets(storedPassword, sizeof(storedPassword), ps);
        storedPassword[strcspn(storedPassword, "\n")] = '\0';

        if (strcmp(pPassword, storedPassword) == 0) {  //lexicographically compares letter by letter
            system("clear");
            welcomeScreen();
        } else {
            puts("Incorrect password.");
        }

        fclose(ps);
    }
}

//sort list by bubblesort algorithm
void sortbyId(){
    int choice, outer, inner, didSwap, employeeCount = 0;
    struct employeeinfo employees[100];

    fptr = fopen("database.txt", "rb");
    if(fptr == NULL){
        perror("Error opening file");
        return;
    }

    //read array of employees
    while(fread(&employees[employeeCount], sizeof(struct employeeinfo), 1, fptr)){
        employeeCount++; //count number of employees
    }
    fclose(fptr);
        for(outer = 0; outer < employeeCount - 1; outer++){
            didSwap = 0;
            for(inner = outer + 1; inner < employeeCount; inner++){
                if(employees[inner].id < employees[outer].id){
                    struct employeeinfo temp = employees[inner];
                    employees[inner] = employees[outer];
                    employees[outer] = temp;
                    didSwap = 1;
                }
            }
            if(didSwap == 0){
                break;
            }
        }
        system("clear");
        puts("\nSorted Employee Records");
        for(int i; i < employeeCount; i++){
             printf("ID: %d, Name: %s, Job: %s, Salary: %.2f\n", employees[i].id, employees[i].name,
              employees[i].job, employees[i].salary);
        }

        puts("Press (1) to go back and press(2) to go to Main Menu");
        scanf("%d", &choice);

        if(choice == 1){
            system("clear");
            viewEmployees();
        }else if(choice == 2){
            system("clear");
            welcomeScreen();
        }

    }

