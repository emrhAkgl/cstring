# xstring

The xstring library was written in C for a string approach similar to that in C++, but much less professional. 
Note that this is a personal project. The project file consists of a single .h file and is written on Linux. 

The string structure is currently 72 bytes in size on 64-bit GNU/Linux due to the function pointers it contains. 
I have to put up with this to give an OOP approach to the string structure. 

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

	printf("\n");
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
}
```

## Build On GNU/Linux
Copy your xstring.h file, preferably to the same directory as your main.c file. Create a file named "CMakeLists.txt":
```bash
touch CMakeLists.txt
```

And edit your file as follows
```cmake
cmake_minimum_required(VERSION 3.10)

project(example_project)

add_compile_options(-Wall -Wextra -std=c11)

add_executable(example main.c)

target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

Then create a folder called "build" to compile our file and go inside the folder:
```bash
mkdir build
cd build
```

You can compile your files as follows: 
```bash
cmake ..
make
```

If you do not receive any error, your file is ready to run:
```bash
./example
```

That's all :)

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[unlicense](https://unlicense.org/)
