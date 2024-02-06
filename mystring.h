#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <sys/types.h>

#define MAX_STRING_SIZE 2048

//This struct is designed to use the string object from other languages in C.
typedef struct string{
	char 			*data;
	size_t 			size;

	size_t 			(*add_string)(struct string *str, const char *_data);
	size_t			(*add_string_from_terminal)(struct string *str);
	void			(*print)(const struct string *str);
	
	void			(*free_string)(struct string *str);
} string;

// To apply the corresponding functions to function pointers in the string_s structure.
string *init_string();

// To add a string to the data pointer in the string_s structure. 
// If the pointer is empty it allocates memory, if it is not empty 
// it adds a space at the end of the last word in it and adds the data
// in "_data" to string->data.
size_t add_string(string *str, const char *_data);

// It does the same job as the add_string function. The only difference is that 
// instead of giving a value with the _data parameter, we get it from the terminal
// with the user's input. Since it does not request the user to enter a value 
// (each user may want to give a different message, so the function can be edited 
// in the future and this situation can be solved), each user must give his own message 
// before the function call. 
size_t add_string_from_terminal(string *str);

void print_string(const string *str);

// Finally, we release the allocated memory again with functions like "init_string, 
// add_string, add_string_from_terminal". 
void free_string(string *str);



#endif
