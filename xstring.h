#ifndef _XSTRING_H_
#define _XSTRING_H_

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>


/************************************************************************************************************************/
/************************************************************************************************************************/
/*							XSTRING.H							*/
#include <sys/types.h>
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
string		*init_string(void);
size_t		add_string(string *self, const char *_data);
int		add_string_from_terminal(string *self);
void		print_string(const string *self);
void		free_string(string *self);
int		pop_back_string(string *self);
size_t		get_string_size(const string *self);
const char 	*get_string_data(const string *self);
void		clear_string(string *self);

char		*xstrdup(const char *s);

/* Henüz yapmadıklarım*/
int erase_word(string *str, const char *word);
int swap_word(string *str, char *str1, const char *str2);
/************************************************************************************************************************/
/************************************************************************************************************************/

#define TEST 1
#define MAX_STRING_SIZE 2048

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
 * To add a string to the data pointer in the string_s structure. 
 * If the pointer is empty it allocates memory, if it is not empty 
 * it adds a space at the end of the last word in it and adds the data
 * in "_data" to string->data.
 */
size_t add_string(string *self, const char *_data)
{
	char *str_data_buf = NULL;
	size_t str_size = 0;
	if (self->data != NULL) {
		str_size = strlen(self->data);
	}

	if(_data == NULL || (strlen(_data) + str_size) > MAX_STRING_SIZE) 	
		return 0;

	if(str_size == 0) {	
		if ((self->data = xstrdup(_data)) == NULL) {
			return 0;
		} else {
			return strlen(self->data);
		}
	}
	
	//'self->data' doluysa sonuna bir boşlukla beraber '_data' yı ekle.
	if((str_data_buf = xstrdup(self->data)) == NULL) {
		return 0;
	} else {
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
}


/*
 * It does the same job as the add_string function. The only difference is that 
 * instead of giving a value with the _data parameter, we get it from the terminal
 * with the user's input. Since it does not request the user to enter a value 
 * (each user may want to give a different message, so the function can be edited 
 * in the future and this situation can be solved), each user must give his own message 
 * before the function call. If the function succeeds, it returns 0, if it fails,
 * it returns a negative value.
 */
int add_string_from_terminal(string *self)
{	
	char *input_buf = NULL;
	size_t str_size = 0;

	if (self->data != NULL) {
		str_size = strlen(self->data);
	}

	if ((input_buf = (char *)calloc((MAX_STRING_SIZE - str_size),sizeof(char))) == NULL) {
		if (TEST)
			fprintf(stderr, "ERROR: input_buf %d\n", __LINE__);
		return -1;
	}
	if (fgets(input_buf, (MAX_STRING_SIZE - str_size), stdin) == NULL) {
		if (TEST) {
			fprintf(stderr, "ERROR: fgets %d\n", __LINE__);
		}
		free(input_buf);
		input_buf = NULL;
		return -1;
    	}
	if (strlen(input_buf) == 1) {
		free(input_buf);
		input_buf = NULL;
		return 0;
	}

	/*
	 *Buraya kadar 'buf için hafızadan alan aldık ve kullanıcıdan buraya giriş yapmasını istedik.
	 * fgets giriş sırasında \n karakterini de değişkene aktarıyor, biz de bunu istemiyoruz.
	 * O yüzden \n karakterini bulup onu NULL ile değiştirelim. 
	 */
	char *new_line = strchr(input_buf, '\n');
	if (new_line != NULL) {
        	*new_line = '\0';
	}

	int res = add_string(self, input_buf);
	free(input_buf);
	input_buf = NULL;
	if (res > 0)
		return 1;
	else 
		return 0;
}



int pop_back_string(string *self)
{
	if (self->data == NULL) {
		return -1;
	}

	if (strlen(self->data) == 0) 
		return -1;

	char *ptr = self->data;
	size_t size = strlen(self->data);
	for(int i = size -1; i >= 0; i--) {
		if (ptr[i] == ' ') {
			int j = i;
			char *buf = (char *)malloc((j + 1) * sizeof(char));
			if (!buf) {
				return -1;
			} else {
				memmove(buf, ptr, j);
				free(self->data);
				self->data = buf;
				return 0;
			}
			
		}
	}

	return 0;
}



void print_string(const string *self)
{
	if (self->data){
		printf("%s", self->data);
		fflush(stdout);
	}
}



size_t	get_string_size(const string *self)
{
	return strlen(self->data);
}



const char *get_string_data(const string *self)
{
	return (const char *)self->data;
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

#endif
