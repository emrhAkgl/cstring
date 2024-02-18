# c_string

The c_string library was written in C for a string approach similar to that in C++, but much less professional. 
Note that this is a personal project. 

## Installation

You can download the library directly from 
```
https://github.com/emrhAkgl/cstring
```
or you can use the 
```bash
git clone https://github.com/emrhAkgl/cstring
```


## Usage

```c
#include "c_string.h"

int main(int argc, char **argv)
{
	string *names = init_string();	
	char *name = "Emrah Akgul";
	char *name2 = "Serdar Aksu";

	names->add_string(names, name);
	names->add_string(names, name2);

	names->print(names);

	names->free_string(names);

	return 0;
}
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[unlicense](https://unlicense.org/)
