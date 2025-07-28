#include <stddef.h>  
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 50
#define MAX_CONTACTS 50

typedef struct ContactInfo {
    char Phone[MAX_LENGTH];
    char Email[MAX_LENGTH];
    char Link[MAX_LENGTH];
} ContactInfo;

typedef struct Contact {
    char LastName[MAX_LENGTH];
    char FirstName[MAX_LENGTH];
    char MiddleName[MAX_LENGTH];
    char Workplace[MAX_LENGTH];
    char Position[MAX_LENGTH];
    ContactInfo Info;
} Contact;

typedef struct Item
{
    Contact value;
    struct Item* next;
    struct Item* prev;
} Item;

extern Contact contacts[MAX_CONTACTS];
extern int count;

void addContact();
Item* DeleteValue(Contact* contact, Item* head);
Contact* getContact(int index, Item* head);
Item* InsertValue(Contact contact, Item* head);
void PrintList(Item* head);
Contact initContact(char* lastname, char* firstname, char* middlename, char* workplace, char* position);
void printContactInfo(const ContactInfo* const contactInfo);
void printContact(const Contact* const contact);
void editContact(Contact* contact);
void deleteContact(Contact* contacts, int *count, int index);
int getIndexOfContact();
void getInput(char *prompt, char *buffer, size_t size, int required);
void Input(Contact* contact);
