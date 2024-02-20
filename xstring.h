#ifndef _XSTRING_H_
#define _XSTRING_H_

#include <sys/types.h>

#define MAX_STRING_SIZE 2048

typedef struct string{
	char 		*data;
	size_t 		size;

	size_t 		(*add)			(struct string *str, const char *_data);
	int		(*add_from_terminal)	(struct string *str);
	void		(*print)			(const struct string *str);
	void		(*free)			(struct string *str);
	int 		(*pop_back)			(struct string *str);
	size_t		(*get_size)			(const struct string *str);
	const char*	(*get_data)			(const struct string *str);
	void		(*clear)			(struct string *str);
} string;

/* FUNCTIONS */
string		*init_string(void);
size_t		add_string(string *str, const char *_data);
int		add_string_from_terminal(string *str);
void		print_string(const string *str);
void		free_string(string *str);
int		pop_back_string(string *str);
size_t		get_string_size(const string *str);
const char 	*get_string_data(const string *str);
void		clear_string(string *str);

#endif
