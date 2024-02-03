#include <stdio.h>
#include "mystring.h"

void test_init_string()
{
        string *test_string = init_string();
        if(!test_string) {
                fprintf(stderr, "test_init_string: hafıza tahsis edilemedi.\n");
        } else {
                free(test_string);
        }
}
