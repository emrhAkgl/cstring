#ifndef _STRUTIL_H_
#define _STRUTIL_H_ 1

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#include <stdio.h>   /* printf */
#include <string.h>  /* strlen, strcpy ... */
#include <stdlib.h>  /* malloc, calloc, realloc ... */
#include <stdint.h>  /* uint8_t */
#include <ctype.h>

#define MAX_STRING_SIZE 4096

typedef struct Str {
	char	*data;
	uint8_t is_dynamic;
} str;


/* FUNCTIONS -> */
str	*str_init(void);
int	str_add(str *self, const char *_data);
size_t  str_input(str *self);
void    str_print(const str *self);
void    str_free(str *self);
int     str_pop_back(str *self, char sep);
size_t  str_get_size(const str *self);
void    str_clear(str *self);
int	str_rem_word(str *self, const char *needle);
const char *str_get_data(const str *self);

static inline char* get_dyn_input(size_t max_str_size);
int str_swap_word(str *self, const char *word1, const char *word2);

//Functions planned to be written.
int str_to_upper(str *self);
int str_to_lower(str *self);
int str_to_title_case(str *self);
int str_to_sentence_case(str *self, const char *sep);
/* <- FUNCTIONS */



/*
 * str_init() - Initializes a new Str structure.
 *
 * This function initializes a new Str structure and allocates memory for it.
 * The caller is responsible for freeing the returned structure using str_free().
 * 
 * Returns:
 *     A pointer to the newly initialized Str structure, or NULL if memory allocation fails.
 */

str *str_init()
{
	str *tmp = (str *)calloc(1, sizeof(str));
	if (!tmp)
		return NULL;

	tmp->is_dynamic = 1;
	return tmp;
}


/*
 * str_add() - Adds a string to the data member of a Str structure.
 * @self: Pointer to the Str structure.
 * @_data: Pointer to the string to be added.
 *
 * This function adds the string @_data to the data member of the Str structure @self.
 * If @self->data is not empty, @_data is appended with a space at the end.
 * 
 * Returns:
 *     0 on successful completion
 *    -1 if @self or @_data is NULL, or if memory allocation fails
 */
int str_add(str *self, const char *_data)
{
	if (_data == NULL)
		return -1;
	
	if (self == NULL) {
		if ((self = str_init()) == NULL) {
			return -1;
		}
	}

	size_t self_data_size = self->data ? strlen(self->data) : 0;
	size_t new_size = self_data_size + strlen(_data) + 1; // +2 for null

	if (new_size >= MAX_STRING_SIZE)
		return -1;

	char *new_data = realloc(self->data, new_size);

	if (new_data == NULL)
		return -1;

	if (self->data == NULL) {
		strcpy(new_data, _data); // Copy data if it's the first addition
	} else {
		strcat(new_data, _data); // Append new data
	}

	self->data = new_data;

	return 0;
}


/*
 * str_input() - Adds a string from the terminal to the data member of a Str structure.
 * @self: Pointer to the Str structure.
 *
 * This function adds a string received from the terminal to the data member of the Str structure @self.
 * If @self->data is not empty, the received value is appended with a space.
 * 
 * Returns:
 *     The length of the string added to @self->data, or 0 if an error occurs
 */

size_t str_input(str *self)
{
	if (self == NULL) {
		if ((self = str_init()) == NULL) {
			return 0;
		}
	}


	if (!self->data) {
		self->data = get_dyn_input(MAX_STRING_SIZE);
		return (self->data ? strlen(self->data) : 0);
	}


	char *buf = get_dyn_input(MAX_STRING_SIZE - strlen(self->data));
	if (!buf)
		return -1;

	char *self_data_ptr = (char *)realloc(self->data, (strlen(self->data) + strlen(buf) + 1));
	if (!self_data_ptr)
		return -1;

	strncat(self->data, buf, strlen(buf));

	free(buf);
	return strlen(self->data);
}


/*
 * str_pop_back() - Removes the last character from the string in a Str structure.
 * @self: Pointer to the Str structure.
 * @sep: Separator character to be removed.
 *
 * This function removes the last occurrence of the separator character @sep 
 * from the string in the Str structure @self->data. If @self->data is empty or 
 * does not contain @sep, the function fails with -1.
 * 
 * Returns:
 *     0 on successful completion
 *    -1 if @self->data is NULL or empty, or if @sep is not found
 */
int str_pop_back(str *self, char sep)
{
	if (self->data == NULL && strlen(self->data) == 0)
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
void str_print(const str *self)
{
	if (self->data) {
		printf("%s", self->data);
		fflush(stdout);
	}
}

/*
 * If @self->data is not empty, it returns the number of characters in it.
 * @self: The struct that contains our return value.
 */
size_t str_get_size(const str *self)
{
    	return (self->data ? strlen(self->data) : 0);
}

/*
 * If the 'data' member of the @self parameter is not empty,
 * it returns the 'data' member as 'const char *'.
 */
const char *str_get_data(const str *self)
{
    	return (const char *)self->data;
}

/*
 * It only releases @self->data. It does not delete @self;
 */
void str_clear(str *self)
{
	if (self->data) {
		free(self->data);
		self->data = NULL;
	}
}


/*
 * It releases @str.
 */
void str_free(str *self)
{
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


/*
 * get_dyn_input() - Dynamically reads input from the terminal.
 * @max_str_size: Maximum size of the input string to be read.
 *
 * This function dynamically reads input from the terminal, allocating memory as needed.
 * It continues reading characters until EOF or newline ('\n') is encountered, dynamically 
 * resizing the memory buffer as necessary. The caller is responsible for freeing the 
 * returned buffer.
 * 
 * Returns:
 *     A dynamically allocated buffer containing the input string read from the terminal,
 *     or NULL if memory allocation fails or EOF is encountered before any characters are read.
 */
static inline char* get_dyn_input(size_t max_str_size)
{
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

/*
 * str_rem_word() - Removes a specific word from the string.
 * @self: Pointer to the Str structure.
 * @needle: The word to be removed from @self->data.
 *
 * This function removes the specific word @needle from @self->data. 
 * If @needle cannot be found, the function fails with -1.
 * 
 * Returns:
 *     0 on successful completion
 *    -1 if @self, @self->data, or @needle is NULL, or if @needle cannot be found
 *
 * Note: This function is designed to manage dynamic memory governed by the 
 * @self->is_dynamic property. The caller is responsible for freeing 
 * the returned data to continue accessing the modified data.
 */
int str_rem_word(str *self, const char *needle)
{
        if (!self && !self->data && !needle)
        	return -1;
            
        size_t self_data_size = strlen(self->data);
        size_t needle_size = strlen(needle);
        
        if (needle_size > self_data_size)
        	return -1;
            
        char *L = NULL;
        L = strstr(self->data, needle);
        if(!L)
        	return -1;

        memmove(L, L + needle_size, self_data_size - (L - self->data) - needle_size + 1);
	self->data[self_data_size - needle_size] = '\0';
        
        char *buf = (char*)realloc(self->data, 
                ((self_data_size - needle_size)) +1);
        
	if (!buf)	// realloc başarısız oldu; ancak kelime diziden kaldırıldı ve sonuna NULL eklendi
		return -2;

        if (buf)
        	self->data = buf;

	return 0;
}


/*
 * str_swap_word() - Replaces a specific word with another word.
 * @self: Pointer to the Str structure.
 * @word1: The word to be replaced.
 * @word2: The new word to replace @word1.
 *
 * This function replaces the specific word @word1 found in @self->data 
 * with @word2. If @word1 cannot be found, the function fails with -1.
 * 
 * Returns:
 *     0 on successful completion
 *    -1 if an error occurred
 *
 * Note: This function is designed to manage dynamic memory governed by the 
 * @self->is_dynamic property. The caller is responsible for freeing 
 * the returned data to continue accessing the modified data.
 */
int str_swap_word(str *self, const char *word1, const char *word2)
{
	if (!self && !self->data && !self->is_dynamic && !word1 && !word2)
		return -1;

	size_t self_data_size = strlen(self->data);
	size_t word1_size = strlen(word1);
	size_t word2_size = strlen(word2);

	char *L = strstr(self->data, word1);
	if (!L)
		return -1;

	size_t new_size = self_data_size - word1_size + word2_size;
	char *buf = (char *)malloc(sizeof(char) * (new_size + 1)); // +1 for null terminator
	if (!buf)
		return -1;

	// Copy everything before word1
	strncpy(buf, self->data, L - self->data);
	buf[L - self->data] = '\0'; // Null terminate the buffer

	// Copy word2
	strcat(buf, word2);

	// Copy everything after word1
	strcat(buf, L + word1_size);

	free(self->data);
	self->data = buf;

	return 0;
}


int str_to_upper(str *self)
{
	char *p = self->data;

	if (!self && !self->data)
		return -1;
	
	while (*p) {
		*p = toupper((int)*p);
		p++;
	}

	return 0;
}


int str_to_lower(str *self)
{
	char *p = self->data;

	if (!self && !self->data)
		return -1;
	
	while (*p) {
		*p = tolower((int)*p);
		p++;
	}

	return 0;
}


int str_to_sentence_case(str *self, const char *sep)
{
	if (!self && !self->data && !sep)
		return -1;

	char *end = NULL;
	char *self_data_ptr = self->data;

	if (*self_data_ptr) {
		*self_data_ptr = toupper((int)*self_data_ptr);
		self_data_ptr++;
	}

	end = strstr(self_data_ptr, sep);
	while (end != NULL && *end != '\0') {
		for (int i = 0; i < strlen(sep); i++) {
			end++;
			self_data_ptr++;
			if (*end == '\0') {
				break;
			}
		}
		*end = toupper((int)*end);
		end = strstr(self_data_ptr, sep);
	}
	return 0;
}

int str_to_title_case(str *self);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _XSTRING_H_ */
