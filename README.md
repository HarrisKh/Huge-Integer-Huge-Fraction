# HugeInteger and HugeFraction - C++ Project

## Overview

This project implements custom `HugeInteger` and `HugeFraction` classes in C++.

The main idea is to perform arithmetic on integers that can be much larger than the normal C++ integer types. Instead of storing the number in `int` or `long long`, `HugeInteger` stores every digit separately in a `vector<int>`.

`HugeFraction` is built on top of `HugeInteger`, allowing fractions with very large numerators and denominators.

The project also demonstrates operator overloading, constructors, comparison operators, file input, and object-oriented programming.

---

## Files

```text
BSAI25066-Project 3
|
+-- BSAI25066-Main.cpp
+-- HugeInteger.h
+-- HugeInteger.cpp
+-- HugeFraction.h
+-- HugeFraction.cpp
```

### `HugeInteger.h`

Contains the declaration of the `HugeInteger` class, its constructors, helper functions, arithmetic operators, comparison operators, and stream operators.

### `HugeInteger.cpp`

Contains the actual implementation of `HugeInteger`.

### `HugeFraction.h`

Contains the declaration of the `HugeFraction` class.

### `HugeFraction.cpp`

Implements fraction arithmetic using `HugeInteger`.

### `BSAI25066-Main.cpp`

Contains the test program. The active main program tests `HugeInteger`. A separate `HugeFraction` test is also included in the file but is commented out.

---

# HugeInteger

## Why HugeInteger?

Normal C++ integer types have a fixed range. This class avoids that limitation by storing a number digit-by-digit.

For example:

```text
12345678901234567890
```

is stored internally approximately as:

```text
[0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 9, 8, 7, 6, 5, 4, 3, 2, 1]
```

The digits are stored in reverse order because arithmetic starts from the least significant digit.

A separate boolean stores whether the number is negative.

```cpp
vector<int> Ds;
bool isNeg;
```

---

# HugeInteger Constructors

The class provides several constructors.

### Default Constructor

```cpp
HugeInteger();
```

Creates a value of zero.

### Size Constructor

```cpp
HugeInteger(int s);
```

Creates an integer with `s` digit positions initialized to zero. This is useful when creating temporary results for arithmetic.

### Copy Constructor

```cpp
HugeInteger(const HugeInteger&);
```

Creates a deep copy of another `HugeInteger`.

### File Constructor

```cpp
HugeInteger(ifstream& rdr);
```

Reads a number from an input file stream and initializes the object from it.

---

# Initializing a Number

The function:

```cpp
initializeFromString(const string& val)
```

converts a string into the internal digit representation.

It handles:

- Positive numbers
- Negative numbers
- A leading `+`
- Leading zeroes
- Zero

For example:

```text
"-001234"
```

is stored as the number:

```text
-1234
```

---

# Removing Leading Zeroes

The private function:

```cpp
trim()
```

removes unnecessary zeroes from the most significant side of the internal vector.

It also makes sure that zero is never stored as a negative number.

---

# Digit Access

The class provides:

```cpp
ithDigit(int i)
```

and:

```cpp
operator[](int i)
```

for accessing individual digits.

The const version of `ithDigit()` returns `0` when the requested position is outside the stored range. This makes arithmetic with numbers of different lengths easier.

---

# Addition

Addition is divided into two parts.

```cpp
ADDQuantityWise()
SUBQuantityWise()
```

`ADDQuantityWise()` performs normal digit-by-digit addition with a carry.

For example:

```text
  999
+   2
-----
 1001
```

The implementation starts from the least significant digit and carries the extra value to the next position.

The public `operator+` then handles the signs.

For example:

```text
positive + positive
negative + negative
positive + negative
negative + positive
```

---

# Subtraction

`SUBQuantityWise()` performs subtraction digit-by-digit using borrowing.

The public subtraction operator is implemented using addition with a negated second operand.

Conceptually:

```text
A - B
=
A + (-B)
```

This keeps the sign handling centralized.

---

# Comparisons

The class supports all common comparison operators:

```cpp
==
!=
<
<=
>
>=
```

The comparison is performed by considering:

1. The signs
2. Number of digits
3. Digits from most significant to least significant

For numbers with the same sign, the quantity comparison functions are used.

---

# Multiplication

The multiplication implementation uses repeated doubling and halving.

The basic idea is similar to binary multiplication:

```text
result = 0

while b > 0:
    if b is odd:
        result += a

    a += a
    b /= 2
```

This avoids directly multiplying every pair of decimal digits.

The final sign is determined from the signs of the two operands.

---

# Division

Division is implemented using repeated subtraction.

The general process is:

```text
quotient = 0

while dividend >= divisor:
    dividend -= divisor
    quotient++
```

A division by zero throws:

```cpp
runtime_error("Division by zero")
```

The result's sign is determined from the signs of the operands.

---

# Modulus

The `%` operator uses repeated subtraction in a similar way to division.

The remaining value after subtracting the divisor repeatedly becomes the remainder.

For example:

```text
17 % 5 = 2
```

because:

```text
17 - 5 - 5 - 5 = 2
```

---

# Increment and Decrement

Both prefix and postfix versions are overloaded.

```cpp
++A
A++
--A
A--
```

The prefix version modifies the object and returns it.

The postfix version saves a copy, modifies the object, and returns the old value.

---

# Unary Minus

The unary `-` operator changes the sign of a non-zero number.

For example:

```text
A  = 500
-A = -500
```

Zero remains non-negative.

---

# Stream Operators

The project overloads:

```cpp
operator>>
operator<<
```

This allows objects to work naturally with:

```cpp
cin >> A;
cout << A;
```

Input is read as a string and then converted into the internal representation.

Output prints the digits from the most significant digit to the least significant digit.

---

# HugeFraction

`HugeFraction` represents fractions using two `HugeInteger` objects:

```cpp
HugeInteger numerator;
HugeInteger denominator;
```

This allows fractions such as:

```text
12345678901234567890 / 98765432109876543210
```

without relying on normal integer limits.

---

# Fraction Constructors

The class provides:

```cpp
HugeFraction();
HugeFraction(const HugeInteger& n);
HugeFraction(const HugeInteger& n, const HugeInteger& d);
HugeFraction(const HugeFraction& F);
```

The default constructor creates:

```text
0/1
```

A single `HugeInteger` creates an integer-valued fraction:

```text
5 -> 5/1
```

The two-argument constructor creates a fraction and then normalizes and reduces it.

---

# Fraction Normalization

The private function:

```cpp
normalize()
```

ensures that the denominator is positive.

For example:

```text
5/-7
```

is changed to:

```text
-5/7
```

---

# Fraction Reduction

The function:

```cpp
reduce()
```

reduces a fraction using the greatest common divisor.

For example:

```text
8/12
```

becomes:

```text
2/3
```

The project implements `gcd()` using repeated subtraction.

---

# Fraction Arithmetic

The following operators are implemented:

```cpp
+
-
*
/
```

For addition:

```text
a/b + c/d
=
(a*d + c*b)/(b*d)
```

For subtraction:

```text
a/b - c/d
=
(a*d - c*b)/(b*d)
```

For multiplication:

```text
a/b * c/d
=
(a*c)/(b*d)
```

For division:

```text
a/b / c/d
=
(a*d)/(b*c)
```

The resulting fraction is constructed through the normalizing and reducing constructor.

---

# Fraction Comparisons

`HugeFraction` supports:

```cpp
==
!=
<
<=
>
>=
```

Fractions are compared using cross multiplication instead of converting them to floating-point values.

For example:

```text
a/b < c/d
```

is checked by comparing:

```text
a*d < c*b
```

This avoids losing precision.

---

# Decimal Input for HugeFraction

The function:

```cpp
fromDecimalString()
```

can convert a decimal string into a fraction.

For example:

```text
12.34
```

is represented conceptually as:

```text
1234/100
```

The fraction can then be reduced through the normal constructor when appropriate.

The input operator uses this function, so a fraction can be read directly from a string.

---

# Compound Assignment Operators

Both classes provide compound assignment operators.

For `HugeInteger`:

```cpp
+=
-=
*=
/=
%=
```

For `HugeFraction`:

```cpp
+=
-=
*=
/=
```

They perform the operation and assign the result back to the current object.

Example:

```cpp
A += B;
```

is effectively:

```cpp
A = A + B;
```

---

# Main Program

The active `main()` tests the `HugeInteger` class.

The user enters two large integers:

```text
Enter first number:
Enter second number integer:
```

The program then displays:

```text
A
B
A + B
A - B
A * B
A / B
A % B
```

Division and modulus are skipped when `B` is zero.

The program also demonstrates:

- Copy construction
- Prefix increment
- Postfix increment
- Prefix decrement
- Postfix decrement
- Comparisons

---

# Example Program Flow

```text
Enter first number: 100000000000000000000
Enter second number integer: 25

A = ...
B = 25
A + B = ...
A - B = ...
A * B = ...
A / B = ...
A % B = ...

Pre/Post inc and dec
C = ...
C++ = ...
After C++ -> ...
++C = ...
C-- = ...
After C-- -> ...

Comparisons
A > B
```

The exact output depends on the numbers entered.

---

# HugeFraction Test

The source file also contains another `main()` implementation for testing `HugeFraction`, but it is commented out.

That test would allow the user to enter two fractions and calculate:

```text
A + B
A - B
A * B
A / B
```

It also checks their ordering.

The project therefore contains both the large-integer and large-fraction functionality, while the current active program focuses on `HugeInteger`.

---

# Object-Oriented Programming Concepts

This project demonstrates several important C++ concepts.

## Encapsulation

The internal digit vector and sign are private:

```cpp
vector<int> Ds;
bool isNeg;
```

The class exposes public functions and operators to work with the number.

## Constructors

Multiple constructors allow objects to be created in different ways.

## Copy Constructor

The copy constructor creates an independent copy of another `HugeInteger` or `HugeFraction`.

## Operator Overloading

Arithmetic and comparison operators are overloaded so custom objects can be used naturally:

```cpp
A + B
A - B
A * B
A / B
A == B
A < B
```

## Friend Functions

The stream operators are declared as friends:

```cpp
friend ostream& operator<<(ostream&, const HugeInteger&);
friend istream& operator>>(istream&, HugeInteger&);
```

This allows them to access private class data.

---

# Data Structures Used

The main data structure is:

```cpp
vector<int>
```

Each element stores one decimal digit.

This provides a flexible size compared with fixed-size integer types.

`HugeFraction` then uses two `HugeInteger` objects to represent the numerator and denominator.

---

# Important Design Idea

The most important idea in the project is that `HugeFraction` builds on top of `HugeInteger`.

```text
HugeInteger
     |
     v
HugeFraction
     |
     +-- numerator
     +-- denominator
```

Instead of implementing large-number arithmetic again for fractions, `HugeFraction` reuses the operations already implemented by `HugeInteger`.

This keeps the project modular and demonstrates code reuse.

---

# Limitations

The implementation is mainly designed to demonstrate custom arithmetic and operator overloading.

Some operations, especially division and modulus, use repeated subtraction and can therefore become very slow for extremely large values.

The project also does not use the standard C++ big-number libraries; the large-number functionality is implemented manually.

---

# Concepts Demonstrated

This project brings together:

- Classes and objects
- Encapsulation
- Constructors
- Copy constructors
- Assignment operators
- Operator overloading
- Friend functions
- Unary operators
- Prefix and postfix operators
- Comparison operators
- File input
- STL `vector`
- Dynamic-sized integer representation
- Arbitrary-size arithmetic
- Fraction arithmetic
- GCD and reduction
- Exception handling for division by zero

---

# Conclusion

This project implements a custom arbitrary-size integer system instead of relying on C++'s built-in integer limits.

`HugeInteger` handles signed numbers and supports arithmetic, comparisons, increment/decrement, input, and output. `HugeFraction` builds on this class to provide arithmetic and comparisons for fractions containing very large numbers.

The project is mainly an exercise in understanding how fundamental arithmetic operations can be implemented manually and how C++ operator overloading can make custom classes behave like built-in data types.
