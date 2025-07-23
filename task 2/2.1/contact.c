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
            printf("Поле не может быть пустым. Повторите ввод.\n");
        }
    } while (required && strlen(buffer) == 0);
}

void addContactInfo(ContactInfo* contactInfo) {
    getInput("Введите номер телефона: ", contactInfo->Phone, MAX_LENGTH, 0);
    getInput("Введите адрес электронной почты: ", contactInfo->Email, MAX_LENGTH, 0);
    getInput("Введите ссылки на свои страницы и профили: ", contactInfo->Link, MAX_LENGTH, 0);
}

void addContact(Contact* contact) {
    if (count < MAX_CONTACTS) {
    getchar(); 

    getInput("Введите фамилию (обязательное поле): ", contact->LastName, MAX_LENGTH, 1);
    getInput("Введите имя (обязательное поле): ", contact->FirstName, MAX_LENGTH, 1);
    getInput("Введите отчество: ", contact->MiddleName, MAX_LENGTH, 0);
    getInput("Введите место работы: ", contact->Workplace, MAX_LENGTH, 0);
    getInput("Введите должность: ", contact->Position, MAX_LENGTH, 0);

    addContactInfo(&contact->Info);
    contacts[count++] = *contact;
    }
}

void printContactInfo(const ContactInfo* const contactInfo) {
    printf("Номер телефона: %s\n", contactInfo->Phone);
    printf("Адрес электронной почты: %s\n", contactInfo->Email); 
    printf("Ссылки на страницы и профили: %s\n", contactInfo->Link);
}

void printContact(const Contact* const contact) {
    printf("ФИО: %s %s %s\n", contact->LastName, contact->FirstName, contact->MiddleName);
    printf("Место работы: %s\n", contact->Workplace); 
    printf("Должность: %s\n", contact->Position);
    printContactInfo(&contact->Info);
}

void editContact(Contact* contact) {
    char input[MAX_LENGTH];
    printf("Введите новые данные (оставьте пустым для сохранения текущего значения):\n");
    printf("Фамилия (%s): ", contact->LastName); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->LastName, input, MAX_LENGTH);
    printf("Имя (%s): ", contact->FirstName); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->FirstName, input, MAX_LENGTH);
    printf("Отчество (%s): ", contact->MiddleName); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->MiddleName, input, MAX_LENGTH);
    printf("Место работы (%s): ", contact->Workplace); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->Workplace, input, MAX_LENGTH);
    printf("Должность (%s): ", contact->Position); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contact->Position, input, MAX_LENGTH);
}

void editContactInfo(ContactInfo* contactInfo) {
    char input[MAX_LENGTH];
    printf("Номер телефона (%s): ", contactInfo->Phone); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contactInfo->Phone, input, MAX_LENGTH);
    printf("Адрес электронной почты (%s): ", contactInfo->Email); 
    fgets(input, MAX_LENGTH, stdin);
    if (strlen(input) != 0) strncpy(contactInfo->Email, input, MAX_LENGTH);
    printf("Ссылки на страницы и профили (%s): ", contactInfo->Link); 
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
    printf("Введите номер контакта: ");
    scanf("%d", &index); getchar();
    while (getchar() != '\n');
    if (index < 1 || index > count) {
        printf("Неверный номер!\n");
        return -1;
    }
    return index - 1;
}