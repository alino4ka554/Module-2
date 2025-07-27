#include <stddef.h>  
#include <string.h>

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

extern Contact contacts[MAX_CONTACTS];
extern int count;

void addContactInfo(ContactInfo* contactInfo);
void addContact(Contact* contact);
void printContactInfo(const ContactInfo* const contactInfo);
void printContact(const Contact* const contact);
void editContact(Contact* contact);
void editContactInfo(ContactInfo* contactInfo);
void deleteContact(Contact* contacts, int *count, int index);
int getIndexOfContact();
void getInput(char *prompt, char *buffer, size_t size, int required);
