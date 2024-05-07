#include <stdio.h>
#include <string.h>
#include "strutil.h"

void test_str_init()
{
	str *s = str_init();
	if (s == NULL) {
		printf("str_init test failed: returned NULL\n");
		return;
	}
	if (s->data != NULL) {
		printf("str_init test failed: data member not initialized to NULL\n");
		return;
	}
	if (s->is_dynamic != 1) {
		printf("str_init test failed: is_dynamic member not set to 1\n");
		return;
	}
	str_free(s);
	printf("str_init test passed\n");
}

void test_str_add()
{
	str *s = str_init();
	if (s == NULL) {
		printf("str_add test failed: str_init failed\n");
		return;
	}
	if (str_add(s, "Hello") != 0) {
		printf("str_add test failed: unable to add string\n");
		str_free(s);
		return;
	}
	if (strcmp(s->data, "Hello") != 0) {
		printf("str_add test failed: incorrect string added\n");
		str_free(s);
		return;
	}
	str_free(s);
	printf("str_add test passed\n");
}

void test_str_pop_back()
{
	str *s = str_init();
	if (s == NULL) {
		printf("str_pop_back test failed: str_init failed\n");
		return;
	}
	str_add(s, "Hello");
	str_add(s, " ");
	str_add(s, "World");
	if (str_pop_back(s, ' ') != 0) {
		printf("str_pop_back test failed: unable to remove separator\n");
		str_free(s);
		return;
	}
	if (strcmp(s->data, "Hello") != 0) {
		printf("str_pop_back test failed: incorrect string after removal\n");
		str_free(s);
		return;
	}
	str_free(s);
	printf("str_pop_back test passed\n");
}

void test_str_get_size()
{
	str *s = str_init();
	if (s == NULL) {
		printf("str_get_size test failed: str_init failed\n");
		return;
	}
	if (str_add(s, "Hello") != 0) {
		printf("str_get_size test failed: str_add failed\n");
		str_free(s);
		return;
	}
	if (str_get_size(s) != 5) {
		printf("str_get_size test failed: incorrect size returned\n");
		str_free(s);
		return;
	}
	str_free(s);
	printf("str_get_size test passed\n");
}

void test_str_rem_word()
{
	str *s = str_init();
	if (s == NULL) {
		printf("str_rem_word test failed: str_init failed\n");
		return;
	}
	if (str_add(s, "Hello World") != 0) {
		printf("str_rem_word test failed: str_add failed\n");
		str_free(s);
		return;
	}
	if (str_rem_word(s, "World") != 0) {
		printf("str_rem_word test failed: unable to remove word\n");
		str_free(s);
		return;
	}
	if (strcmp(s->data, "Hello ") != 0) {
		printf("str_rem_word test failed: incorrect string after removal\n");
		str_free(s);
		return;
	}
	str_free(s);
	printf("str_rem_word test passed\n");
}

void test_str_swap_word()
{
	str *s = str_init();
	if (s == NULL) {
		printf("str_swap_word test failed: str_init failed\n");
		return;
	}
	if (str_add(s, "Hello World") != 0) {
		printf("str_swap_word test failed: str_add failed\n");
		str_free(s);
		return;
	}
	if (str_swap_word(s, "Hello", "Hi") != 0) {
		printf("str_swap_word test failed: unable to swap word\n");
		str_free(s);
		return;
	}
	if (strcmp(s->data, "Hi World") != 0) {
		printf("str_swap_word test failed: incorrect string after swap\n");
		str_free(s);
		return;
	}
	str_free(s);
	printf("str_swap_word test passed\n");
}

int main()
{
	test_str_init();
	test_str_add();
	test_str_pop_back();
	test_str_get_size();
	test_str_rem_word();
	test_str_swap_word();
	
	return 0;
}
