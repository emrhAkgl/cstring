/*
 * strutil.h - String Utility Functions
 *
 * This header file provides a set of functions for manipulating and managing
 * strings in a thread-safe manner. The `str` structure allows for dynamic
 * string management with support for various operations such as adding,
 * modifying, and querying string data.
 *
 * Features:
 * - Dynamic memory management for string data.
 * - Thread safety through mutex locking.
 * - Functions for common string operations like conversion, reversal, and
 *   manipulation.
 *
 * The functions provided in this header file include:
 * - `str_init()`: Initialize a new `Str` structure.
 * - `str_add()`: Append a string to the existing data.
 * - `str_input()`: Read a string from standard input.
 * - `str_add_input()`: Append input from standard input to existing data.
 * - `str_pop_back()`: Remove trailing data after a specified separator.
 * - `str_print()`: Print the string data to standard output.
 * - `str_get_size()`: Get the length of the string.
 * - `str_clear()`: Clear the string data.
 * - `str_free()`: Free the `Str` structure and its associated resources.
 * - `str_rem_word()`: Remove a specified word from the string.
 * - `str_swap_word()`: Swap occurrences of two words in the string.
 * - `str_to_upper()`: Convert the string to uppercase.
 * - `str_to_lower()`: Convert the string to lowercase.
 * - `str_to_title_case()`: Convert the string to title case.
 * - `str_reverse()`: Reverse the string.
 * - `str_is_empty()`: Check if the string is empty.
 * - `get_dyn_input()`: Helper function to read input dynamically.
 *
 * This file includes necessary headers for standard operations and thread safety,
 * and defines the `Str` structure along with associated function prototypes.
 *
 * Author: Emrah Akgül
 * Date: 27.07.2024
 *
 * License: unlicense
 */


#if !_STRUTIL_H_
#define _STRUTIL_H_ 1

/*    HEADERS    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include <pthread.h>


#if defined(__clang__) || defined(__GNUC__)
  #define STR_WARN_UNUSED_RESULT __attribute((warn_unused_result))
#else
  #define STR_WARN_UNUSED_RESULT 
#endif

#define OFF 0
#define ON 1

#define STRDEBUGMODE ON

const static size_t MAX_STRING_SIZE  = ((SIZE_MAX / 100) * 95);


typedef struct Str {
	char	*data;
	unsigned char is_dynamic;
	pthread_mutex_t lock;
} str;

typedef enum Str_err_t{
	STR_OK = 0,
	STR_NULL,
	STR_INVALID,
	STR_NOMEM,
	STR_ERRCPY,
	STR_MAXSIZE,
	STR_ALLOC,
	STR_EMPTY,
	STR_FAIL
}Str_err_t;

/*		FUNCTIONS -->		*/
/*
 * str_init - Initialize a new Str structure
 *
 * This function allocates and initializes a new Str structure. It sets the
 * is_dynamic flag to 1 and initializes the mutex. The caller is responsible
 * for freeing the allocated memory using str_free().
 *
 * Return: Pointer to the newly allocated Str structure, or NULL if memory
 * allocation fails.
 */
str *str_init(void);


/*
 * str_add - Add a string to the Str structure
 *
 * @self: Pointer to the Str structure
 * @_data: Pointer to the string to be added
 *
 * This function appends the given string @_data to the existing data in
 * the Str structure. If the data is already present, it reallocates
 * memory to accommodate the new string. Ensures thread safety with
 * mutex locks. Returns 0 on success or a negative error code on failure.
 */
Str_err_t str_add(str *self, const char *_data);


/*
 * str_input - Read a string from standard input into the Str structure.
 *
 * @self: Pointer to the Str structure where the input will be stored.
 *
 * This function reads a line of input from standard input (stdin) and
 * stores it in the Str structure. It allocates memory dynamically for
 * the input string. Thread safety is ensured by locking the mutex. If
 * there is already data present in the structure, it will return an error.
 * Returns 0 on success, or -1 if an error occurs.
 *
 * Return: 0 on success, or -1 on failure.
 */
Str_err_t str_input(str *self);


/*
 * str_print - Print the string data to standard output.
 *
 * @self: Pointer to the Str structure containing the data to print.
 *
 * This function prints the string data stored in the Str structure to
 * standard output (stdout). It acquires a mutex lock to ensure thread safety
 * while accessing the data. If the Str structure or its data is NULL, nothing
 * will be printed.
 */
void str_print(str *self);


/*
 * str_free - Free the Str structure and its resources.
 *
 * @self: Pointer to the Str structure to be freed.
 *
 * This function releases all memory allocated for the Str structure,
 * including the string data and the structure itself if it was dynamically
 * allocated. Ensures thread safety by locking the mutex during the cleanup
 * process. If the Str structure or its data is NULL, nothing is done.
 */
void str_free(str *self);


/*
 * str_pop_back - Remove the trailing portion of the string after the last
 * occurrence of a separator.
 *
 * @self: Pointer to the Str structure from which the data will be modified.
 * @sep: Separator character after which data will be removed.
 *
 * This function trims the string data in the Str structure by removing
 * the portion of the string following the last occurrence of the specified
 * separator character. Thread safety is ensured by using mutex locking.
 * Returns 0 on success, or a negative error code if an error occurs.
 *
 * Return: 0 on success, or a negative error code on failure.
 */
Str_err_t str_pop_back(str *self, char sep);


/*
 * str_get_size - Get the length of the string in the Str structure.
 *
 * @self: Pointer to the Str structure whose string length is queried.
 *
 * This function returns the length of the string data stored in the Str
 * structure. If the structure or its data is NULL, it returns 0.
 *
 * Return: Length of the string, or 0 if the Str structure or data is NULL.
 */
size_t  str_get_size(const str *self);


/*
 * str_clear - Clear the string data from the Str structure.
 *
 * @self: Pointer to the Str structure whose data will be cleared.
 *
 * This function deallocates the memory used for the string data in the
 * Str structure and sets the data pointer to NULL. Thread safety is ensured
 * through mutex locking. If the Str structure itself is NULL, no action is
 * taken.
 */
void str_clear(str *self);


/*
 * str_rem_word - Remove all occurrences of a word from the string.
 *
 * @self: Pointer to the Str structure from which the word will be removed.
 * @needle: The word to remove from the string.
 *
 * This function removes all occurrences of the specified word from the
 * string data stored in the Str structure. Adjusts memory allocation as
 * necessary. Mutex locking is used to ensure thread safety. Returns 0 on
 * success, or a negative error code if an error occurs.
 *
 * Return: 0 on success, or a negative error code on failure.
 */
Str_err_t str_rem_word(str *self, const char *needle);


/*
 * str_get_data - Retrieve the current string data from the Str structure.
 *
 * @self: Pointer to the Str structure from which to retrieve the data.
 *
 * This function returns a pointer to the string data stored within the
 * Str structure. If the Str structure or its data is NULL, the function
 * returns NULL. The caller should not modify the returned string directly
 * as it is managed by the Str structure. If modifications are needed,
 * use the appropriate functions provided by the Str API.
 *
 * Return: Pointer to the string data stored in the Str structure, or NULL
 *         if the Str structure or its data is NULL.
 */
const char *str_get_data(const str *self);


/*
 * str_add_input - Append a line of input to existing string data.
 *
 * @self: Pointer to the Str structure where the input will be appended.
 *
 * This function reads a line of input from standard input (stdin) and appends
 * it to the existing string data within the Str structure. If there is no
 * existing data, it initializes the data with the new input. If there is
 * existing data, it reallocates memory to accommodate the new input and
 * appends it. Ensures thread safety with mutex locking. Returns 0 on success,
 * or a negative error code if any issue arises during input handling or memory
 * allocation.
 *
 * Return: 0 on success, or a negative error code on failure.
 */
Str_err_t str_add_input(str *self);


/*
 * str_to_upper - Convert the entire string to uppercase.
 *
 * @self: Pointer to the Str structure containing the string to convert.
 *
 * This function transforms all lowercase characters in the string data
 * to uppercase. Thread safety is maintained through mutex locking. If
 * the Str structure or its data is NULL, returns -1.
 *
 * Return: 0 on success, or -1 if the Str structure or data is NULL.
 */
Str_err_t str_to_upper(str *self);


/*
 * str_to_lower - Convert the entire string to lowercase.
 *
 * @self: Pointer to the Str structure containing the string to convert.
 *
 * This function transforms all uppercase characters in the string data
 * to lowercase. Mutex locking is used to ensure thread safety. Returns 0
 * on success, or -1 if the Str structure or data is NULL.
 *
 * Return: 0 on success, or -1 if the Str structure or data is NULL.
 */
Str_err_t str_to_lower(str *self);


/*
 * get_dyn_input - Read a line of input from stdin with dynamic allocation.
 *
 * @max_str_size: The maximum size of the input string to read.
 *
 * This function reads a line of input from the standard input (stdin), dynamically
 * allocating memory as needed to accommodate the input. It grows the buffer in chunks
 * if necessary to handle larger inputs. The function ensures that the total size of
 * the buffer does not exceed the specified maximum size. After reading the input, it
 * copies the buffer to a new memory location and returns it, freeing the original
 * buffer. Returns a pointer to the newly allocated string or NULL if an error occurs.
 *
 * Return: Pointer to the dynamically allocated input string, or NULL on failure.
 */
char* get_dyn_input(size_t max_str_size);


/*
 * str_swap_word - Swap occurrences of two words in the string.
 *
 * @self: Pointer to the Str structure where the words will be swapped.
 * @word1: The word to be replaced.
 * @word2: The word to replace word1 with.
 *
 * This function replaces all occurrences of word1 in the string with word2.
 * Handles memory allocation and ensures thread safety with mutex locking.
 * Returns 0 on success, or a negative error code if an error occurs.
 *
 * Return: 0 on success, or a negative error code on failure.
 */
Str_err_t str_swap_word(str *self, const char *word1, const char *word2);


/*
 * str_to_title_case - Convert the string to title case.
 *
 * @self: Pointer to the Str structure containing the string to modify.
 *
 * This function converts the string data to title case, where the first
 * letter of each word is capitalized and the remaining letters are in
 * lowercase. Mutex locking ensures thread safety. Returns 0 on success,
 * or -1 if the Str structure or its data is NULL or empty.
 *
 * Return: 0 on success, or -1 if the Str structure or data is NULL or empty.
 */
Str_err_t str_to_title_case(str *self);


/*
 * str_reverse - Reverse the string in the Str structure.
 *
 * @self: Pointer to the Str structure containing the string to reverse.
 *
 * This function reverses the entire string data stored in the Str structure.
 * Ensures thread safety by locking the mutex. Returns 0 on success, or -1
 * if the Str structure or its data is NULL, or if the string is empty.
 *
 * Return: 0 on success, or -1 if the Str structure or data is NULL or empty.
 */
Str_err_t str_reverse(str *self);


/*
 * str_is_empty - Check if the Str structure's string is empty.
 *
 * @self: Pointer to the Str structure to check.
 *
 * This function checks whether the string data in the Str structure is
 * either NULL or has zero length. Returns true if the string is empty,
 * false otherwise.
 *
 * Return: true if the string is empty or NULL, false otherwise.
 */
bool str_is_empty(str *self);

static char *str_copy(char *dest, const char *source);
static Str_err_t str_concat(char *dest, const char *source);
static size_t str_length(const char *s);
static Str_err_t str_nconcat(char *dest, const char *src, size_t n);
static Str_err_t str_ncopy(char *dest, const char *src, size_t n);

int str_check_err(Str_err_t err, const char *msg);


/* 	<--FUNCTIONS		*/


str *str_init(void)
{
	str *tmp = (str *)calloc(1, sizeof(str));
	if (!tmp)
		return NULL;

	tmp->is_dynamic = 1;
	pthread_mutex_init(&tmp->lock, NULL);
	return tmp;
}


Str_err_t str_add(str *self, const char *_data)
{
	if (!self || !_data)
		return STR_NULL;

	pthread_mutex_lock(&self->lock);
	size_t size = str_length(_data);

	if (self->data) {
		size += str_length(self->data);

		char *p = (char *)realloc(self->data, (size + 1));
		if (!p) {
			pthread_mutex_unlock(&self->lock);
			return STR_NOMEM;
		}

		self->data = p;	
		str_concat(self->data, _data);
	} else {
		self->data = (char *)malloc((size + 1));
		if (!self->data) {
			pthread_mutex_unlock(&self->lock);
			return STR_NOMEM;
		}

		if (str_copy(self->data, _data) != self->data) {
			free(self->data);
			self->data = NULL;
			pthread_mutex_unlock(&self->lock);
			return STR_ERRCPY;
		}
	}

	pthread_mutex_unlock(&self->lock);
	return STR_OK;
}


Str_err_t str_input(str *self)
{
	if (!self) {
		return STR_NULL;
	} else if(self->data != NULL) {
		return STR_INVALID;
	}
	
	pthread_mutex_lock(&self->lock);
	self->data = get_dyn_input(MAX_STRING_SIZE);
	pthread_mutex_unlock(&self->lock);
	return (self->data ? STR_OK : STR_MAXSIZE);
}


Str_err_t str_add_input(str *self)
{
	if (!self) {
		return STR_NULL;
	}

	pthread_mutex_lock(&self->lock);

	if (!self->data) {
		self->data = get_dyn_input(MAX_STRING_SIZE);
		
		if (self->data == NULL) {
			pthread_mutex_unlock(&self->lock);
			return STR_MAXSIZE;
		}
		pthread_mutex_unlock(&self->lock);
		return STR_OK;
	}

	size_t self_data_size = str_length(self->data);

	char *buf = get_dyn_input(MAX_STRING_SIZE - self_data_size);
	if (!buf) {
		pthread_mutex_unlock(&self->lock);
		return STR_ALLOC;
	}

	char *new_data = (char *)realloc(self->data, (self_data_size + str_length(buf) + 1));
	if (!new_data) {
		free(buf);
		pthread_mutex_unlock(&self->lock);
		return STR_ALLOC;
	} else {
		self->data = new_data;
	}

	Str_err_t concat_res = str_nconcat(self->data, buf, strlen(buf));
	if (concat_res != STR_OK) {
		char *res = (char *)realloc(self->data, self_data_size + 1);
		if (res) {
			self->data = res;
		}
		free(buf);
		pthread_mutex_unlock(&self->lock);
		return concat_res;
	}

	free(buf);
	pthread_mutex_unlock(&self->lock);
	return STR_OK;
}



Str_err_t str_pop_back(str *self, char sep)
{
	if (!self) {
		return STR_NULL;
	} else if (!self->data || !str_length(self->data)) {
		return STR_EMPTY;
	}

	pthread_mutex_lock(&self->lock);

	char *p = strrchr(self->data, sep);
	if (!p) {
		pthread_mutex_unlock(&self->lock);
		return STR_FAIL;
	}

	p++;
	*p = '\0';

	char *self_data_ptr = (char *)realloc(self->data, str_length(self->data) + 1); // Trim memory
	if (!self_data_ptr) {
		pthread_mutex_unlock(&self->lock);
		return STR_ALLOC;
	}
	
	self->data = self_data_ptr;
	pthread_mutex_unlock(&self->lock);
	return STR_OK;
}


void str_print(str *self)
{
	if (self) {
		pthread_mutex_lock(&self->lock);
		if (self->data) {
			printf("%s", self->data);
			fflush(stdout);
		}
		pthread_mutex_unlock(&self->lock);
	}
}



size_t str_get_size(const str *self)
{
	if (self) {
    		return (self->data ? str_length(self->data) : 0);
	} else {
		return 0;
	}
}


const char *str_get_data(const str *self)
{
	if (self) {
		if (self->data) {
    			return (const char *)self->data;
		}
	}
	return NULL;
}


void str_clear(str *self)
{
	if (self){
		pthread_mutex_lock(&self->lock);
		if (self->data) {
			free(self->data);
			self->data = NULL;
		}
		pthread_mutex_unlock(&self->lock);
	}
}


void str_free(str *self)
{
	if (self) {
		if (self->data) {
			free(self->data);
			self->data = NULL;
		}
		if (self->is_dynamic) {
			free(self);
			self = NULL;
			pthread_mutex_destroy(&self->lock);
		}
	}
}


char* get_dyn_input(size_t max_str_size)
{
	const int CHUNK_SIZE = 10;
	char* buffer = (char *)malloc(CHUNK_SIZE);
	if (!buffer) 
		return NULL;

	size_t current_size = CHUNK_SIZE; // Size of available memory.
	size_t length = 0; // Length of current string

	char *tmp = NULL;
	int c;
	while ((c = getchar()) != EOF && c != '\n') {
		if (length + 1 >= current_size) { // Expand memory
			current_size += CHUNK_SIZE;			

			tmp = (char *)realloc(buffer, current_size);
			if (!tmp) {
				free(buffer);
				return NULL;
			}
			buffer = tmp;
		}

		if (length >= (max_str_size - 1)) {
			free(buffer);
			return NULL;
		}

		buffer[length++] = (char)c;
		buffer[length] = '\0'; // End the series
	}

	// Finally release the extra memory
	tmp = (char *)realloc(buffer, length + 1);
	if (!tmp) {
		free(buffer);
		return NULL;
	}
	buffer = tmp;
	return buffer;
}


Str_err_t str_rem_word(str *self, const char *needle)
{
	if (!self || !needle) {
		return STR_NULL;
	} else if (!self->data) {
		return STR_EMPTY;
	} 
        
	pthread_mutex_lock(&self->lock);
        size_t self_data_size = str_length(self->data);
        size_t needle_size = str_length(needle);
        
        if (needle_size > self_data_size) {
		pthread_mutex_unlock(&self->lock);
        	return STR_FAIL;
	}
            
        char *L = NULL;
        L = strstr(self->data, needle);
        if(!L) {
		pthread_mutex_unlock(&self->lock);
        	return STR_FAIL;
	}

    	memmove(L, L + needle_size, self_data_size - (L - self->data) - needle_size + 1);
	self->data[self_data_size - needle_size] = '\0';
        
        char *buf = (char*)realloc(self->data, 
                ((self_data_size - needle_size)) +1);
        
	if (!buf) {	// realloc başarısız oldu; ancak kelime diziden kaldırıldı ve sonuna NULL eklendi
		pthread_mutex_unlock(&self->lock);
		return STR_ALLOC;
	}

        if (buf)
        	self->data = buf;

	pthread_mutex_unlock(&self->lock);
	return STR_OK;
}


Str_err_t str_swap_word(str *self, const char *old_word, const char *new_word)
{
	if (!self || !old_word || !new_word)
		return STR_NULL;
	else if (!self->data)
		return STR_EMPTY;

	pthread_mutex_lock(&self->lock);

	size_t self_data_size = str_length(self->data);
	size_t old_word_size = str_length(old_word);
	size_t new_word_size = str_length(new_word);
	size_t result_length = 0;
	char *old_word_pos = NULL;
	char *buf = NULL;

	old_word_pos = strstr(self->data, old_word);
	if (!old_word_pos) {
		pthread_mutex_unlock(&self->lock);
		return STR_FAIL;
	}

	result_length = self_data_size - old_word_size + new_word_size;
	buf = (char *)malloc(sizeof(char) * (result_length + 1)); // +1 for null terminator
	if (!buf) {
		pthread_mutex_unlock(&self->lock);
		return STR_ALLOC;
	}

	// Copy everything before word1
	Str_err_t err =  str_ncopy(buf, self->data, old_word_pos - self->data);
	if (err != STR_OK) {
#if STRDEBUGMODE == ON
		str_check_err(err, "str_swap_word --> Str_err_t err =  str_ncopy(buf, self->data, old_word_pos - self->data)");
#endif
		free(buf);
		return err;
	}
	buf[old_word_pos - self->data] = '\0'; // Null terminate the buffer

	// Copy word2
	err = str_concat(buf, new_word);
	if (err != STR_OK) {
#if STRDEBUGMODE == ON
		str_check_err(err, "str_swap_word --> Str_err_t err = str_concat(buf, new_word)");
#endif
		free(buf);
		return err;
	}

	// Copy everything after word1
	err = str_concat(buf, old_word_pos + old_word_size);
	if (err != STR_OK) {
#if STRDEBUGMODE == ON
		str_check_err(err, "str_swap_word --> Str_err_t err = str_concat(buf, old_word_pos + old_word_size)");
#endif
		free(buf);
		return err;
	}

	free(self->data);
	self->data = buf;

	pthread_mutex_unlock(&self->lock);
	return STR_OK;
}


Str_err_t str_to_upper(str *self)
{
	if (!self) {
		return STR_NULL;
	} else if (!self->data) {
		return STR_EMPTY;
	}
	pthread_mutex_lock(&self->lock);

	char *p = self->data;
	while (*p) {
		if ((*p >= 'a') && (*p <= 'z'))
			*p &= ~(1 << 5);
		p++;
	}
	pthread_mutex_unlock(&self->lock);
	return STR_OK;
}


Str_err_t str_to_lower(str *self)
{
	if (!self)
		return STR_NULL;
	if (!self->data)
		return STR_EMPTY;
	
	pthread_mutex_lock(&self->lock);
	char *p = self->data;
	while (*p) {
		if ((*p >= 'A') && (*p <= 'Z'))
			*p |= (1 << 5); // yes, faster than tolower :/
		p++;
	}

	pthread_mutex_unlock(&self->lock);
	return STR_OK;
}


Str_err_t str_to_title_case(str *self)
{
	if (!self)
		return STR_NULL;
	if (!self->data || !str_length(self->data))
		return STR_EMPTY;
	
	pthread_mutex_lock(&self->lock);

	char *p = self->data;
	short flag = 1;

	while (*p) {
		if (flag && (*p >= 'a') && (*p <= 'z')) {
			*p &= ~(1 << 5);
			flag = 0;
		} else if (*p == ' ') {
			flag = 1;
		}
		p++;
	}

	pthread_mutex_unlock(&self->lock);
	return STR_OK;
}

Str_err_t str_reverse(str *self)
{
	if (!self)
		return STR_NULL;
	else if (!self->data)
		return STR_NULL;
	else if (!str_length(self->data))
		return STR_EMPTY;
    
	pthread_mutex_lock(&self->lock);
	char buf = 0;
	size_t head = 0;
	size_t tail = str_length(self->data) - 1;

	while (head < tail) {
		buf = self->data[head];
		self->data[head] = self->data[tail];
		self->data[tail] = buf;
		head++;
		tail--;
	}

	pthread_mutex_unlock(&self->lock);
	return STR_OK;
}

bool str_is_empty(str *self)
{
	if (self){
		if (!self->data){
			return true;
		} else if (!str_length(self->data)) {
			return true;
		}
	}
	return false;
}


static char *str_copy(char *dest, const char *source)
{
	char *p = dest;
	while((*p++ = *source++) != '\0')
		/* :) */;
	
	return dest;
}


static Str_err_t str_concat(char *dest, const char *source)
{
	if (!dest || !source)
		return STR_NULL;

	char *p = dest;
	while (*p)
		p++;

	while ((*p = *source++) != '\0')
		p++;
	
	return STR_OK;
}


static Str_err_t str_nconcat(char *dest, const char *src, size_t n)
{
	if (!dest || !src)
		return STR_NULL;
	else if ( n < 1)
		return STR_INVALID;
	
	size_t src_size = str_length(src);
	if (n > src_size)
		return STR_INVALID;
	
	while (*dest)
		dest++;

	while (n) {
		*dest++ = *src++;
		n--;
	}
	*dest = '\0';

	return STR_OK;
}

static Str_err_t str_ncopy(char *dest, const char *src, size_t n)
{
	if (!dest || !src)
		return STR_NULL;
	else if (n < 1)
		return STR_INVALID;
	
	while (n) {
		*dest++ = *src++;
		n--;
	}
	*dest = '\0';
	return STR_OK;
}


static size_t str_length(const char *s)
{
	if (!s)
		return 0;

	size_t length = 0;
	while(*s++)
		length++;

	return length;
}

int str_check_err (Str_err_t Error, const char *user_message)
{
	bool user_message_flag = false;
	if (user_message)
		user_message_flag = true;

	if (Error < 0)
		fprintf(stderr, "str_err is invalid\n");
	else if (user_message_flag)
		fprintf(stderr, "ERR: %s\n", user_message);

	switch (Error)
	{
	case STR_OK:
		break;
	case STR_NULL:
		if (user_message_flag) {
                	fprintf(stderr, "Error: STR_NULL - %s\n", user_message);
		} else {
			fprintf(stderr, "Error: STR_NULL\n");
		}
                break;
            case STR_INVALID:
                if (user_message_flag) {
                	fprintf(stderr, "Error: STR_INVALID - %s\n", user_message);
		} else {
			fprintf(stderr, "Error: STR_INVALID\n");
		}
                break;
            case STR_NOMEM:
                if (user_message_flag) {
                	fprintf(stderr, "Error: STR_NOMEM - %s\n", user_message);
		} else {
			fprintf(stderr, "Error: STR_NOMEM\n");
		}
                break;
            case STR_ERRCPY:
                if (user_message_flag) {
                	fprintf(stderr, "Error: STR_ERRCPY - %s\n", user_message);
		} else {
			fprintf(stderr, "Error: STR_ERRCPY\n");
		}
                break;
            case STR_MAXSIZE:
                if (user_message_flag) {
                	fprintf(stderr, "Error: STR_MAXSIZE - %s\n", user_message);
		} else {
			fprintf(stderr, "Error: STR_MAXSIZE\n");
		}
                break;
            case STR_ALLOC:
                if (user_message_flag) {
                	fprintf(stderr, "Error: STR_ALLOC - %s\n", user_message);
		} else {
			fprintf(stderr, "Error: STR_ALLOC\n");
		}
                break;
            case STR_EMPTY:
                if (user_message_flag) {
                	fprintf(stderr, "Error: STR_EMPTY - %s\n", user_message);
		} else {
			fprintf(stderr, "Error: STR_EMPTY\n");
		}
                break;
            case STR_FAIL:
                if (user_message_flag) {
                	fprintf(stderr, "Error: STR_FAIL - %s\n", user_message);
		} else {
			fprintf(stderr, "Error: STR_FAIL\n");
		}
                break;
            default:
                if (user_message_flag) {
                	fprintf(stderr, "Unknown error - %s\n", user_message);
		} else {
			fprintf(stderr, "Unknown error\n");
		}
                break;
        }

	return 0;
}


#endif /* _STRUTIL_H_ */
