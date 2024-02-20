# xstring

The xstring library was written in C for a string approach similar to that in C++, but much less professional. 
Note that this is a personal project. The project file consists of a single .h file and is written on Linux. 

## Installation

You can download the library directly from 
```
https://github.com/emrhAkgl/xstring
```
or you can use the 
```bash
git clone https://github.com/emrhAkgl/xstring
```


## Usage

```c
#include "xstring.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	char *str1 = "Hello";
	char *str2 = "World!";
	char *str3 = "what's up?";
	char *answ = "Good :)";

	string *hi = init_string();
	if (!hi) {	
		fprintf(stderr, "init_string returned NULL");
		return 1;
	}

	hi->add(hi, str1); 
	hi->add(hi, str2); 
	hi->add(hi, str3); 

	hi->print(hi); /* Hello World! What's up? */

	hi->clear(hi);

	(*hi).add(hi, answ);

	const char *data = hi->get_data(hi);

	/* Good :) */
	/* hi size: 7 */
	printf("\n%s\nhi size: %lu\n", data, hi->get_size(hi));
	/*					|		*/
	/*					V		*/
	/*				strlen(hi->data)	*/

	hi->free(hi);
	return 0;
}```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[unlicense](https://unlicense.org/)
