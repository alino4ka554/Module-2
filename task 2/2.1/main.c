#include <stdio.h> 
#include <locale.h>
#include "contact.h"

int main(void) {  
    setlocale(LC_ALL, "");          
    int choice;
    int index;
    do {
        printf("\n--- Телефонная книга ---\n");
        printf("1. Добавить контакт\n");
        printf("2. Показать все контакты\n");
        printf("3. Редактировать контакт\n");
        printf("4. Удалить контакт\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        choice = getchar();
        while (getchar() != '\n');
        switch(choice) {
            case '1': 
                Contact contact;
                addContact(&contact);
                break;
            case '2':
                for(int i = 0; i < count; i++) {
                    printf("\n[%d] ", i + 1);
                    printContact(&contacts[i]);
                }
                break;
            case '3':
                index = getIndexOfContact();
                if (index != -1)
                    editContact(&contacts[index]);
                break;
            case '4':
                index = getIndexOfContact();
                if (index != -1)
                    deleteContact(contacts, &count, index);
                break;
            case '5':
                break;
            default: 
                printf("Неверный выбор!\n");
        } 
    }  while (choice != '5');
    return 0;                      
}    