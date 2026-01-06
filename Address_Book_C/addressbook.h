#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>


struct Contact{
    char name[50];
    char phone[15];
    char email[50];
};

struct AddressBook {
    struct Contact contacts[100];
    int contactCount;
    int index_record[100];
    int ir_size;
};
//all function prototypes
void push_data_tofile(struct AddressBook * , char * );
void pull_file_data(struct AddressBook * ,char *);
void add_contact(struct AddressBook *addressBook);
void search_contact(struct AddressBook *addressBook);
void edit_contact(struct AddressBook *addressBook);
void delete_contact(struct AddressBook *addressBook);
void list_contacts(struct AddressBook *addressBook);
int validatemobile(char * );
int validateemail(char *);
int duplicatemobileno(struct AddressBook * , char *);
int duplicateemail(struct AddressBook * , char *);
#endif
