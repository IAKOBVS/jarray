## Dependencies:
<https://github.com/IAKOBVS/pp_macros>
<br>
Change
```
#include "/home/james/pp_macros/pp_va_args_macros.h"
```
in jstr.h to

```
#include "/path/to/pp_macros/pp_va_args_macros.h"
```

Compile jstr.c into an object file with

```
gcc -c jstr.c
```

Include jarr.h when using it in your program.
