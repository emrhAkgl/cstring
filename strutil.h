#ifndef _STRUTIL_H_
#define _STRUTIL_H_ 1

#include <stdio.h>   /* printf */
#include <string.h>  /* strlen, strcpy ... */
#include <stdlib.h>  /* malloc, calloc, realloc ... */

typedef struct Str {
	char	*data;
	unsigned int is_dynamic : 1;
} str;

/* FUNCTIONS */
str  	*str_init(void);
size_t  str_add(str *self, const char *_data);
size_t  str_input(str *self);
void    str_print(const str *self);
void    str_free(str *self);
int     str_pop_back(str *self, char sep);
size_t  str_get_size(const str *self);
void    str_clear(str *self);
const char *str_get_data(const str *self);

static inline char* get_dyn_input(size_t max_str_size);


/* Henüz yapmadıklarım */
int erase_word(str *self, const char *word);
int swap_word(str *self, char *word1, const char *word2);
/************************************************ XSTRING.H *************************************************************/
/************************************************************************************************************************/

#define MAX_STRING_SIZE 4096

/*
 * To apply the corresponding functions to function pointers in the str structure.
 */
str *init_string() {
	str *tmp = (str *)calloc(1, sizeof(str));
	if (!tmp)
		return NULL;

	tmp->is_dynamic = 1;
	return tmp;
}

/*
 * Adds @_data to the data member of @self.
 * @self: struct to which we will add @_data to the member named data.
 * @_data: A pointer to the text to be added to @self->data.
 * Note: If 'self->data' is not empty, it appends '_data' with a space at the end.
 */
size_t str_add(str *self, const char *_data) {
	if (self == NULL || _data == NULL)
		return 0;

	size_t self_data_size = self->data ? strlen(self->data) : 0;
	size_t new_size = self_data_size + strlen(_data) + 1; // +2 for null

	if (new_size >= MAX_STRING_SIZE)
		return 0;

	char *new_data = realloc(self->data, new_size);

	if (new_data == NULL)
		return 0;

	if (self->data == NULL) {
		strcpy(new_data, _data); // Copy data if it's the first addition
	} else {
		strcat(new_data, _data); // Append new data
	}

	self->data = new_data;

	return strlen(self->data);
}


/*
 * Adds a char array to the data member of @self from the terminal.
 * If @self->data is not empty, the value received with a space is appended to @self->data.
 * @self: struct containing the destination of the str received from the terminal. (@self->data)
 */
size_t str_input(str *self) {
	if (self == NULL) {
		self = init_string();
		if (!self) {
		fprintf(stderr, "Line: %d \nstr pointer was NULL and "
				"memory allocation for str failed!",
			(__LINE__ - 1));
		return 0;
		}
	}


	if (!self->data) {
		self->data = get_dyn_input(MAX_STRING_SIZE);
		return (self->data ? strlen(self->data) : 0);
	}


	char *buf = get_dyn_input(MAX_STRING_SIZE - strlen(self->data));
	if (!buf)
		return 0;

	char *self_data_ptr = (char *)realloc(self->data, (strlen(self->data) + strlen(buf) + 1));
	if (!self_data_ptr)
		return 0;

	strncat(self->data, buf, strlen(buf));

	free(buf);
	return strlen(self->data);
}


/*
 * If @self->data is not empty, delete the word at the end.
 */
int str_pop_back(str *self, char sep) {
	if (!self->data || strlen(self->data) == 0)
		return -1;

	char *p = strrchr(self->data, sep);
	if (!p)
		return -1;

	*p = '\0';

	char *self_data_ptr = (char *)realloc(self->data, strlen(self->data) + 1); // Trim memory
	if (!self_data_ptr)
		return -1;
	
	self->data = self_data_ptr;
	return 0;
}

/*
 * If @self->data is not empty, it prints the value in it to the terminal.
 */
void str_print(const str *self) {
	if (self->data) {
		printf("%s", self->data);
		fflush(stdout);
	}
}

/*
 * If @self->data is not empty, it returns the number of characters in it.
 * @self: The struct that contains our return value.
 */
size_t str_get_size(const str *self) {
    	return (self->data ? strlen(self->data) : 0);
}

/*
 * If the 'data' member of the @self parameter is not empty,
 * it returns the 'data' member as 'const char *'.
 */
const char *str_get_data(const str *self) {
    	return (const char *)self->data;
}

/*
 * It only releases @self->data. It does not delete @self;
 */
void str_clear(str *self) {
	if (self->data) {
		free(self->data);
		self->data = NULL;
	}
}


/*
 * It releases @str.
 */
void str_free(str *self) {
	if (self) { // Check NULL
		if (self->data) {
			free(self->data);
			self->data = NULL;
		}
		if (self->is_dynamic) {
			free(self);
			self = NULL;
		}
	}
}

static inline char* get_dyn_input(size_t max_str_size) {
	const int CHUNK_SIZE = 10;
	char* buffer = (char *)calloc(CHUNK_SIZE,  sizeof(char));

	if (buffer == NULL) 
		return NULL;

	size_t current_size = CHUNK_SIZE; // Size of available memory.
	size_t length = 0; // Length of current string

	int c;
	while ((c = getchar()) != EOF && c != '\n') {
		if (length + 1 >= current_size) { // Expand memory
			current_size += CHUNK_SIZE;			
			char* tmp = realloc(buffer, current_size);

			if (tmp == NULL) {
				free(buffer);
				return NULL;
			}
			buffer = tmp;
		}

		if (current_size >= (max_str_size - 1)) {
			free(buffer);
			return NULL;
		}

		buffer[length++] = (char)c;
		buffer[length] = '\0'; // End the series
	}

	// Finally release the extra memory
	char *result = (char *)malloc((length + 1) * sizeof(char));
	if (result == NULL) {
		free(buffer);
		return NULL;
	}
	
	strncpy(result, buffer, strlen(buffer));
	result[strlen(buffer)] = '\0';

	free(buffer);
	return result;
}


#endif /* _XSTRING_H_ */
