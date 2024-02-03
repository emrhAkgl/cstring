#ifndef _MYSTRING_H_
#define _MYSTRING_H_

typedef struct string_s string;

string *init_string();

static size_t add_string(string *str, const char *_data);
static size_t add_string_from_terminal(string *str);
static void free_string(string *str);



#endif
