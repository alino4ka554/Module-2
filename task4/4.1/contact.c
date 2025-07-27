#include <stdio.h> 
#include <locale.h>
#include "contact.h"

Contact contacts[MAX_CONTACTS];
int count = 0;

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
    getInput("Enter last name (required): ", lastName, MAX_LENGTH, 1);
    getInput("Enter first name (required): ", firstName, MAX_LENGTH, 1);
    getInput("Enter middle name: ", middleName, MAX_LENGTH, 0);
    getInput("Enter your place of work: ", workplace, MAX_LENGTH, 0);
    getInput("Enter your job title: ", position, MAX_LENGTH, 0);
    contact = initContact(lastname, firstname, middlename, workplace, position);
    getInput("Enter phone number: ", contact->ContactInfo.Phone, MAX_LENGTH, 0);
    getInput("Enter email address: ", contact->ContactInfo.Email, MAX_LENGTH, 0);
    getInput("Enter links to your pages and profiles: ", contact->ContactInfo.Link, MAX_LENGTH, 0);
}

void addContactInfo(ContactInfo* contactInfo) {
    getInput("Enter phone number: ", contactInfo->Phone, MAX_LENGTH, 0);
    getInput("Enter email address: ", contactInfo->Email, MAX_LENGTH, 0);
    getInput("Enter links to your pages and profiles: ", contactInfo->Link, MAX_LENGTH, 0);
}

Contact* initContact(char* lastname, char* firstname, char* middlename, char* workplace, char* position) {
    if (count < MAX_CONTACTS) {
        Contact contact;
        strncpy(contact.LastName, lastname, MAX_LENGTH);
        strncpy(contact.FirstName, firstname, MAX_LENGTH);
        strncpy(contact.MiddleName, middlename, MAX_LENGTH);
        strncpy(contact.Workplace, workplace, MAX_LENGTH);
        strncpy(contact.Position, position, MAX_LENGTH);
        contacts[count++] = *contact;
        return &contact;
    }
    else 
        return NULL;
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

void editContact(Contact* contact) {
    char input[MAX_LENGTH];
    printf("Enter new data (leave blank to keep current value): \n");
    printf("Last Name (%s): ", contact->LastName); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->LastName, input, MAX_LENGTH);
    printf("First Name (%s): ", contact->FirstName); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->FirstName, input, MAX_LENGTH);
    printf("Middle Name (%s): ", contact->MiddleName); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->MiddleName, input, MAX_LENGTH);
    printf("Workplace (%s): ", contact->Workplace); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->Workplace, input, MAX_LENGTH);
    printf("Position (%s): ", contact->Position); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->Position, input, MAX_LENGTH);
}

void editContactInfo(ContactInfo* contactInfo) {
    char input[MAX_LENGTH];
    printf("Phone number (%s): ", contactInfo->Phone); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contactInfo->Phone, input, MAX_LENGTH);
    printf("Email address (%s): ", contactInfo->Email); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contactInfo->Email, input, MAX_LENGTH);
    printf("Links to pages and profiles (%s): ", contactInfo->Link); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contactInfo->Link, input, MAX_LENGTH);
}

void deleteContact(Contact* contacts, int *count, int index) {
    for(int i = index; i < *count; i++) {
        contacts[i] = contacts[i + 1];
    }
    (*count)--;
}

int getIndexOfContact() {
    int index;
    printf("Enter contact number: ");
    scanf("%d", &index); getchar();
    while (getchar() != '\n');
    if (index < 1 || index > count) {
        printf("Invalid number!\n");
        return -1;
    }
    return index - 1;
}