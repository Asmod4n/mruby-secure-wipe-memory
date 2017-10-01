#ifndef MRB_SECURE_WIPE_MEMORY_H
#define MRB_SECURE_WIPE_MEMORY_H

#define __STDC_WANT_LIB_EXT1__ 1

#include <mruby.h>

MRB_BEGIN_DECL

MRB_API void
mrb_secure_wipe_memory(void *v, size_t n);

MRB_END_DECL

#endif
