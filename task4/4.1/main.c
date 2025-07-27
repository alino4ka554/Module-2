#include <stdio.h> 
#include <locale.h>
#include "contact.h"

int main(void) {  
    setlocale(LC_ALL, "");          
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
                printf("Wrong choice!\n");
        } 
    }  while (choice != '5');
    return 0;                      
}    