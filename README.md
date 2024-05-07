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

```c
#include <stdio.h>
#include "strutil.h"

int main() {
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
    printf("\nModified String: %s\n", str_get_data(my_string);

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
