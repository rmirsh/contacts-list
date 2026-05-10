#pragma once

#include <stddef.h>

int ui_read_field(char *buf, size_t buf_size, const char *field_name);
void ui_list_contacts(void);
void ui_flush_buffer(void);
void ui_run(void);
