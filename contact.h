#pragma once

#define MAX_CONTACTS 10

typedef struct Contact {
    char name[100];
    char phone[20];   // телефон как строка
} Contact;

extern Contact contacts[MAX_CONTACTS];
extern int contacts_count;


int contact_add(const char *name, const char *phone);
void contact_list(void);
Contact *contact_search(const char *name, const char *phone);
int contact_delete(int index);
int contact_edit(int index, const char *name, const char *phone);
