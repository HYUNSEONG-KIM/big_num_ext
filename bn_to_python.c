#include "bn_python.h"

PyObject *
_PyLong_FromBignum(const struct bn *bignum_obj) {
    char hex_str[HEX_STR_SIZE];
    bignum_to_string(bignum_obj, hex_str, HEX_STR_SIZE);

    // Use base 16 to convert the hexadecimal string to a PyLongObject
    PyObject *py_long = PyLong_FromString(hex_str, NULL, 16);
    
    return py_long;
}

// Function to convert PyLongObject to bignum
int _Bignum_FromPyLong(PyObject *obj, struct bn * bignum_obj) {
    if (!PyLong_Check(obj)) {
        PyErr_SetString(PyExc_TypeError, "Expected a PyLongObject");
        return -1;
    }

    // Get a hex string
    PyObject * pystr = PyObject_Format(obj, PyUnicode_FromString("0x"));
    if (!pystr) {
        PyErr_Print();
        Py_DECREF(pystr);
        return -1;
    }
    // Calculate bing_num length unit
    Py_ssize_t cstr_len = PyUnicode_GET_LENGTH(pystr);
    Py_DECREF(pystr);
    const size_t str_unit = (sizeof(DTYPE) * 2);
    int buff_len = 0;
    int buff_factor = cstr_len/str_unit, b=cstr_len%str_unit;
    char format_str[HEX_STR_SIZE];
    buff_factor = (b==0) ? buff_factor : buff_factor+1;
    buff_len  = buff_factor*str_unit;

    // Specific formatter
    sprintf(format_str, "0%dx", buff_len);
    // Generate hex string with fixed point.
    PyObject *pystr2 = PyObject_Format(obj, PyUnicode_FromString(format_str));
    if (!pystr2) {
        PyErr_Print();
        Py_DECREF(pystr2);
        return -1;
    }
    // Get a hex string in C array.
    const char *cstr = PyUnicode_AsUTF8(pystr2);
    if (!cstr) {
        PyErr_Print();
        Py_DECREF(pystr2);
        return -1;
    }

    bignum_from_string(bignum_obj, cstr, buff_len);

    return 0;
}