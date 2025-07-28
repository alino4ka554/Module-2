#include <stdio.h> 
#include <locale.h>
#include "contact.h"

Contact initContact(char* lastname, char* firstname, char* middlename, char* workplace, char* position) {
    Contact contact;
    strncpy(contact.LastName, lastname, MAX_LENGTH);
    strncpy(contact.FirstName, firstname, MAX_LENGTH);
    strncpy(contact.MiddleName, middlename, MAX_LENGTH);
    strncpy(contact.Workplace, workplace, MAX_LENGTH);
    strncpy(contact.Position, position, MAX_LENGTH);
    return contact;
}

Item* InsertValue(Contact contact, Item* head) {
    Item* newItem;
    Item* tmp = head;
    newItem = malloc(sizeof(struct Item));
    newItem->value = contact;
    if(NULL == head) {
        newItem->prev = newItem;
        newItem->next = newItem;
        head = newItem;
        return head;
    }
    do {
        if(newItem->value.LastName[0] <= tmp->value.LastName[0]) {
            newItem->next = tmp;
            newItem->prev = tmp->prev;
            tmp->prev->next = newItem;
            tmp->prev = newItem;
            if(tmp == head) head = newItem;
            return head;
        }
        tmp = tmp->next;
    } while(tmp != head);
    newItem->next = tmp;
    newItem->prev = tmp->prev;
    tmp->prev->next = newItem;
    tmp->prev = newItem;
    return head;
}

Item* DeleteValue(Contact* contact, Item* head) {
    Item *tmp = head;
    int count = 0;
    if (NULL == head) {
        printf("List empty!\n");
        return head;
    }
    do {
        if (contact == &tmp->value) {
            if (tmp->next == tmp && tmp->prev == tmp) {
            free(tmp);
            return NULL;
        }
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
        if(tmp == head) head = head->next;
            free(tmp);
            return head;
        }
        tmp = tmp->next;
        count++;
    } while (tmp != head);
    printf("List does not contain %d!\n");
    return head;
}

void PrintList(Item* head) {
    Item* tmp = head;
    int count = 1;
    if (NULL == head) {
        printf("List empty!\n");
        return;
    }
    do {
        printf("\n[%d] ", count);
        printContact(&(tmp->value));
        tmp = tmp->next;
        count++;
    } while (tmp != head);
    printf("\n");
}

Contact* getContact(int index, Item* head) {
    Item *tmp = head;
    int count = 0;
    if (!head) return NULL;
    do {
        if (count == index)
            return &tmp->value;
        tmp = tmp->next;
        count++;
    } while (tmp != head);
    return NULL;
}

void editContact(Contact* contact) {
    Input(contact);
}
