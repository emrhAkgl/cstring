#ifndef _XSTRING_H_
#define _XSTRING_H_

#include <stdio.h>	/* printf */
#include <string.h>	/* strlen, strcpy ... */
#include <stddef.h>
#include <stdlib.h>	/* malloc, calloc ...*/

/************************************************************************************************************************/
/************************************************************************************************************************/
/*							XSTRING.H							*/
#include <sys/types.h>	/* size_t */
typedef struct string{
	char 		*data;

	size_t		(*add)(struct string *self, const char *_data);
	int 		(*add_from_terminal)(struct string *self);
	void 		(*print)(const struct string *self);
	void 		(*free)(struct string *self);
	int 		(*pop_back)(struct string *self);
	size_t 		(*get_size)(const struct string *self);
	const char*	(*get_data)(const struct string *self);
	void 		(*clear)(struct string *self);
} string;

/* FUNCTIONS */
string	*init_string(void);
size_t	add_string(string *self, const char *_data);
int	add_string_from_terminal(string *self);
void	print_string(const string *self);
void	free_string(string *self);
int	pop_back_string(string *self);
size_t	get_string_size(const string *self);
const char *get_string_data(const string *self);
void clear_string(string *self);

char *xstrdup(const char *s);

/* Henüz yapmadıklarım*/
int erase_word(string *self, const char *word);
int swap_word(string *self, char *word1, const char *word2);
/************************************************ XSTRING.H *************************************************************/
/************************************************************************************************************************/

#define MAX_STRING_SIZE 4096

/*
 * To apply the corresponding functions to function pointers in the string structure.
 */
string *init_string()
{
	string *tmp = (string*)calloc(1, sizeof(string));
	if(!tmp)	
		return NULL;
	
	tmp->add = &add_string;
	tmp->add_from_terminal = &add_string_from_terminal;
	tmp->print = &print_string;
	tmp->free = &free_string;
	tmp->pop_back = &pop_back_string;
	tmp->get_size = &get_string_size;
	tmp->get_data = &get_string_data;
	tmp->clear = &clear_string;

	return tmp;
}

/*
 * Adds @_data to the data member of @self. 
 * @self: struct to which we will add @_data to the member named data.
 * @_data: A pointer to the text to be added to @self->data.
 * Note: If 'self->data' is not empty, it appends '_data' with a space at the end. 
 */
size_t add_string(string *self, const char *_data)
{
	char *str_data_buf = NULL;
	size_t str_size = 0;
	if (self->data != NULL) {
		str_size = strlen(self->data);
	}

	if(_data == NULL || (strlen(_data) + str_size) > MAX_STRING_SIZE) {
		fprintf(stderr, "%s = %lu, %s %s\n", "MAX_STRING_SIZE",
			(size_t)MAX_STRING_SIZE, 
			"if you need you can edit the MAX_STRING_SIZE value in the xstring.h",
			"header file according to your needs");
		return 0;
	}

	if(str_size == 0) {	
		if ((self->data = xstrdup(_data)) == NULL) {
			return 0;
		} else {
			return strlen(self->data);
		}
	}
	
	if((str_data_buf = xstrdup(self->data)) == NULL)
		return 0;
	
	free(self->data);
	self->data = NULL;
		
	if ((self->data = (char *)calloc(((strlen(str_data_buf) + strlen(_data)) + 1), sizeof(char))) == NULL) {
		free(str_data_buf);
		return 0;
	} else {
		sprintf(self->data, "%s %s", str_data_buf, _data);
		free(str_data_buf);
		str_data_buf = NULL;
		return (strlen(self->data) + 1);
	}		
}

/*
 * Adds a char array to the data member of @self from the terminal. 
 * If @self->data is not empty, the value received with a space is appended to @self->data. 
 * @self: struct containing the destination of the string received from the terminal. (@self->data)
 */
int add_string_from_terminal(string *self)
{	
	char *input_buf = NULL;
	size_t str_size = 0;

	if (self->data != NULL)
		str_size = strlen(self->data);

	if ((MAX_STRING_SIZE - str_size) <= 0) {
		fprintf(stderr, "%s = %lu, %s %s\n", "MAX_STRING_SIZE",
			(size_t)MAX_STRING_SIZE, 
			"if you need you can edit the MAX_STRING_SIZE value in the xstring.h",
			"header file according to your needs");
	}

	if ((input_buf = (char *)calloc((MAX_STRING_SIZE - str_size),sizeof(char))) == NULL)
		return -1;
		
	if (fgets(input_buf, (MAX_STRING_SIZE - str_size), stdin) == NULL) {
		free(input_buf);
		input_buf = NULL;
		return -1;
    	}
	
	if (strlen(input_buf) == 1) {
		free(input_buf);
		input_buf = NULL;
		return 0;
	}

	/* We need to delete the '\n' character at the end of the received string. */
	char *new_line = strchr(input_buf, '\n');
	
	if (new_line != NULL)
        	*new_line = '\0';

	int res = add_string(self, input_buf);
	free(input_buf);
	input_buf = NULL;
	
	if (res > 0)
		return 1;
	else 
		return 0;
}

/*
 * If @self->data is not empty, delete the word at the end. 
 */
int pop_back_string(string *self)
{
	char *tmp = NULL;
	size_t tmp_len = 0;
	
        if (!self->data || strlen(self->data) == 0)
	        return -1;
	
	char *wht_space = strrchr(self->data, ' ');
	if (!wht_space)
	        return -1;
	
	tmp_len = (size_t)(wht_space - self->data);
	tmp = (char*)calloc(sizeof(char), tmp_len);
	memmove(tmp, self->data, tmp_len);
	*(tmp+tmp_len) = '\0';
	
	free(self->data);
	self->data = tmp;
	return 0;
}

/*
 * If @self->data is not empty, it prints the value in it to the terminal. 
 */
void print_string(const string *self)
{
	if (self->data){
		printf("%s", self->data);
		fflush(stdout);
	}
}

/*
 * If @self->data is not empty, it returns the number of characters in it. 
 * @self: @self: The struct that contains our return value.
 */
size_t	get_string_size(const string *self)
{
	return strlen(self->data);
}

/*
 * If the 'data' member of the @self parameter is not empty, 
 * it returns the 'data' member as 'const char *'. 
 */
const char *get_string_data(const string *self)
{
	if (self->data)
		return (const char *)self->data;
	else
		return NULL;
}


/*
 * It only releases @self->data. It does not delete @self;
 */
void clear_string(string *self)
{
	if (self->data == NULL)
		return;

	free(self->data);
	self->data = NULL;
}


/*
 * It releases @str.
 */
void free_string(string *str)
{
	if (str != NULL) {

		if(str->data != NULL){
			free(str->data);
			str->data = NULL;
		}

		free(str);
		str = NULL;
	}
}


/*
 * Copies @str to a dynamically allocated memory and returns it. 
 * @str: Value to be copied to dynamic memory. 
 */
char *xstrdup(const char *str)
{
	size_t len = strlen(str) + 1;
	char *tmp = (char *)malloc(len);
	char *tmp_ptr = tmp;
	
	if (!tmp_ptr) {
	    fprintf(stderr, "tmp maloc err, line: %d\n", __LINE__);
		return NULL;
	}
	
	while ((*tmp_ptr++ = *str++) != '\0');
	
	return tmp;
}
#endif /* _XSTRING_H_ */
