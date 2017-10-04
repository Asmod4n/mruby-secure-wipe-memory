# mruby-secure-wipe-memory

Securely wipes the memory contents of Strings, Data, C pointer or Array Objects.

Ruby example
```ruby
s = "hello"
secure_wipe_memory s
```
C example
```c
#include <mruby/secure_wipe_memory.h>
char *s = strdup("hello");
mrb_secure_wipe_memory(s, strlen(s));
```
