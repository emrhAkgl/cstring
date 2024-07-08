#include "strutil.h"
#include<stdio.h>

int main()
{
	str *name = NULL;
	int res = 0;
	int res2 = 0;

	name = str_init();
	if (!name)
		return 1;
	
	printf("Name: ");
	fflush(stdout);
	res = str_input(name);

	if (!!res) {
		fprintf(stderr, "str_add_input hatası %d\n", res);
		str_free(name);
		return 1;
	}
	str_to_title_case(name);
	
	str_print(name);
	printf("\n\nres: %d\nres2: %d\n", res, res2);
	str_free(name);

	return 0;
}
