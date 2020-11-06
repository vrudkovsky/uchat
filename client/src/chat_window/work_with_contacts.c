#include "client.h"



static make_start_contact_list(void) {
    for (int i = 0; i < main_data.contacts; i++) {
    }
}

void work_with_contacts(void) {
    chat.contact_row_list = malloc(sizeof(contact_row_t));
    chat.contact_row_list->next = NULL;
    if (main_data.contacts > 0)
        make_start_contact_list();
}