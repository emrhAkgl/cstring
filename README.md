# xstring

The xstring library was written in C for a string approach similar to that in C++, but much less professional. 
Note that this is a personal project. 

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

int main(int argc, char **argv)
{
	string *names = init_string();	
	char *name = "Emrah Akgul";
	char *name2 = "Vladislav Polyanskiy";

	names->add(names, name);
	names->add(names, name2);

	names->print(names);

	names->free(names);

	return 0;
}
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[unlicense](https://unlicense.org/)
