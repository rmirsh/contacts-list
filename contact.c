#include "contact.h"
#include <string.h>

Contact contacts[MAX_CONTACTS];
int contacts_count = 0;

int contact_add(const char *name, const char *phone) {
    if (contacts_count >= MAX_CONTACTS) {
        return -1;
    }

    // имя
    strncpy(contacts[contacts_count].name, name, sizeof(contacts[contacts_count].name) - 1);
    contacts[contacts_count].name[sizeof(contacts[contacts_count].name) - 1] = '\0';

    // телефон
    strncpy(contacts[contacts_count].phone, phone, sizeof(contacts[contacts_count].phone) - 1);  // надо
    contacts[contacts_count].phone[sizeof(contacts[contacts_count].phone) - 1] = '\0';

    contacts_count++;
    return 0;
}

Contact *contact_search(const char *name, const char *phone) {
    int search_by_name = 0;

    if (name != NULL && name[0] != '\0') {
        search_by_name = 1;
    } else if (phone == NULL || phone[0] == '\0') {
        return NULL;
    }

    for (int i = 0; i < contacts_count; i++) {
        if (search_by_name) {
            if (strcmp(contacts[i].name, name) == 0) {
                return &contacts[i];
            }
        } else {
            if (strcmp(contacts[i].phone, phone) == 0) {
                return &contacts[i];
            }
        }
    }
    return NULL;
}


int contact_delete(int index);
