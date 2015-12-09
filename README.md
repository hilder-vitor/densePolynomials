# densePolynomials
A simple library for dense-polynomials arithmetic

## Dependencies

* The GNU Multiple Precision Arithmetic Library (https://gmplib.org/). It must be installed with support to its C++ interface, which means that you have to build this lib with the flag *-enable-cxx*. See the GMP's documentation for futher information. 

* Any C++ compiler that supports the C++11

* [Optional] If you want to run the tests, then you must use GoogleTest (https://github.com/google/googletest). To do so, create a directory called googletest inside tests/ and decompress the googletest lib inside tests/googletest. Then, run the tests/Makefile. 

## How to use

The following code creates some polynomials and operates over them:

```C++
  #include"poly.h"
  #include<iostream>
  
  int main(){
    Poly a; // default constructor
    a.set(2, 1233); // setting the second coefficient (so a(x) = 1233*x^2)
    a.set(3, -92938199292929293888439311221); // now a(x) = -92938199292929293888439311221*x^3 + 1233*x^2
    
    Poly b(50); // using this constructor because I know that b will has degree 50
    for (unsigned int i = 0; i <= 50; i++){
      b.set(i, i % 3); // setting all the coefficients to values 0, 1, and 2
    }
    
    Poly c("+2x^10 - 3x^11 + 9x^13 - 4x^14"); // creating polynomial from a string
    
    Poly d = a + b;
    Poly e = c * d;
    
    std::cout << e << std::endl;
    
    return 0;
```

If you want to make some calculations using polynomials without writting your own program, just use the command *make* to compile the project and run

```bash
./calc
```

it will open a *very simple* shell on which you can define polynomials associating them to letters like that

```bash
>> a := +1x^3 - 2x^4
>> k := +512x^50 - 42x^13 + 3333x^42
```

and operates over them like that
```bash
>> b = a + k
>> c = b * a
```



