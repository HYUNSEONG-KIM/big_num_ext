


- Data: July 27th 2024
- Error module: `_PyLong_FromBignum`
- module location: Python interface
- Problem: When bignum struct contains zero, the numbers are not properly converted to the python integer.
- Error situation: Same with problem
- Solution: `bignum_to_string` module was a problem. If the `0` was given, the function return empty string.


### Error code

```
PyObject *
_PyLong_FromBignum(const struct bn *bignum_obj) {
    char hex_str[HEX_STR_SIZE];
    bignum_to_string((struct bn *)bignum_obj, hex_str, HEX_STR_SIZE);

    // Use base 16 to convert the hexadecimal string to a PyLongObject
    PyObject *py_long = PyLong_FromString(hex_str, NULL, 16);
    
    return py_long;
}
```

The above has no problem. 
In `bn.c`, `bignum_to_string` function,

```
/* Count leading zeros: */
  j = 0;
  while (str[j] == '0')
  {
    j += 1;
  }
  /* Move string j places ahead, effectively skipping leading zeros */ 
    for (i = 0; i < (nbytes - j); ++i)
    {
      str[i] = str[i + j];
    }

    /* Zero-terminate string */
    str[i] = 0;
```
was changed to 
```
/* Count leading zeros: */
  j = 0;
  while (str[j] == '0')
  {
    j += 1;
  }

// Detect the bignum data is whether zero or not.
  // (*)
  if(j == 2*BIG_NUM_BYTES)
  {
    str[0]='0'; str[1]='\0';
  }
  else
  {
    /* Move string j places ahead, effectively skipping leading zeros */ 
    for (i = 0; i < (nbytes - j); ++i)
    {
      str[i] = str[i + j];
    }

    /* Zero-terminate string */
    str[i] = 0;

  }
```