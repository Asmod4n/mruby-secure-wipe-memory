#include "mrb_secure_wipe.h"
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/array.h>

MRB_API void NOT_OPTIMIZED
mrb_secure_wipe_memory(void *v, size_t n)
{
#if defined(_MSC_VER) && VC_GE_2005(_MSC_VER)
    SecureZeroMemory(v, n);
#elif defined(__STDC_LIB_EXT1__)
    mrb_assert(memset_s(v, n, 0, n) == 0);
#elif defined(__OpenBSD__)
    explicit_bzero(v, n);
#else
    static void *(*const volatile memset_sec)(void *, int, size_t) = &memset;
    memset_sec(v, 0, n);
#endif
}

static mrb_value
mrb_secure_wipe_memory_m(mrb_state *mrb, mrb_value secure_wipe_mod)
{
  mrb_value object;
  mrb_int len = 0;
  mrb_bool len_given = FALSE;
  mrb_get_args(mrb, "o|i?", &object, &len, &len_given);

  switch(mrb_type(object)) {
    case MRB_TT_STRING: {
      if (len_given) {
        mrb_assert_int_fit(mrb_int, len, size_t, SIZE_MAX);
        mrb_assert(len <= RSTRING_CAPA(object)||len <= RSTRING_LEN(object));
        mrb_secure_wipe_memory(RSTRING_PTR(object), len);
      } else {
        mrb_secure_wipe_memory(RSTRING_PTR(object), RSTRING_CAPA(object));
      }
    } break;
    case MRB_TT_DATA: {
      if (!len_given) mrb_raise(mrb, E_ARGUMENT_ERROR, "no len given");
      mrb_assert_int_fit(mrb_int, len, size_t, SIZE_MAX);
      mrb_secure_wipe_memory(DATA_PTR(object), len);
    } break;
    case MRB_TT_CPTR: {
      if (!len_given) mrb_raise(mrb, E_ARGUMENT_ERROR, "no len given");
      mrb_assert_int_fit(mrb_int, len, size_t, SIZE_MAX);
      mrb_secure_wipe_memory(mrb_cptr(object), len);
    } break;
    case MRB_TT_ARRAY: {
      if (len_given) {
        mrb_assert_int_fit(mrb_int, len, size_t, SIZE_MAX);
        mrb_assert(len <= ARY_CAPA(RARRAY(object))||len <= RARRAY_LEN(object));
        mrb_secure_wipe_memory(RARRAY_PTR(object), len * sizeof(mrb_value));
      } else {
        mrb_secure_wipe_memory(RARRAY_PTR(object), ARY_CAPA(RARRAY(object)) * sizeof(mrb_value));
      }
    } break;
    default: {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "can only wipe string, data, cptr or array objects");
    }
  }

  return object;
}

void
mrb_mruby_secure_wipe_memory_gem_init(mrb_state *mrb)
{
  mrb_define_module_function(mrb, mrb_define_module(mrb, "SecureWipeMemory"), "wipe", mrb_secure_wipe_memory_m, MRB_ARGS_ARG(1, 1));
}

void mrb_mruby_secure_wipe_memory_gem_final(mrb_state *mrb) {}
