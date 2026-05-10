#include "ui.h"
#include "contact.h"
#include <string.h>
#include <stdio.h>

void ui_flush_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

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
    printf("\n--- Contact List (Total: %d) ---\n", contacts_count);
    if (contacts_count == 0) {
        printf("No contacts found.\n");
    } else {
        for (int i = 0; i < contacts_count; i++) {
            printf("[%d] Name: %s\n    Phone: %s\n", 
                   i, contacts[i].name, contacts[i].phone);
            if (i < contacts_count - 1) {
                printf("---------------------------------\n");
            }
        }
    }
    printf("---------------------------------\n\n");
}

void ui_run(void) {

    printf("Contacts Manager | version 0.0.1\n");
    
    while (1) {
        char action;
        printf("--- Main Menu ---\n"
               "(l) List contacts\n"
               "(a) Add contact\n"
               "(s) Search contact\n"
               "(d) Delete contact\n"
               "(c) Change contact\n"
               "(e) Exit\n"
               "\nChoose an action: ");
        if (scanf(" %c", &action) != 1) {
            fprintf(stderr, "Input error\n");
            return;
        }

        ui_flush_buffer();

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

            case 'd': {
                printf("Enter index: \n");
                int index;
                if (scanf("%d", &index) != 1) {
                    fprintf(stderr, "Input error\n");
                    ui_flush_buffer();
                    break;
                }
                ui_flush_buffer();
                
                if (contact_delete(index) != 0) {
                    fprintf(stderr, "Contact deletion error\n");
                }

                printf("Contact with index %d deleted\n", index);

                break;
            }

            case 'c': {
                printf("Enter index: \n");
                int index;
                if (scanf("%d", &index) != 1) {
                    fprintf(stderr, "Input error\n");
                    ui_flush_buffer();
                    break;
                }
                ui_flush_buffer();

                char name[100];

                if (ui_read_field(name, sizeof(name), "name") != 0) {
                    break;
                }

                char phone[20];
                if (ui_read_field(phone, sizeof(phone), "phone") != 0) {
                    break;
                }
                
                if (contact_edit(index, name, phone) != 0) {
                    fprintf(stderr, "Edit error\n");
                }

                printf("\nContact changed\n");

                break;
            }
                

            default:
                printf("Unknown action: '%c'\n", action);
        }
    }
}
