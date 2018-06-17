# Notebook

I try to learn some basic knowledge about how to build a c/c++ project while building this toy project Codeep. Some references are listed as follows.

## Conditional Compile

## *boost::program_options*
This is a argument parser library in *boost*. See tutorial [here](https://www.boost.org/doc/libs/1_63_0/doc/html/program_options/tutorial.html). 
### About *namespace*
```C++
namespace po = boost::program_options
```
just looks like
```python
import boost.program_options as po
```

## Macro Function
Macros are **pre-processed** which means that all the macros would be processed before your program compiles. However, functions are not **preprocessed but compiled**. In short, you can regard macro as a naive replacement, which makes macro 'faster' than functions in some cases.


## Makefile

