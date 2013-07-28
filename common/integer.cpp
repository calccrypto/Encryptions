#include "./../common/integer.h"

void integer::trim(){                             // remove 0 bytes from top of deque to save memory
    while (!value.empty() && !value[0]){
        value.pop_front();
    }
    if (value.empty()){                           // change sign to false if value is zero
        _sign = false;
    }
}

// Constructors
integer::integer(): _sign(false){}

integer::integer(const bool & b): _sign(false), value(1, b){
    trim();
}

integer::integer(const integer & rhs): _sign(rhs._sign), value(rhs.value){
    trim();
}

integer::integer(base & val, bool s): _sign(s), value(val){
    trim();
}

// need at least gcc 4.7 to compile next line, otherwise use uncommented version
// integer(const std::string & val, uint16_t base): integer(val.begin(), val.end(), base){}

integer::integer(const std::string & val, uint16_t b){
    *this = integer(val.begin(), val.end(), b);
}

//  RHS input args only

// Assignment Operator
integer & integer::operator=(const bool & b){
    value.clear();
    value.push_back(b);
    _sign = false;
    return *this;
}

// Typecast Operators
integer::operator bool(){
    return !value.empty();
}

integer::operator char(){
    if (value.empty())
        return 0;
    return (char) (value.back() & 255);
}

integer::operator uint8_t(){
    if (value.empty())
        return 0;
    return value.back() & 255;
}

integer::operator uint16_t(){
    uint16_t out = 0;
    for(uint8_t x = 0; x < std::min(value.size(), 2 / sizeof(digit)); x++){
        out += (uint16_t) value[value.size() - x - 1] << (x * BITS);
    }
    return out;
}

integer::operator uint32_t(){
    uint32_t out = 0;
    for(uint8_t x = 0; x < std::min(value.size(), 4 / sizeof(digit)); x++){
        out += (uint32_t) value[value.size() - x - 1] << (x * BITS);
    }
    return out;
}

integer::operator uint64_t(){
    uint64_t out = 0;
    for(uint8_t x = 0; x < std::min(value.size(), 8 / sizeof(digit)); x++){
        out += (uint64_t) value[value.size() - x - 1] << (x * BITS);
    }
    return out;
}

integer::operator int8_t(){
    if (value.empty()){
        return 0;
    }
    int8_t out = value.back() & 255;
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator int16_t(){
    int16_t out = 0;
    for(uint8_t x = 0; x < std::min(value.size(), 2 / sizeof(digit)); x++){
        out += (int16_t) value[value.size() - x - 1] << (x * BITS);
    }
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator int32_t(){
    int32_t out = 0;
    for(uint8_t x = 0; x < std::min(value.size(), 4 / sizeof(digit)); x++){
        out += (int32_t) value[value.size() - x - 1] << (x * BITS);
    }
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator int64_t(){
    int64_t out = 0;
    for(uint8_t x = 0; x < std::min(value.size(), 8 / sizeof(digit)); x++){
        out += (int64_t) value[value.size() - x - 1] << (x * BITS);
    }
    if (_sign){
        out = -out;
    }
    return out;
}

// Bitwise Operators

integer integer::operator&(integer rhs){
    base out;
    for(base::reverse_iterator i = value.rbegin(), j = rhs.value.rbegin(); (i != value.rend()) && (j != rhs.value.rend()); i++, j++){
        out.push_front(*i & *j);
    }
    return integer(out, _sign & rhs._sign);
}

integer integer::operator|(integer rhs){
    base out;
    base::reverse_iterator i = value.rbegin(), j = rhs.value.rbegin();
    for(; (i != value.rend()) && (j != rhs.value.rend()); i++, j++){
        out.push_front(*i | *j);
    }
    while (i != value.rend()){
        out.push_front(*i++);
    }
    while (j != rhs.value.rend()){
        out.push_front(*j++);
    }
    return integer(out, _sign | rhs._sign);
}

integer integer::operator^(integer rhs){
    base out;
    base::reverse_iterator i = value.rbegin(), j = rhs.value.rbegin();
    for(; (i != value.rend()) && (j != rhs.value.rend()); i++, j++){
        out.push_front(*i ^ *j);
    }
    while (i != value.rend()){
        out.push_front(*i++);
    }
    while (j != rhs.value.rend()){
        out.push_front(*j++);
    }
    return integer(out, _sign ^ rhs._sign);
}

integer integer::operator&=(const integer & rhs){
    *this = *this & rhs;
    return *this;
}

integer integer::operator|=(const integer & rhs){
    *this = *this | rhs;
    return *this;
}

integer integer::operator^=(const integer & rhs){
    *this = *this ^ rhs;
    return *this;
}

integer integer::operator~(){
    base out = value;
    for(d_size i = 1; i < out.size(); i++){
        out[i] ^= NEG1;
    }
    digit mask = HIGH_BIT;
    while (!(out[0] & mask)){
        mask >>= 1;
    }
    while (mask){
        out[0] ^= mask;
        mask >>= 1;
    }
    return integer(out, _sign);
}

// Bit Shift Operators

// left bit shift. sign is maintained
integer integer::operator<<(uint64_t shift){
    if (!*this || !shift)
        return *this;
    base out = value;
    for(uint64_t i = 0; i < (shift / BITS); i++){
        out.push_back(0);
    }
    shift %= BITS;
    if (shift){
        out.push_back(0);
        return integer(out, _sign) >> (BITS - shift);
    }
    return integer(out, _sign);
}

integer integer::operator<<(integer shift){
    integer out = *this;
    for(integer i = 0, s = shift / BITS; i < s; ++i){
       out.value.push_back(0);
    }
    return out << (uint64_t) (shift % BITS);
}

// right bit shift. sign is maintained
integer integer::operator>>(uint64_t shift){
    if (shift >= bits()){
        return integer(0);
    }
    base out = value;
    for(uint64_t i = 0; i < (shift / BITS); i++){
        out.pop_back();
    }
    shift %= BITS;
    if (shift){
        base v;
        for(d_size i = out.size() - 1; i != 0; i--){
            v.push_front(((out[i] >> shift) | (out[i - 1] << (BITS - shift))) & NEG1);
        }
        v.push_front(out[0] >> shift);
        out = v;
    }
    return integer(out, _sign);
}

integer integer::operator>>(integer shift){
    integer out = *this;
    for(integer i = 0, s = shift / BITS; i < s; ++i){
       out.value.pop_back();
    }
    return out >> (uint64_t) (shift % BITS);
}

integer integer::operator<<=(const integer & shift){
    *this = *this << shift;
    return *this;
}

integer integer::operator>>=(const integer & shift){
    *this = *this >> shift;
    return *this;
}

// Logical Operators
bool integer::operator!(){
    return !((bool) *this);
}

bool integer::operator&&(integer rhs){
    return (bool) *this && (bool) rhs;
}

bool integer::operator||(integer rhs){
    return ((bool) *this) || (bool) rhs;
}

// Comparison Operators
bool integer::operator==(const integer & rhs){
    return ((_sign == rhs._sign) && (value == rhs.value));
}

bool integer::operator!=(const integer & rhs){
    return !(*this == rhs);
}

// operator> not considering signs
bool integer::gt(const integer & lhs, const integer & rhs){
    if (lhs.value.size() > rhs.value.size()){
        return true;
    }
    if (lhs.value.size() < rhs.value.size()){
        return false;
    }
    if (lhs.value == rhs.value){
        return false;
    }
    for(d_size i = 0; i < lhs.value.size(); i++){
        if (lhs.value[i] != rhs.value[i]){
            return lhs.value[i] > rhs.value[i];
        }
    }
    return false;
}

bool integer::operator>(const integer & rhs){
    if (_sign & !rhs._sign){               // - > +
        return false;
    }
    else if (!_sign & rhs._sign){          // + > -
        return true;
    }
    else if (_sign & rhs._sign){           // - > -
        return !gt(*this, rhs);
    }
//            else (!_sign & !rhs._sign)          // + > +
    return gt(*this, rhs);
}

bool integer::operator>=(const integer & rhs){
    return ((*this > rhs) | (*this == rhs));
}

// operator< not considering signs
bool integer::lt(const integer & lhs, const integer & rhs){
    if (lhs.value.size() < rhs.value.size()){
        return true;
    }
    if (lhs.value.size() > rhs.value.size()){
        return false;
    }
    if (lhs.value == rhs.value){
        return false;
    }
    for(d_size i = 0; i < lhs.value.size(); i++){
        if (lhs.value[i] != rhs.value[i]){
            return lhs.value[i] < rhs.value[i];
        }
    }
    return false;
}

bool integer::operator<(const integer & rhs){
    if (_sign & !rhs._sign){                   // - < +
        return true;
    }
    else if (!_sign & rhs._sign){              // + < -
        return false;
    }
    else if (_sign & rhs._sign){               // - < -
        return !lt(*this, rhs);
    }
//            else (!_sign & !rhs._sign)              // + < +
    return lt(*this, rhs);
}

bool integer::operator<=(const integer & rhs){
    return ((*this < rhs) | (*this == rhs));
}

// Arithmetic Operators
integer integer::add(integer & lhs, integer & rhs){
    base out;
    base::reverse_iterator i = lhs.value.rbegin(), j = rhs.value.rbegin();
    bool carry = false;
    double_digit sum;
    for(; ((i != lhs.value.rend()) && (j != rhs.value.rend())); i++, j++){
        sum = (double_digit) *i + (double_digit) *j + carry;
        out.push_front(sum);
        carry = (sum > NEG1);
    }
    for(; i != lhs.value.rend(); i++){
        sum = (double_digit) *i + carry;
        out.push_front(sum);
        carry = (sum > NEG1);
    }
    for(; j != rhs.value.rend(); j++){
        sum = (double_digit) *j + carry;
        out.push_front(sum);
        carry = (sum > NEG1);
    }
    if (carry){
        out.push_front(1);
    }
    return integer(out);
}

integer integer::operator+(integer rhs){
    if (!rhs){
        return *this;
    }
    if (!*this){
        return rhs;
    }
    integer out = *this;
    if (_sign == rhs._sign){
        out = add(out, rhs);
        out._sign = _sign;
    }
    else if (gt(out, rhs)){
        if ((!_sign & rhs._sign) | (_sign & !rhs._sign)){         // + + -    - + +
            out = sub(out, rhs);
        }
        if ((!_sign & !rhs._sign) | (_sign & rhs._sign)){         // + + +    - + -
            out = add(out, rhs);
        }
        out._sign = _sign;
    }
    else if (lt(out, rhs)){
        if ((!_sign & rhs._sign) | (_sign & !rhs._sign)){        // + + -    - + +
            out = sub(rhs, out);
            out._sign = !_sign;
        }
        if ((_sign & rhs._sign) | (!_sign & !rhs._sign)){        // + + +    - + -
            out = add(rhs, out);
            out._sign = _sign;
        }
    }
    else{ //if (eq(out, rhs)){
        if ((_sign & rhs._sign) | (!_sign & !rhs._sign)){
            return integer(0);
        }
        //if ((_sign & !rhs._sign) | (!_sign & rhs._sign))
        out <<= 1;
        out._sign = _sign;
    }
    out.trim();
    return out;
}

integer integer::operator+=(const integer & rhs){
    *this = *this + rhs;
    return *this;
}

// Subtraction as done by hand
integer integer::long_sub(integer & lhs, integer & rhs){
    // rhs always smaller than lhs
    d_size lsize = lhs.value.size() - 1;
    d_size rsize = rhs.value.size() - 1;
    for(d_size x = 0; x < rsize + 1; x++){
        // if rhs digit is smaller than lhs digit, subtract
        if (rhs.value[rsize - x] <= lhs.value[lsize - x]){
            lhs.value[lsize - x] -= rhs.value[rsize - x];
        }
        else{// carry
            d_size y = lsize - x - 1;
            while (!lhs.value[y]){
                y--;
            }
            lhs.value[y]--;
            y++;
            for(; y < lsize - x; y++){
                lhs.value[y] = NEG1;
            }
            lhs.value[y] = ((double_digit) lhs.value[y]) + ((uint64_t) 1 << BITS) - rhs.value[rsize - x];
        }
    }
    return lhs;
}

//        // Two's Complement Subtraction
//        integer integer::two_comp_sub(const integer & lhs, integer & rhs){
//            rhs = rhs.twos_complement(lhs.bits());
//            return add(lhs, rhs) & (~(integer(1) << lhs.bits()));   // Flip bits to get max of 1 << x
//        }

integer integer::sub(integer & lhs, integer & rhs){
    if (!rhs){
        return lhs;
    }
    if (!lhs){
        return -rhs;
    }
    if (lhs == rhs){
        return 0;
    }
    return long_sub(lhs, rhs);
//            return two_comp_sub(lhs, rhs);
}

integer integer::operator-(integer rhs){
    integer out = *this;
    if (gt(out, rhs)){
        if ((!_sign & rhs._sign) | (_sign & !rhs._sign)){             // + - -         - - +
            out = add(out, rhs);
        }
        if ((!_sign & !rhs._sign) | (_sign & rhs._sign)){             // + - +         - - -
            out = sub(out, rhs);
        }
        out._sign = _sign;
    }
    else if (lt(out, rhs)){
        if ((!_sign & rhs._sign) | (_sign & !rhs._sign)){            // + - -         - - +
            out = add(out, rhs);
            out._sign = _sign;
        }
        if ((_sign & rhs._sign) | (!_sign & !rhs._sign)){            // + - +         - - -
            out = sub(rhs, out);
            out._sign = !_sign;
        }
    }
    else{ //if (eq(out, rhs)){
        if ((_sign & rhs._sign) | (!_sign & !rhs._sign)){
            return integer(0);
        }
        //if ((_sign & !rhs._sign) | (!_sign & rhs._sign))
        out <<= 1;
        out._sign = _sign;
    }
    out.trim();
    return out;
}

integer integer::operator-=(const integer & rhs){
    *this = *this - rhs;
    return *this;
}

// Peasant Multiplication
integer integer::peasant(integer lhs, integer rhs){
    integer SUM = 0;
    for(d_size x = 0; x < lhs.bits(); x++){
       if (lhs[x]){
           SUM += rhs;
        }
       rhs <<= 1;
    }
    return SUM;
}

// Recurseive Peasant Algorithm
integer integer::recursive_peasant(integer lhs, integer rhs){
    if (!rhs){
        return 0;
    }
    if (rhs & 1){
        return lhs + recursive_peasant(lhs << 1, rhs >> 1);
    }
    return recursive_peasant(lhs << 1, rhs >> 1);
}

// Recursive Multiplication
integer integer::recursive_mult(integer lhs, integer rhs){
    if (!rhs){
       return 0;
    }
    integer z = recursive_mult(lhs, rhs >> 1);
    if (!(rhs & 1)){
       return z << 1;
    }
    return lhs + (z << 1);
}

// Karatsuba Algorithm O(n^log2(3) = n ^ 1.585)
// Thanks to kjo @ stackoverflow for fixing up my original Karatsuba Algorithm implementation
// which i then converted to C++ and made a few changes
// http://stackoverflow.com/questions/7058838/karatsuba-algorithm-too-much-recursion
integer integer::karatsuba(integer lhs, integer rhs, integer bm){
   // b is base = 256
   // m is chars = 4
   // bm is max value = b ^ m

   if ((lhs <= bm) | (rhs <= bm))
       return peasant(lhs, rhs);

   std::pair <integer, integer> x = dm(lhs, bm);
   std::pair <integer, integer> y = dm(rhs, bm);
   integer x0 = x.second;
   integer x1 = x.first;
   integer y0 = y.second;
   integer y1 = y.first;

   integer z0 = karatsuba(x0, y0);
   integer z2 = karatsuba(x1, y1);
   integer z1 = karatsuba(x1 + x0, y1 + y0) - z2 - z0;
   return karatsuba(karatsuba(z2, bm) + z1, bm) + z0;
}

// Toom–Cook multiplication
// as described at http://en.wikipedia.org/wiki/Toom%E2%80%93Cook_multiplications
// This implementation is a bit weird. In the pointwise Multiplcation step, using
// operator* and long_mult works, but everything else fails.
// It's also kind of slow.
integer integer::toom_cook_3(integer m, integer n, integer bm){
   if ((m <= bm) | (n <= bm)){
       return peasant(m, n);
    }

   // Splitting
   integer i = integer(std::max(m.log(3), n.log(3))) / 3 + 1;
   integer bi = integer(3).pow(i);
   integer B = 1;
   integer base = 10;
   while (B < bi){
       B *= base;
    }

   integer M[3], N[3];
   for(uint8_t i = 0; i < 3; i++){
       std::pair <integer, integer> tm = dm(m, B);
       std::pair <integer, integer> tn = dm(n, B);
       m = tm.first;
       n = tn.first;
       M[i] = tm.second;
       N[i] = tn.second;
   }

   // Evaluation
   //             {0,             1,                 -1,                         -2,                             inf}
   integer p[5] = {M[0], M[0] + M[1] + M[2], M[0] - M[1] + M[2], M[0] - M[1] - M[1] + M[2] + M[2] + M[2] + M[2], M[2]};
   integer q[5] = {N[0], N[0] + N[1] + N[2], N[0] - N[1] + N[2], N[0] - N[1] - N[1] + N[2] + N[2] + N[2] + N[2], N[2]};

   // Pointwise Multiplication
   integer r[5];
   for(uint8_t i = 0; i < 5; i++)
       r[i] = p[i] * q[i];                 // dont understand why only operator* and long_mult can be used here

   // Interpolation
   integer r0 = r[0];
   integer r4 = r[4];
   integer r3 = (r[3] - r[1]) / 3;
   integer r1 = (r[1] - r[2]) / 2;
   integer r2 = r[2] - r[0];
   r3 = (r2 - r3) / 2 + r4 + r4;
   r2 = r2 + r1 - r4;
   r1 = r1 - r3;

   // Recomposition
   return peasant(peasant(peasant(peasant(r4, B) + r3, B) + r2, B) + r1, B) + r0;
}

// Long multiplication
integer integer::long_mult(integer lhs, integer rhs){
    unsigned int zeros = 0;
    integer row, out = 0;
    for(base::reverse_iterator i = lhs.value.rbegin(); i != lhs.value.rend(); i++){
        row.value = base(zeros++, 0); // zeros on the right hand side
        digit carry = 0;
        for(base::reverse_iterator j = rhs.value.rbegin(); j != rhs.value.rend(); j++){
            double_digit prod = (double_digit) *i * (double_digit) *j + carry;// multiply through
            row.value.push_front(prod & NEG1);
            carry = prod >> BITS;
        }
        if (carry){
            row.value.push_front(carry);
        }
        out = add(out, row);
    }
    return out;
}

//Private FFT helper function
int integer::fft(std::deque<double>& data, bool dir)
{
     //Verify size is a power of two
     std::size_t n = data.size()/2;
     if ((n == 0) || (n & (n-1))) return 1;

     //rearrange data for signal flow chart
     std::size_t bitr_j = 1;
     for (std::size_t i = 3; i < 2*n-1; i += 2)
     {
          std::size_t msz = n;
          while (bitr_j >= msz)
          {
               bitr_j -= msz;
               msz >>= 1;
          }
          bitr_j += msz;

          if (bitr_j > i)
          {
               double swap = data[bitr_j-1];
               data[bitr_j-1] = data[i-1];
               data[i-1] = swap;
               swap = data[bitr_j];
               data[bitr_j] = data[i];
               data[i] = swap;
          }
     }

     //Perform "butterfly" calculations
     std::size_t lmax = 2;
     while (lmax <= n)
     {
          double wr = 1;
          double wi = 0;

          double theta = (2*M_PI)/double(lmax*(dir?1.0:-1.0));
          double wpr = cos(theta);
          double wpi = sin(theta);

          int pstep = 2*lmax;
          for (std::size_t l = 1; l < lmax; l += 2)
          {
               for (std::size_t p = l; p < 2*n; p += pstep)
               {
                    std::size_t q = p + lmax;
                    double tempr = wr*data[q-1] - wi*data[q];
                    double tempi = wr*data[q] + wi*data[q-1];
                    data[q-1] = data[p-1] - tempr;
                    data[q] = data[p] - tempi;
                    data[p-1] = data[p-1] + tempr;
                    data[p] = data[p] + tempi;
               }

               //Find the next power of W
               double wtemp = wr;
               wr = wr*wpr - wi*wpi;
               wi = wi*wpr + wtemp*wpi;
          }

          lmax = pstep;
     }

     //All is good
     return 0;
}

// FFT-based multiplication
//Based on the convolution theorem which states that the Fourier
//transform of a convolution is the pointwise product of their
//Fourier transforms.
integer integer::fft_mult(integer& lhs, integer& rhs){
     //Convert each integer to input wanted by fft()
     size_t size = 1;
     while (size < lhs.value.size()*2){
          size <<= 1;
     }
     while (size < rhs.value.size()*2){
          size <<= 1;
     }

     std::deque<double> lhs_fft;
     lhs_fft.resize(size*2, 0);
     for (size_t i = 0; i < lhs.value.size(); i++){
          lhs_fft[i*2] = double(lhs.value[lhs.value.size()-1-i]);
     }

     std::deque<double> rhs_fft;
     rhs_fft.resize(size*2, 0);
     for (size_t i = 0; i < rhs.value.size(); i++){
          rhs_fft[i*2] = double(rhs.value[rhs.value.size()-1-i]);
     }

     //Compute the FFT of each
     fft(lhs_fft);
     fft(rhs_fft);

     //Perform pointwise multiplication (numbers are complex)
     std::deque<double> out_fft(2*size);
     for (size_t i = 0; i < 2*size; i+=2){
          out_fft[i] = lhs_fft[i]*rhs_fft[i] - lhs_fft[i+1]*rhs_fft[i+1];
          out_fft[i+1] = lhs_fft[i]*rhs_fft[i+1] + lhs_fft[i+1]*rhs_fft[i];
     }

     //Compute the inverse FFT of this number
     //remember to properly scale afterwards!
     fft(out_fft, false);
     for (size_t i = 0; i < 2*size; i++){
          out_fft[i] /= size;
     }

     //Convert back to integer, carrying along the way
     double carry = 0;
     integer out;
     for (size_t i = 0; i < 2*size; i+=2){
          double current = out_fft[i]+carry;
          if (current > double(NEG1)){
               carry = current / (double(NEG1)+1);
               carry = double(floor(carry+0.0001));
               current = current - (carry*(NEG1+1));

          }
          else {
               carry = 0;
          }
          out.value.push_front(digit(current+0.0001));
     }

     //Finish up
     return out;
}

integer integer::operator*(integer rhs){
    if ((!*this) || (!rhs)){             // if multiplying by 0
        return 0;
    }
    if (*this == 1){                     // if multiplying by 1
        return rhs;
    }
    if (rhs == 1){                       // if multiplying by 1
        return *this;
    }
    bool s = _sign ^ rhs._sign;
    integer out = *this;
    out._sign = false;
    rhs._sign = false;
    if (rhs.abs() == 10){               // if rhs == 10
        out = (out << 3) + (out << 1);
        out._sign = s;
        return out;
    }
    if (out.abs() == 10){               // if lhs == 10
        out = (rhs << 3) + (rhs << 1);
        out._sign = s;
        return out;
    }
    // while rhs is multiple of 2
    while (!(rhs & 1)){
        rhs >>= 1;
        out <<= 1;
    }
//            out = peasant(out, rhs);
//            out = recursive_peasant(out, rhs);
//            out = recursive_mult(out, rhs);
//            out = karatsuba(out, rhs);
//            out = toom_cook_3(out, rhs);
//            out = long_mult(out, rhs);
    out = fft_mult(out, rhs);
    out._sign = s;
    out.trim();
    return out;
}

integer integer::operator*=(const integer & rhs){
    *this = *this * rhs;
    return *this;
}


//        // Long Division returning both quotient and remainder
//        std::pair <integer, integer> integer::long_div(const integer & lhs, const integer & rhs){
//            std::pair <integer, integer> qr;
//            qr.first = 0;
//            qr.second = lhs;
//            integer copyd = rhs;
//            integer adder = 1;
//            while (qr.second > copyd){
//                copyd <<= 1;
//                adder <<= 1;
//            }
//            while (qr.second >= rhs){
//                if (qr.second >= copyd){
//                    qr.second -= copyd;
//                    qr.first |= adder;
//                }
//                copyd >>= 1;
//                adder >>= 1;
//            }
//            return qr;
//        }

//        // Recursive Division that returns both the quotient and remainder
//        // Recursion took up way too much memory
//        std::pair <integer, integer> integer::recursive_divmod(integer lhs, const integer & rhs){
//            std::pair <integer, integer> qr;
//            if (!lhs){
//                qr.first = 0;
//                qr.second = 0;
//                return qr;
//            }
//            qr = recursive_divmod(lhs >> 1, rhs);
//            qr.first <<= 1;
//            qr.second <<= 1;
//            if (lhs & 1)
//                qr.second++;
//            if (qr.second >= rhs){
//                qr.second -= rhs;
//                qr.first++;
//            }
//            return qr;
//        }

// Non-Recursive version of above algorithm
std::pair <integer, integer> integer::non_recursive_divmod(integer & lhs, integer & rhs){
    std::pair <integer, integer> qr;
    qr.first = 0;
    qr.second = 0;
    for(size_t x = lhs.bits(); x > 0; x--){
        qr.first <<= 1;
        qr.second <<= 1;
        if (lhs[x - 1]){
            qr.second++;
        }
        if (qr.second >= rhs){
            qr.second -= rhs;
            qr.first++;
        }
    }
    return qr;
}

// division ignoring signs
std::pair <integer, integer> integer::dm(integer & lhs, integer & rhs){
    if (!rhs){                           // divide by 0 error
        throw std::runtime_error("Error: division or modulus by zero");
    }
    std::pair <integer, integer> out;
    if (rhs == 1){                      // divide by 1 check
        out.first = lhs;
        out.second = 0;
        return out;
    }
    if (lhs == rhs){                    // divide by same value check
        out.first = 1;
        out.second = 0;
        return out;
    }
    if (!lhs){                          // 0 / rhs check
        out.first = 0;
        out.second = 0;
        return out;
    }
    if (lt(lhs, rhs)){                  // lhs < rhs check
        out.first = 0;
        out.second = lhs;
        return out;
    }

    // Check for powers of two /////////////////////
    // Cannot do it the easy way for some reason
    if (!(rhs & 1)){
        uint64_t s = 0;
        integer copyd(rhs);
        while (!(copyd & 1)){
            copyd >>= 1;
            s++;
        }
        if (copyd == 1){
            out.first = lhs >> s;
            out.second = lhs - (out.first << s);
            return out;
        }
    }
    ////////////////////////////////////////////////
//            return long_div(lhs, rhs);
//            return recursive_divmod(lhs, rhs);
    return non_recursive_divmod(lhs, rhs);
}

integer integer::operator/(integer rhs){
    bool s = _sign ^ rhs._sign;
    integer lhs = *this;
    lhs._sign = false;
    rhs._sign = false;
    integer out = dm(lhs, rhs).first;
    out._sign = s;
    out.trim();
    return out;
}

integer integer::operator/=(const integer & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator%(integer rhs){
    bool s1 = _sign;
    bool s2 = rhs._sign;
    integer lhs = *this;
    lhs._sign = false;
    rhs._sign = false;
    integer out = dm(lhs, rhs).second;
    out.trim();
    if (!out.value.empty()){
        if (s1 == s2){
            out._sign = s1;
        }
        else{
            out = rhs - out;
            out._sign = s2;
        }
    }
    return out;
}

integer integer::operator%=(const integer & rhs){
    *this = *this % rhs;
    return *this;
}

// Increment Operator
integer & integer::operator++(){
    *this += 1;
    return *this;
}

integer integer::operator++(int){
    integer temp(*this);
    ++*this;
    return temp;
}

// Decrement Operator
integer & integer::operator--(){
    *this -= 1;
    return *this;
}

integer integer::operator--(int){
    integer temp(*this);
    --*this;
    return temp;
}

// Nothing done since promotion doesnt work here
integer integer::operator+() const{
    return *this;
}

// Flip Sign
integer integer::operator-(){
    integer out = *this;
    if (out.value.size()){
        out._sign = !out._sign;
    }
    return out;
}

// get private values
bool integer::sign() const{
    return _sign;                    // false = pos, true = neg
}

// get number of bits
unsigned int integer::bits() const{
    if (value.empty()){
        return 0;
    }
    unsigned int out = value.size() * BITS;
    digit mask = HIGH_BIT;
    while (!(value[0] & mask)){
        out--;
        mask >>= 1;
    }
    return out;
}

unsigned int integer::bytes() const{
    if (value.empty()){
        return 0;
    }
    unsigned int b = bits();
    return (b >> 3) + (b & 7);
}

// get number of digits
unsigned int integer::digits() const{
    return value.size();
}

// get internal data
base integer::data() const{
    return value;
}

// Miscellaneous Functions
integer integer::twos_complement(unsigned int b){
    base out = value;
    for(d_size i = 1; i < out.size(); i++){
        out[i] ^= NEG1;
    }
    digit mask = HIGH_BIT;
    while (!(out[0] & mask)){
        mask >>= 1;
    }
    integer top = integer(1) << ((uint64_t) (out.size() - 1) * BITS);
    while (mask){
        out[0] ^= mask;
        mask >>= 1;
        top <<= 1;
    }
    integer OUT(out, _sign);
    while (b){
        OUT ^= top;
        top <<= 1;
        b--;
    }
    return OUT + 1;
}

// returns positive value of *this
integer integer::abs() const{
    integer out = *this;
    out._sign = false;
    return out;
}

// fills an integer with 1s
void integer::fill(const uint64_t & b){
    value = base(b / BITS, NEG1);
    if (b % BITS){
        value.push_front((1 << (b % BITS)) - 1);
    }
}

// get bit, where 0 is the lsb and bits() - 1 is the msb
bool integer::operator[](const unsigned int & b){
    if (b >= bits()){ // if given index is larger than bits in this value, return 0
        return 0;
    }
    return (value[value.size() - (b / BITS) - 1] >> (b % BITS)) & 1;
}

// Output value as a string in bases 2 to 16, and 256
std::string integer::str(integer b, const unsigned int & length){
    std::string out = "";
    if (b == 256){
        if (value.empty()){
            out = std::string(1, 0);
        }
        for(d_size x = 0; x < value.size(); x++){
            out += std::string(1, value[x]);
        }
        while (out.size() < length){
            out = std::string(1, 0) + out;
        }
        if (_sign){
            if (!out[0]){
                out = out.substr(1, out.size() - 1);
            }
            out = "-" + out;
        }
    }
    else{
        if ((b < 2) || (b > 16)){                        // if base outside of 2 <= base <= 16
            b = 10;                                      // set to default value of 10
        }
        integer rhs = *this;
        static const std::string B16 = "0123456789abcdef";
        std::pair <integer, integer> qr;
        do{
            qr = dm(rhs, b);
            out = B16[qr.second] + out;
            rhs = qr.first;
        } while (rhs);

        while (out.size() < length){
            out = "0" + out;
        }
        if (_sign){
            if (out[0] == '0'){
                out = out.substr(1, out.size() - 1);
            }
            out = "-" + out;
        }
    }
    return out;
}

// IO Operators
std::ostream & operator<<(std::ostream & stream, integer rhs){
    if (stream.flags() & stream.oct){
        stream << rhs.str(8);
    }
    else if (stream.flags() & stream.hex){
        stream << rhs.str(16);
    }
    else{
        stream << rhs.str(10);
    }
    return stream;
}

std::istream & operator>>(std::istream & stream, integer & rhs){
    uint8_t base;
    if (stream.flags() & stream.oct){
        base = 8;
    }
    else if (stream.flags() & stream.hex){
        base = 16;
    }
    else{
        base = 10;
    }
    std::string in;
    stream >> in;
    rhs = integer(in, base);
    return stream;
}

// Special functions
std::string makebin(integer value, unsigned int size){
    // Changes a value into its binary string
    return value.str(2, size);
}

std::string makehex(integer value, unsigned int size){
    // Changes a value into its hexadecimal string
    return value.str(16, size);
}

std::string makeascii(integer value, unsigned int size){
    // Changes a value into ASCII
    return value.str(256, size);
}

integer abs(integer value){
    return value.abs();
}
