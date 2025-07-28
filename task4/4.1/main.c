#include <stdio.h> 
#include <locale.h>
#include "contact.h"

void getInput(char *prompt, char *buffer, size_t size, int required) {
    do {
        if (prompt) printf("%s", prompt);
        fgets(buffer, size, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; 

        if (required && strlen(buffer) == 0) {
            printf("Field cannot be empty. Please re-enter.\n");
        }
    } while (required && strlen(buffer) == 0);
}

void Input(Contact* contact) {
    char lastname[MAX_LENGTH], firstname[MAX_LENGTH], middlename[MAX_LENGTH], workplace[MAX_LENGTH], position[MAX_LENGTH], phone[MAX_LENGTH], email[MAX_LENGTH], link[MAX_LENGTH];
    getInput("Enter last name (required): ", lastname, MAX_LENGTH, 1);
    getInput("Enter first name (required): ", firstname, MAX_LENGTH, 1);
    getInput("Enter middle name: ", middlename, MAX_LENGTH, 0);
    getInput("Enter your place of work: ", workplace, MAX_LENGTH, 0);
    getInput("Enter your job title: ", position, MAX_LENGTH, 0);
    *contact = initContact(lastname, firstname, middlename, workplace, position);
    getInput("Enter phone number: ", contact->Info.Phone, MAX_LENGTH, 0);
    getInput("Enter email address: ", contact->Info.Email, MAX_LENGTH, 0);
    getInput("Enter links to your pages and profiles: ", contact->Info.Link, MAX_LENGTH, 0);
}


void printContactInfo(const ContactInfo* const contactInfo) {
    printf("Phone number: %s\n", contactInfo->Phone);
    printf("Email address: %s\n", contactInfo->Email); 
    printf("Links to pages and profiles: %s\n", contactInfo->Link);
}

void printContact(const Contact* const contact) {
    printf("Full name: %s %s %s\n", contact->LastName, contact->FirstName, contact->MiddleName);
    printf("Work place: %s\n", contact->Workplace); 
    printf("Job title: %s\n", contact->Position);
    printContactInfo(&contact->Info);
}

int getIndexOfContact() {
    int index;
    printf("Enter contact number: ");
    scanf("%d", &index); getchar();
    return index - 1;
}

int main(void) {  
    setlocale(LC_ALL, "");       
    Item* head = NULL;   
    Contact* cont;
    int choice;
    int index;
    do {
        printf("\n--- Phonebook ---\n");
        printf("1. Add contact\n");
        printf("2. Show all contacts\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. Exit\n");
        printf("Select action: ");
        choice = getchar();
        while (getchar() != '\n');
        switch(choice) {
            case '1': 
                Contact contact;
                Input(&contact);
                head = InsertValue(contact, head);
                break;
            case '2':
                PrintList(head);
                break;
            case '3':
                index = getIndexOfContact();
                cont = getContact(index, head);
                if (cont) 
                    editContact(cont);
                else 
                    printf("Invalid contact index!\n");
                break;
            case '4':
                index = getIndexOfContact();
                cont = getContact(index, head);
                if (cont) 
                    head = DeleteValue(cont, head);
                else 
                    printf("Invalid contact index!\n");
                break;
            case '5':
                break;
            default: 
                printf("Wrong choice!\n");
        } 
    }  while (choice != '5');
    return 0;                      
}    