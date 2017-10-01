#ifndef MRB_SECURE_WIPE_H
#define MRB_SECURE_WIPE_H

#include <mruby/secure_wipe_memory.h>
#ifdef _MSC_VER
#include <Windows.h>
#endif
#define VC_GE_2005(version) (version >= 1400)
#include <string.h>

#if (defined(__has_attribute) && __has_attribute(optnone)||defined(__clang__) && __has_attribute(optnone))
#define NOT_OPTIMIZED __attribute__((optnone))
#elif defined(__GNUC__)
#define GCC_VERSION                                                            \
    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if GCC_VERSION >= 40400
#define NOT_OPTIMIZED __attribute__((optimize("O0")))
#endif
#endif
#ifndef NOT_OPTIMIZED
#define NOT_OPTIMIZED
#endif

#endif
