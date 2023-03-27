## Dependencies:
<https://github.com/IAKOBVS/pp_macros>
<br>
Change
```
#include "/home/james/pp_macros/pp_va_args_macros.h"
```
in jarr.h to

```
#include "/path/to/pp_macros/pp_va_args_macros.h"
```

Compile jarr.c into an object file with

```
gcc -c jarr.c
```

Include jarr.h when using it in your program.
