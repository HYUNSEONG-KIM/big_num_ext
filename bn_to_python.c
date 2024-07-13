#include <Python.h>

#include "bn.h"
#include "bn_ext.h"

/* To python*/
//PyObject* big_num_to_pyint(const bn * n);
// pyint_to_big_num(const bn *n);



PyObject* bignum_to_pyint(const struct bn * n) {
    // Create a string to hold the hexadecimal representation of the bit array
    char *hexstr = (char *)malloc(bitarray_size * 2 + 1);
    if (!hexstr) {
        return PyErr_NoMemory();
    }

    // Convert bit array to hexadecimal string
    for (size_t i = 0; i < bitarray_size; i++) {
        sprintf(&hexstr[i * 2], "%02x", bitarray[i]);
    }

    hexstr[bitarray_size * 2] = '\0';

    // Convert the hexadecimal string to a Python integer
    PyObject *pyint = PyLong_FromString(hexstr, NULL, 16);
    free(hexstr);

    if (!pyint) {
        return NULL;
    }

    return pyint;
}

