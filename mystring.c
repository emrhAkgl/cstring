#include "mystring.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>


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

size_t add_string(string *str, const char *_data)
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

size_t add_string_from_terminal(string *str) {
	char buf[2048];

	if (fgets(buf, sizeof(buf), stdin) == NULL) {
        	return 0;
    	}

	char *new_line = strchr(buf, '\n');
	if (new_line != NULL) {
        	*new_line = '\0';
	}

	size_t buf_size = strlen(buf);
	
    	if (str->data == NULL) {
        	str->data = strdup(buf);
        	if (str->data == NULL) {
			return 0;
		}
        str->size = buf_size + 1;
	} else {
        	char *data_buf = realloc(str->data, str->size + buf_size);
        	if (data_buf == NULL) {
            		return 0;
        	}
		if (data_buf != str->data) {
			free(str->data);
			str->data = data_buf;
		}
        
	        strcat(str->data, buf);
	        str->size += buf_size;
    	}

    return buf_size;
}

void free_string(string *str)
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
