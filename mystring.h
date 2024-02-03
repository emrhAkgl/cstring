#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <sys/types.h>

typedef struct string_s {
	char 			*data;
	size_t 			size;

	size_t 			(*add_string)(struct string_s *str, const char *_data);
	size_t			(*add_string_from_terminal)(struct string_s *str);
	
	void			(*free_string)(struct string_s *str);
} string;

string *init_string();

size_t add_string(string *str, const char *_data);
size_t add_string_from_terminal(string *str);
void free_string(string *str);



#endif
