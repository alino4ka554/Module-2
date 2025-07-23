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
            printf("���� �� ����� ���� ������. ��������� ����.\n");
        }
    } while (required && strlen(buffer) == 0);
}

void addContactInfo(ContactInfo* contactInfo) {
    getInput("������� ����� ��������: ", contactInfo->Phone, MAX_LENGTH, 0);
    getInput("������� ����� ����������� �����: ", contactInfo->Email, MAX_LENGTH, 0);
    getInput("������� ������ �� ���� �������� � �������: ", contactInfo->Link, MAX_LENGTH, 0);
}

void addContact(Contact* contact) {
    if (count < MAX_CONTACTS) {
    getchar(); 

    getInput("������� ������� (������������ ����): ", contact->LastName, MAX_LENGTH, 1);
    getInput("������� ��� (������������ ����): ", contact->FirstName, MAX_LENGTH, 1);
    getInput("������� ��������: ", contact->MiddleName, MAX_LENGTH, 0);
    getInput("������� ����� ������: ", contact->Workplace, MAX_LENGTH, 0);
    getInput("������� ���������: ", contact->Position, MAX_LENGTH, 0);

    addContactInfo(&contact->Info);
    contacts[count++] = *contact;
    }
}

void printContactInfo(const ContactInfo* const contactInfo) {
    printf("����� ��������: %s\n", contactInfo->Phone);
    printf("����� ����������� �����: %s\n", contactInfo->Email); 
    printf("������ �� �������� � �������: %s\n", contactInfo->Link);
}

void printContact(const Contact* const contact) {
    printf("���: %s %s %s\n", contact->LastName, contact->FirstName, contact->MiddleName);
    printf("����� ������: %s\n", contact->Workplace); 
    printf("���������: %s\n", contact->Position);
    printContactInfo(&contact->Info);
}

void editContact(Contact* contact) {
    char input[MAX_LENGTH];
    printf("������� ����� ������ (�������� ������ ��� ���������� �������� ��������):\n");
    printf("������� (%s): ", contact->LastName); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->LastName, input, MAX_LENGTH);
    printf("��� (%s): ", contact->FirstName); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->FirstName, input, MAX_LENGTH);
    printf("�������� (%s): ", contact->MiddleName); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->MiddleName, input, MAX_LENGTH);
    printf("����� ������ (%s): ", contact->Workplace); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->Workplace, input, MAX_LENGTH);
    printf("��������� (%s): ", contact->Position); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->Position, input, MAX_LENGTH);
}

void editContactInfo(ContactInfo* contactInfo) {
    char input[MAX_LENGTH];
    printf("����� �������� (%s): ", contactInfo->Phone); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contactInfo->Phone, input, MAX_LENGTH);
    printf("����� ����������� ����� (%s): ", contactInfo->Email); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contactInfo->Email, input, MAX_LENGTH);
    printf("������ �� �������� � ������� (%s): ", contactInfo->Link); 
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
    printf("������� ����� ��������: ");
    scanf("%d", &index); getchar();
    while (getchar() != '\n');
    if (index < 1 || index > count) {
        printf("�������� �����!\n");
        return -1;
    }
    return index - 1;
}