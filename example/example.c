
#include <stdio.h>
#include "strutil.h"

int main (void)
{
	char name_list[3][10] = {"Emrah", "Vladislav", "Celil"};
	Str_err_t str_err;

	str *names = str_init();
	if (names == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 3; i++) {
		str_err = str_add(names, name_list[i]);
		if (str_err != STR_OK) {
			str_check_err(str_err, "axample.c -> str_err = str_add(names, name_list[i])");
			str_free(names);
			return EXIT_FAILURE;
		}

		if (i != 2) {
			str_err = str_add(names, " ");
			if (str_err != STR_OK) {
				str_free(names);
				return EXIT_FAILURE;
			}
		}
	}

	printf("names: %s.\n", str_get_data(names));
	//Emrah Vladislav Celil.

	// Or you can use 'if (str_err)' instead of 
	//'if (str_err != STR_OK)', because STR_OK is defined as 0
	str_err = str_rem_word(names, "islav");
	if (str_err) {
		str_check_err(str_err, "example.c -> str_rem_word failed");
		return EXIT_FAILURE;
	} else {
		printf("names: %s.\n", str_get_data(names));
		//Emrah Vlad Celil.
	}

	str_err = str_swap_word(names, "Celil", "Nazmiye");
	if (str_err) {
		str_check_err(str_err, "example.c -> str_swap_word failed");
	}

	printf("result of main : %s\n", str_get_data(names));
	str_free(names);
	return 0;
}
