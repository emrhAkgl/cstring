[![Tested on Linux](https://img.shields.io/badge/Tested%20on-Linux-green.svg)](https://github.com/akgulemrah/strutil)

# strutil

Strutil.h is a simple and useful header file for text processing functions in the C programming language. This header file contains a set of functions that facilitate text processing tasks and provide dynamic memory management.

Functions include adding text, taking input from the user, removing a specific word from the text, printing the text, getting the size of the text, and more. Additionally, memory operations required for dynamic memory management are automatically handled.

This header file offers a quick and efficient solution for C programmers to streamline text processing tasks.

## Installation

You can download the library directly from 
```
https://github.com/akgulemrah/strutil
```
or you can use the 
```bash
git clone https://github.com/akgulemrah/strutil
```


## Usage
First of all, the examples here assume that you only save the header file (strutil.h) in your directory. 
If you downloaded the repo using git, you can delete files other than strutil.h and follow the steps below. 

```c
#include <stdio.h>
#include "strutil.h"

int main(int argc, char **argv)
{
	// Initialize a new Str structure
	str *my_string = str_init();

	// Add some strings to the Str structure
	str_add(my_string, "Hello");
	str_add(my_string, " ");
	str_add(my_string, "world!");

	// Print the string in the Str structure
	printf("Original String: ");
	str_print(my_string);

	// Remove the word "world" from the string
	str_rem_word(my_string, "world");

	// Print the modified string
	printf("\nModified String: %s\n", str_get_data(my_string));

	// Free the memory allocated for the Str structure
	str_free(my_string);

	return 0;
}
```

## Build On GNU/Linux
Copy your strutil.h file, preferably to the same directory as your main.c file. Create a file named "CMakeLists.txt":
```bash
touch CMakeLists.txt
```

And edit your file as follows
```cmake
cmake_minimum_required(VERSION 3.0)
project(StrUtil C)

set(HEADERS
	strutil.h
)

set(SOURCES
	main.c
)

add_executable(strutil ${SOURCES})

target_include_directories(strutil PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

You can compile your files as follows: 
```bash
mkdir build
cd build
cmake ..
make
```

If you do not receive any error, your file is ready to run:
```bash
./strutil
```

That's all :)

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## Disclaimer

This software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, or non-infringement. In no event shall the authors or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, arising from, out of, or in connection with the software or the use or other dealings in the software.

## Usage Risks

Please be aware that this software may contain bugs, security vulnerabilities, or other issues. It is your responsibility to test and validate the software before using it in any critical or production environment. The authors do not assume any responsibility for any issues that may arise from the use of this software.

## License

[unlicense](https://unlicense.org/)
