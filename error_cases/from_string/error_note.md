
- Data: July 27th 2024
- Error module: `bignum_from_string`
- module location: original bignum library
- Problem: The module made weird bit-string.
- Error situation: When the given string length exceeds `(sizeof(DTYPE) * 2)` the error occurred.
- Description: This is occurred because the library was not designed to  convert arbitrary length string. We have to match the string length to the bignum unit.