/*
integer
An Arbitrary Precision Integer Type
by Jason Lee @ calccrypto at gmail.com

With much help from:
    Auston Sterling - Initial debugging and coding help and FFT multiplication
    Corbin @ Code Review (StackExchange) - wrote a sizeable chunk of code and suggestions
    Keith Nicholas  @ Code Review (StackExchange)
    ROBOKITTY @ Code Review (StackExchange)
    Winston Ewert @ Code Review (StackExchange) - suggested many improvements

This is an implementation of an arbitrary precision integer
container. The actual limit of how large the integers can
be is std::deque <Z>().max_size() * sizeof(Z) * 8 bits, which
should be enormous. Most of the basic operators are implemented,
although their outputs might not necessarily be the same output
as a standard version of that operator. Anything involving
pointers and addresses should be taken care of by C++.

Data is stored in big endian, so value[0] is the most
significant digit, and value[value.size() - 1] is the
least significant digit.

Negative values are stored as their positive value,
with a bool that says the value is negative.

NOTE: Build with the newest compiler. Some functions are only
      supported in the latest versions of C++ compilers and
      standards.

NOTE: Base256 strings are assumed to be postive when read into
      integer. Use operator-() to negate the value.

NOTE: Multiple algorithms for subtraction, multiplication, and
      division have been implemented and commented out. They
      should all work, but are there for educational purposes.
      If one is faster than another on different systems, by
      all means change which algorithm is used. Just make sure
      all related functions are changed as well.

NOTE: All algorithms operate on positive values only. The
      operators deal with the signs.

NOTE: Changing the internal representation to a std::string
      makes integer run slower than using a std::deque <uint8_t>
*/

#include <cmath> //For fft sin, cos, M_PI, and floor
#include <deque>
#include <iostream>
#include <stdexcept>
#include <stdint.h>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#ifndef __INTEGER__
#define __INTEGER__

typedef uint8_t                           digit;            // Change this integer type to reduce wasted bits/increase speed
typedef uint64_t                          double_digit;     // sizeof(double_digit) must be larger than sizeof(digit)

typedef std::deque <digit>                base;             // internal representation of values
typedef std::deque <digit>::size_type     d_size;           // size type of std::deque

const digit NEG1 = -1;                                      // value with all bits ON - will only work for unsigned integer types, where -1 == 111...1
const digit BITS = sizeof(digit) << 3;                      // bit size of value; hardcode this if digit is not standard int type
const digit HIGH_BIT = 1 << (BITS - 1);                     // highest bit of value (uint8_t -> 128)

class integer{
    private:
        bool _sign;                                         // false = positive, true = negative
        base value;                                         // holds the actual value in base

        template <typename Z> void setFromZ(Z val){
            value.clear();
            _sign = false;
            if (val < 0){
                _sign = true;
                val = -val;
            }
            while (val){
                Z mask = 1;
                digit d = 0;
                for(unsigned int x = 0; x < BITS; x++){
                    d += ((val & 1)?mask:0);
                    val >>= 1;
                    mask <<= 1;
                }
                value.push_front(d);
            }
            trim();
        }

        void trim();                                        // remove 0 digits from top of deque to save memory

    public:
        // Constructors
        integer();
        integer(const bool & b);
        integer(const integer & rhs);
        template <typename Z> integer(Z val) : integer() {setFromZ(val);}
        integer(base & val, bool s = false);

        // Written by Corbin
        // Slightly modified by me
        template <typename Iterator> integer(Iterator start, const Iterator& end, uint16_t b) : integer() {
            bool s = false;
            if (start == end)
                return;
            if (b != 256)            // All base 256 inputs assumed to be positive
                if (*start == '-'){
                    s = true;
                    ++start;
                }
            switch (b){
                case 2:
                    while (start != end){
                        *this = (*this << 1) + (*start - '0');
                        ++start;
                    }
                    break;
                case 8:
                    while (start != end){
                        *this = (*this << 3) + (*start - '0');
                        ++start;
                    }
                    break;
                case 10:
                    while (start != end){
                        *this = (*this << 3) + (*this << 1) + (*start - '0');
                        ++start;
                    }
                    break;
                case 16:
                    while (start != end){
                        *this <<= 4;
                        if (std::isxdigit(*start)){
                            if (std::isdigit(*start))
                                *this += *start - 0x30;                //0-9
                            else if (std::islower(*start))
                                *this += *start - 0x57;                //a-f
                            else if (std::isupper(*start))
                                *this += *start - 0x37;                //A-F
                            else
                                throw std::runtime_error("Character not between 'a' and 'f' found");
                        }
                        ++start;
                    }
                    break;
                case 256:
                    while (start != end){
                        *this = (*this << 8) + static_cast <uint8_t> (*start);
                        ++start;
                    }
                    break;
                default:
                    throw std::runtime_error("Unknown base provided (must be 2, 8, 10, 16 or 256)");
                    break;
            }
            _sign = s;
            trim();
        }
        // need at least gcc 4.7 to compile next line, otherwise use uncommented version
        // integer(const std::string & val, uint16_t base);

        integer(const std::string & val, uint16_t b);

        //  RHS input args only

        // Assignment Operator
        integer & operator=(const bool & b);
        template <typename Z> integer& operator=(const Z & val){ setFromZ(val); return *this;}

        // Typecast Operators
        operator bool();
        operator char();
        operator uint8_t();
        operator uint16_t();
        operator uint32_t();
        operator uint64_t();
        operator int8_t();
        operator int16_t();
        operator int32_t();
        operator int64_t();

        // Bitwise Operators
        template <typename Z> integer operator&(const Z & rhs){return *this & integer(rhs);}
        integer operator&(integer rhs);
        template <typename Z> integer operator|(const Z & rhs){return *this | integer(rhs);}
        integer operator|(integer rhs);
        template <typename Z> integer operator^(const Z & rhs){return *this ^ integer(rhs);}
        integer operator^(integer rhs);
        template <typename Z> integer operator&=(const Z & rhs){*this = *this & rhs;return *this;}
        integer operator&=(const integer & rhs);
        template <typename Z> integer operator|=(const Z & rhs){*this = *this | rhs; return *this;}
        integer operator|=(const integer & rhs);
        template <typename Z> integer operator^=(const Z & rhs){*this = *this ^ rhs; return *this;}
        integer operator^=(const integer & rhs);
        integer operator~();

        // Bit Shift Operators
        // left bit shift. sign is maintained
        template <typename Z> integer operator<<(const Z & shift){return *this << static_cast <uint64_t> (shift);}
        integer operator<<(uint64_t shift);
        integer operator<<(integer shift);

        // right bit shift. sign is maintained
        template <typename Z> integer operator>>(const Z & shift){return *this >> static_cast <uint64_t> (shift);}
        integer operator>>(uint64_t shift);
        integer operator>>(integer shift);

        template <typename Z> integer operator<<=(const Z & shift){*this = *this << shift; return *this;}
        integer operator<<=(const integer & shift);
        template <typename Z> integer operator>>=(const Z & shift){*this = *this >> shift; return *this;}
        integer operator>>=(const integer & shift);

        // Logical Operators
        bool operator!();

        // Comparison Operators
        template <typename Z> bool operator==(const Z & rhs){return (*this == integer(rhs));}
        bool operator==(const integer & rhs);
        template <typename Z> bool operator!=(const Z & rhs){return !(*this == integer(rhs));}
        bool operator!=(const integer & rhs);

    private:
        // operator> not considering signs
        bool gt(const integer & lhs, const integer & rhs);

    public:
        template <typename Z> bool operator>(const Z & rhs){return (*this > integer(rhs));}
        bool operator>(const integer & rhs);

        template <typename Z> bool operator>=(const Z & rhs){return ((*this > rhs) | (*this == rhs));}
        bool operator>=(const integer & rhs);

    private:
        // operator< not considering signs
        bool lt(const integer & lhs, const integer & rhs);

    public:
        template <typename Z> bool operator<(const Z & rhs){return (*this < integer(rhs));}
        bool operator<(const integer & rhs);
        template <typename Z> bool operator<=(const Z & rhs){return ((*this < rhs) | (*this == rhs));}
        bool operator<=(const integer & rhs);

    private:
        // Arithmetic Operators
        integer add(integer & lhs, integer & rhs);

    public:
        template <typename Z> integer operator+(const Z & rhs){return *this + integer(rhs);}
        integer operator+(integer rhs);
        template <typename Z> integer operator+=(const Z & rhs){*this = *this + rhs; return *this;}
        integer operator+=(const integer & rhs);

    private:
        // Subtraction as done by hand
        integer long_sub(integer & lhs, integer & rhs);

//        // Two's Complement Subtraction
//        integer two_comp_sub(integer & lhs, integer & rhs);

        integer sub(integer & lhs, integer & rhs);

    public:
        template <typename Z> integer operator-(const Z & rhs){return *this - integer(rhs);}
        integer operator-(integer rhs);
        template <typename Z> integer operator-=(const Z & rhs){*this = *this - rhs; return *this;}
        integer operator-=(const integer & rhs);

    private:
//       // Peasant Multiplication
//       integer peasant(integer lhs, integer rhs);
//
//       // Recurseive Peasant Algorithm
//       integer recursive_peasant(integer lhs, integer rhs);
//
//       // Recursive Multiplication
//       integer recursive_mult(integer lhs, integer rhs);
//
//       // Karatsuba Algorithm O(n^log2(3) = n ^ 1.585)
//       // The peasant function is needed if karatsuba is used.
//       // Thanks to kjo @ stackoverflow for fixing up my original Karatsuba Algorithm implementation
//       // which I then converted to C++ and made a few changes.
//       // http://stackoverflow.com/questions/7058838/karatsuba-algorithm-too-much-recursion
//       integer karatsuba(integer lhs, integer rhs, integer bm = 0x1000000U);
//
//       // Toom-Cook multiplication
//       // as described at http://en.wikipedia.org/wiki/Toom%E2%80%93Cook_multiplications
//       // The peasant function is needed if karatsuba is used.
//       // This implementation is a bit weird. In the pointwise Multiplcation step, using
//       // operator* and long_mult works, but everything else fails.
//       // It's also kind of slow.
//       integer toom_cook_3(integer m, integer n, integer bm = 0x1000000U);
//
//       // Long multiplication
//       integer long_mult(integer lhs, integer rhs);

       //Private FFT helper function
       int fft(std::deque<double>& data, bool dir = true);

       // FFT-based multiplication
       //Based on the convolution theorem which states that the Fourier
       //transform of a convolution is the pointwise product of their
       //Fourier transforms.
       integer fft_mult(integer& lhs, integer& rhs);

    public:
        template <typename Z> integer operator*(const Z & rhs){return *this * integer(rhs);}
        integer operator*(integer rhs);
        template <typename Z> integer operator*=(const Z & rhs){*this = *this * rhs; return *this;}
        integer operator*=(const integer & rhs);

    private:
//        // Long Division returning both quotient and remainder
//        std::pair <integer, integer> long_div(const integer & lhs, const integer & rhs);

//        // Recursive Division that returns both the quotient and remainder
//        // Recursion took up way too much memory
//        std::pair <integer, integer> recursive_divmod(integer lhs, const integer & rhs);

        // Non-Recursive version of above algorithm
        std::pair <integer, integer> non_recursive_divmod(integer & lhs, integer & rhs);
        // division ignoring signs
        std::pair <integer, integer> dm(integer & lhs, integer & rhs);

    public:

        template <typename Z> integer operator/(const Z & rhs){return *this / integer(rhs);}
        integer operator/(integer rhs);
        template <typename Z> integer operator/=(const Z & rhs){*this = *this / integer(rhs); return *this;}
        integer operator/=(const integer & rhs);

        template <typename Z> integer operator%(const Z & rhs){return *this % integer(rhs);}
        integer operator%(integer rhs);
        template <typename Z> integer operator%=(const Z & rhs){*this = *this % integer(rhs); return *this;}
        integer operator%=(const integer & rhs);

        // Increment Operator
        integer & operator++();
        integer operator++(int);

        // Decrement Operator
        integer & operator--();
        integer operator--(int);

        // Nothing done since promotion doesnt work here
        integer operator+() const;

        // Flip Sign
        integer operator-();

        // get private values
        bool sign() const;

        // get number of bits
        unsigned int bits() const;

        // get numboer of bytes
        unsigned int bytes() const;

        // get number of digits
        unsigned int digits() const;

        // get internal data
        base data() const;

        // Miscellaneous Functions
        integer twos_complement(unsigned int b = 0);

        // returns positive value of *this
        integer abs() const;

        // returns floor(log_b(*this))
        template <typename Z>
        integer log(Z b){
            integer count = 0;
            integer x = *this;
            while (x){
                x /= b;
                count++;
            }
            return count;
        }
        // raises *this to exponent exp
        template <typename Z>
        integer pow(Z exp){
            if (exp < 0)
                return 0;
            integer result = 1;
            // take advantage of optimized integer * 10
            if (*this == 10){
                for(Z x = 0; x < exp; x++)
                    result *= *this;
                return result;
            }
            integer b = *this;
            while (exp){
                if (exp & 1)
                    result *= b;
                exp >>= 1;
                b *= b;
            }
            return result;
        }

        // fills an integer with 1s
        void fill(const uint64_t & b);

        // get bit, where 0 is the lsb and bits() - 1 is the msb
        bool operator[](const unsigned int & b);

        // Output value as a string in bases 2 to 16, and 256
        std::string str(integer b = 10, const unsigned int & length = 1);
};
// lhs type Z as first arguemnt

// Bitwise Operators
template <typename Z> Z operator&(const Z & lhs, integer rhs){
    return static_cast <Z> (rhs & lhs);
}

template <typename Z> Z operator|(const Z & lhs, integer rhs){
    return static_cast <Z> (rhs | lhs);
}

template <typename Z> Z operator^(const Z & lhs, integer rhs){
    return static_cast <Z> (rhs ^ lhs);
}

template <typename Z> Z operator&=(Z & lhs, integer rhs){
    lhs = static_cast <Z> (rhs & lhs);
    return lhs;
}

template <typename Z> Z operator|=(Z & lhs, integer rhs){
    lhs = static_cast <Z> (rhs | lhs);
    return lhs;
}

template <typename Z> Z operator^=(Z & lhs, integer rhs){
    lhs = static_cast <Z> (rhs ^ lhs);
    return lhs;
}

// Comparison Operators
template <typename Z> bool operator==(const Z & lhs, integer rhs){
    return (rhs == lhs);
}

template <typename Z> bool operator!=(const Z & lhs, integer rhs){
    return (rhs != lhs);
}

template <typename Z> bool operator>(const Z & lhs, integer rhs){
    return (rhs < lhs);
}

template <typename Z> bool operator<(const Z & lhs, integer rhs){
    return (rhs > lhs);
}

template <typename Z> bool operator>=(const Z & lhs, integer rhs){
    return (rhs <= lhs);
}

template <typename Z> bool operator<=(const Z & lhs, integer rhs){
    return (rhs >= lhs);
}

// Arithmetic Operators
template <typename Z> Z operator+(const Z & lhs, integer rhs){
    return static_cast <Z> (rhs + lhs);
}

template <typename Z> Z & operator+=(Z & lhs, integer rhs){
    lhs = static_cast <Z> (rhs + lhs);
    return lhs;
}

template <typename Z> Z operator-(const Z & lhs, integer rhs){
    return static_cast <Z> (integer(lhs) - rhs);
}

template <typename Z> Z & operator-=(Z & lhs, integer rhs){
    lhs = lhs - rhs;
    return lhs;
}

template <typename Z> Z operator*(const Z & lhs, integer rhs){
    return static_cast <Z> (rhs * lhs);
}

template <typename Z> Z & operator*=(Z & lhs, integer rhs){
    lhs = static_cast <Z> (rhs * lhs);
    return lhs;
}

template <typename Z> Z operator/(const Z & lhs, integer rhs){
    return static_cast <Z> (integer(lhs) / rhs);
}

template <typename Z> Z & operator/=(Z & lhs, integer rhs){
    lhs = integer(lhs) / rhs;
    return lhs;
}
template <typename Z> Z operator%(const Z & lhs, integer rhs){
    return static_cast <Z> (integer(lhs) % rhs);
}

template <typename Z> Z & operator%=(Z & lhs, integer rhs){
    lhs = lhs % rhs;
    return lhs;
}

// IO Operators
std::ostream & operator<<(std::ostream & stream, integer rhs);
std::istream & operator>>(std::istream & stream, integer & rhs);

// Special functions
std::string makebin(integer value, unsigned int size = 1);
std::string makehex(integer value, unsigned int size = 1);
std::string makeascii(integer value, unsigned int size = 1);
integer abs(integer value);

template <typename Z> integer log(integer x, Z base){
    return x.log(base);
}

template <typename Z> integer pow(integer base, Z exp){
    return base.pow(exp);
}

#endif // INTEGER_H
