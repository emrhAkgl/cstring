#include "xstring.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#define TEST 1

string *init_string()
{
	/*
 	 * To apply the corresponding functions to function pointers in the string_s structure.
 	 */
	string *buf = (string*)calloc(1, sizeof(string));
	if(!buf)	
		return NULL;
	
	buf->add_string = &add_string;
	buf->add_string_from_terminal = &add_string_from_terminal;
	buf->print = &print_string;
	buf->free_string = &free_string;

	return buf;
}

size_t add_string(string *str, const char *_data)
{
	/*
	 * To add a string to the data pointer in the string_s structure. 
	 * If the pointer is empty it allocates memory, if it is not empty 
	 * it adds a space at the end of the last word in it and adds the data
	 * in "_data" to string->data.
	 */
	char *str_data_buf = NULL;

	if(_data == NULL || (strlen(_data) + str->size) > MAX_STRING_SIZE) 	
		return 0;

	if(str->size == 0) {	
		if ((str->data = strdup(_data)) == NULL) {
			return 0;
		} else {
			str->size = strlen(str->data)+1;
			return str->size;
		}
	}
	
	//'str->data' doluysa sonuna bir boşlukla beraber '_data' yı ekle.
	if((str_data_buf = strdup(str->data)) == NULL) {
		return 0;
	} else {
		free(str->data);
		str->data = NULL;
		
		if ((str->data = (char *)calloc(((strlen(str_data_buf) + strlen(_data)) + 1), sizeof(char))) == NULL) {
			free(str_data_buf);
			return 0;
		} else {
			sprintf(str->data, "%s %s", str_data_buf, _data);
			str->size = strlen(str->data) + 1;
			free(str_data_buf);
			str_data_buf = NULL;
			return (strlen(str->data) + 1);
		}
	}		
}

int add_string_from_terminal(string *str)
{
	/*
	 * It does the same job as the add_string function. The only difference is that 
	 * instead of giving a value with the _data parameter, we get it from the terminal
	 * with the user's input. Since it does not request the user to enter a value 
	 * (each user may want to give a different message, so the function can be edited 
	 * in the future and this situation can be solved), each user must give his own message 
	 * before the function call. If the function succeeds, it returns 0, if it fails,
	 * it returns a negative value.
	 */
	
	char *input_buf = NULL;
	size_t input_buf_size = 0;

	if ((input_buf = (char *)calloc((MAX_STRING_SIZE - str->size),sizeof(char))) == NULL) {
		if (TEST)
			fprintf(stderr, "Hata: input_buf %d\n", __LINE__);
		return -1;
	}
	if (fgets(input_buf, (MAX_STRING_SIZE - str->size), stdin) == NULL) {
		if (TEST) {
			fprintf(stderr, "Hata: fgets %d\n", __LINE__);
		}
		free(input_buf);
		input_buf = NULL;
		return -1;
    	}
	if (strlen(input_buf) == 1) {
		free(input_buf);
		input_buf = NULL;
		return 0;
	} else {
		/* "-1" because the '\n' character has not yet been deleted.*/
		input_buf_size = strlen(input_buf) - 1; 
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

	int res = add_string(str, input_buf);
	free(input_buf);
	input_buf = NULL;
	if (res > 0)
		return 1;
	else 
		return 0;
}


void print_string(const string *str)
{
	if (str->data){
		printf("Dada: %s\nSize: %lu\n", str->data, str->size);
	}
}


void free_string(string *str)
{
	/*
	 * Finally, we release the allocated memory again with functions like "init_string, 
	 * add_string, add_string_from_terminal". 
	 */
	if (str != NULL) {

		if(str->data != NULL){
			free(str->data);
			str->data = NULL;
		}

		free(str);
		str = NULL;
	}
}
