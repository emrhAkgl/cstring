#include "mystring.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>


typedef struct string_s {
	char 			*data;
	size_t 			size;

	size_t 			(*add_string)(struct string_s *str, const char *_data);
	size_t			(*add_string_from_terminal)(struct string_s *str);
	
	void			(*free_string)(struct string_s *str);
} string;


string *init_string()
{
		string *buf = (string*)calloc(1, sizeof(string));
		if(!buf)
			return NULL;

		buf->add_string = &add_string;
		buf->add_string_from_terminal = &add_string_from_terminal;
		buf->free_string = &free_string;
		
		return buf;
}

static size_t add_string(string *str, const char *_data)
{
	if(_data == NULL)
		return 0;
	if(str->size == 0) {
		str->data = strdup(_data);
		if(str->data == NULL) {
			return 0;
		} else {
			str->size = strlen(str->data)+1;
			return str->size;
		}
	} else {
		char *str_data_buf = strdup(str->data);
		if(str_data_buf == NULL) {
			return 0;
		} else {
			free(str->data);
			str->data = NULL;
			str->data = (char *)calloc(((strlen(str_data_buf) + strlen(_data)) + 1), sizeof(char));
			
			if(str->data == NULL) {
				free(str_data_buf);
				return 0;
			} else {
				sprintf(str->data, "%s %s", str_data_buf, _data);
				str->size = strlen(str->data) + 1;
				return (size_t)(strlen(str->data) + 1);
			}
		}	
	}
}

static size_t add_string_from_terminal(string *str)
{
	char *buf = (char *)calloc(2048, sizeof(char));
	if(buf == NULL)
		return 0;
	
	if(fgets(buf, 2048, stdin) == NULL) {
		free(buf);
		return 0;
	}
	char *new_line = strchr(buf, '\n');
	if(new_line != NULL)
		*new_line = '\0';
	
	if(str->data == NULL) {
		str->data = (char *)calloc((strlen(buf) + 1), sizeof(char));
		if(str->data == NULL) {
			free(buf);
			return 0;
		}
		
		size_t i = 0;
		for(; i < strlen(buf); i++) {
			str->data[i] = buf[i];
		}
		str->data[i] = '\0';
		
		str->size = strlen(str->data);
		return str->size;
	} else {
		size_t buf_size = strlen(buf);
		
		char *data_buf = (char *)calloc((str->size + buf_size), sizeof(char));
		if(data_buf == NULL) {
			free(buf);
			return 0;
		}
		
		sprintf(data_buf, "%s %s", str->data, buf);
		free(str->data);
		
		str->data = data_buf;
		str->size = strlen(str->data) + 1;
		free(buf);
		return buf_size;
	}
}

static void free_string(string *str)
{
	if(str->data != NULL){
		free(str->data);
		str->data = NULL;
	}
	if(str != NULL) {
		free(str);
		str = NULL;
	}
}