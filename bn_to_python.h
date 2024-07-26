#include "bn.h"
#include "bn_ext.h"
#include <Python.h>


#define HEX_STR_SIZE BN_ARRAY_SIZE*(2*WORD_SIZE) + 1

PyObject * _PyLong_FromBignum(const struct bn *bignum_obj) ;
int _Bignum_FromPyLong(PyObject *obj, struct bn *bignum_obj);