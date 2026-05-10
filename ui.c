#include "ui.h"
#include "contact.h"
#include <string.h>
#include <stdio.h>

int ui_read_field(char *buf, size_t buf_size, const char *field_name) {
    printf("Enter %s: \n", field_name);
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return -1;
    }

    buf[strcspn(buf, "\n")] = '\0';

    return 0;
}

void ui_list_contacts(void) {
    for (int i = 0; i < contacts_count; i++) {
        printf("Contact: %d\nName: %s\nPhone: %s\n\n", 
               i, contacts[i].name, contacts[i].phone);
    }
}

void ui_run(void) {

    printf("Contacts Manager | version 0.0.1\n");
    
    while (1) {
        char action;
        printf("What do you want to do?\n\nList contacts(l) | Add contact(a) | Search contact(s) | Exit(e)\n\n");
        if (scanf(" %c", &action) != 1) {
            fprintf(stderr, "Input error\n");
            return;
        }

        // clear buffer from \n
        int c;
        while ((c = getchar()) != '\n' && c != EOF);


        switch (action) {
            case 'l':
                ui_list_contacts();
                break;

            case 'a': {
                char name[100];

                if (ui_read_field(name, sizeof(name), "name") != 0) {
                    break;
                }

                char phone[20];
                if (ui_read_field(phone, sizeof(phone), "phone") != 0) {
                    break;
                }
                
                int res = contact_add(name, phone);
                if (res == -1) {
                    printf("Contacts list is full (max %d)\n", MAX_CONTACTS);
                } else {
                    printf("Contact added.\n");
                }

                break;
            }

            case 'e':
                printf("Exiting...\n");
                return;

            case 's': {
                char name[100];

                if (ui_read_field(name, sizeof(name), "name") != 0) {
                    break;
                }

                char phone[20];
                if (ui_read_field(phone, sizeof(phone), "phone") != 0) {
                    break;
                }

                Contact *c = contact_search(name, phone);
                
                if (c == NULL) {
                    printf("Contact not found.\n");
                } else {
                    printf("Found contact:\nName: %s\nPhone: %s\n", c->name, c->phone);
                }
                
                break;
            }
                

            default:
                printf("Unknown action: '%c'\n", action);
        }
    }
}
