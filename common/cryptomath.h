/*
A bunch of math algorithms that
I have found useful.

gcd, invmod, and pow are deprecated since
they are now done through GMP. However,
they are still useful for integer types
that do not have these functions defined.
*/

#ifndef __CRYPTO_MATH__
#define __CRYPTO_MATH__

#include <iostream>

// Greatest Common Divisor
template <typename T> T gcd(T a, T b){
	T c = 1;
	while (c != 0){
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

// Inverse Mod b * x = 1 mod a
template <typename T> T invmod(T a, T b){
	T A = a;
	T x = 0, lastx = 1, y = 1, lasty = 0;
	while (b != 0){
		T quotient = a / b;
		T temp = b;
		b = a % b;
		a = temp;
		temp = x;
		x = lastx - quotient * x;
		lastx = temp;
		temp = y;
		y = lasty - quotient * y;
		lasty = temp;
	}
	if (lasty < 0){
		lasty += A;
    }
	return lasty;
}

// Faster Exponentiation by Squaring
// adapted from http://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-mpz_class-based-power-function-powint-int
template <typename S, typename T>
S POW(S base, T exp)
{
    S result = 1;
    while (exp != 0)
    {
        if ((exp & 1) == 1){
            result *= base;
        }
        exp >>= 1;
        base *= base;
    }
    return result;
}

// Exponentiation by squaring
template <typename R, typename S, typename T>
T POW(R base, S exponent, const T mod){
	T result = 1;
	while (exponent != 0){
		if ((exponent & 1) == 1){
			result = (result * base) % mod;
        }
		exponent >>= 1;
		base = (base * base) % mod;
	}
	return result;
}

// Two's compliment
template <typename T>
T two_comp(const T & a, const uint8_t bits = 16){
	//Change a number to its 2s compliment//
	T XOR = 1;
	XOR = (XOR << (bits - 1)) - 1;
	XOR = (XOR << 1) + 1;
	return (a ^ XOR) + 1;
}

// From a Twofish code (modified)
// Rotate Right
template <typename T>
T ROR(T x, const uint64_t & n, const uint64_t & bits){
	// Bitwise rotation to the right
	T mask = 1;
	mask = (mask << (n - 1)) - 1;
	mask = (mask << 1) + 1;
	T mask_bits = x & mask;
    return (x >> n) | (mask_bits << (bits - n));
}

// Rotate Left
template <typename T>
T ROL(const T & x, const uint64_t & n, const uint64_t & bits){
	// Bitwise rotation to the left
	return ROR(x, bits - n, bits);
}

#endif
