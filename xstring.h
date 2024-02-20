#ifndef _XSTRING_H_
#define _XSTRING_H_

#include <sys/types.h>

#define MAX_STRING_SIZE 2048

typedef struct string{
	char 		*data;
	size_t 		size;

	size_t 		(*add)(struct string *str, const char *_data);
	int		(*add_from_terminal)(struct string *str);
	void		(*print)(const struct string *str);
	void		(*free)(struct string *str);
} string;

string *init_string();
size_t add_string(string *str, const char *_data);
int add_string_from_terminal(string *str);
void print_string(const string *str);
void free_string(string *str);

#endif
