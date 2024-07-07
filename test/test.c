#include <stdio.h>
#include <string.h>

#include "strutil.h"

#define STR_PRINTERR() do {											\
	fprintf(stderr, "\033[31m%s failed, file: %s, line: %d\033[0m\n", __func__, __FILE__, __LINE__);	\
} while (0)

unsigned int test_count = 1;

str *test_str_init()
{
	str *s = str_init();
	if (s == NULL || s->is_dynamic != 1) {
		STR_PRINTERR();
		str_clear(s);
		return NULL;
	}
	printf("Test %d test_str_init test passed\n", test_count++);
	fflush(stdout);
	return s;
}

void test_str_add(str *s)
{
	if (s == NULL || s->data != NULL) {
		STR_PRINTERR();
		return;
	}
	if (str_add(s, "Hello") != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	if (strcmp(s->data, "Hello") != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}

	str_clear(s);
	printf("Test %d test_str_add test passed\n", test_count++);
	fflush(stdout);
}

void test_str_input(str *s)
{
	if (s == NULL || s->data != NULL) {
		STR_PRINTERR();
		return;
	}
	printf("test_str_input, write \"Hello\" and press enter: ");
	fflush(stdout);

	int res = str_input(s);
	if (res != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}

	if (strcmp(s->data, "Hello") != 0) {
		STR_PRINTERR();
		fprintf(stderr, "expected: \"Hello\", entered: %s\n", s->data);
		str_clear(s);
		return;
	}
	str_clear(s);
	printf("Test %d test_str_input passed\n", test_count++);
	fflush(stdout);
}

void test_str_pop_back(str *s)
{
	if (s == NULL || s->data != NULL) {
		STR_PRINTERR();
		return;
	}
	int res = str_add(s, "Hello");
	if (res) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}

	int res2 = str_add(s, " ");
	if (res2) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}

	int res3 = str_add(s, "World");
	if (res3) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}

	if (str_pop_back(s, ' ') != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	if (strcmp(s->data, "Hello ") != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	str_clear(s);
	printf("Test %d test_str_input passed\n", test_count++);
	fflush(stdout);
}

void test_str_get_size(str *s)
{
	if (s == NULL || s->data != NULL) {
		STR_PRINTERR();
		return;
	}
	if (str_add(s, "Hello") != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	if (str_get_size(s) != 5) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	str_clear(s);
	printf("Test %d test_str_input passed\n", test_count++);
	fflush(stdout);
}

void test_str_rem_word(str *s)
{
	if (s == NULL || s->data != NULL) {
		STR_PRINTERR();
		return;
	}
	if (str_add(s, "Hello World") != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	if (str_rem_word(s, "World") != 0) {
		STR_PRINTERR();
		return;
	}
	if (strcmp(s->data, "Hello ") != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	str_clear(s);
	printf("Test %d test_str_input passed\n", test_count++);
	fflush(stdout);	
}

void test_str_swap_word(str *s)
{
	if (s == NULL || s->data != NULL) {
		STR_PRINTERR();
		return;
	}

	if (str_add(s, "Hello World") != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	if (str_swap_word(s, "Hello", "Hi") != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	if (strcmp(s->data, "Hi World") != 0) {
		STR_PRINTERR();
		str_clear(s);
		return;
	}
	str_clear(s);
	printf("Test %d test_str_input passed\n", test_count++);
	fflush(stdout);	
}

int main()
{
	str *s = test_str_init();
	if (!s)
		return EXIT_FAILURE;

	test_str_add(s);
	test_str_input(s);
	test_str_pop_back(s);
	test_str_get_size(s);
	test_str_rem_word(s);
	test_str_swap_word(s);
	
	str_free(s);
	return 0;
}
