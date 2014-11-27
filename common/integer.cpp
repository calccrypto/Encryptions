#include "integer.h"

constexpr integer::DIGIT integer::NEG1;
constexpr integer::DIGIT integer::OCTETS;
constexpr integer::DIGIT integer::BITS;
constexpr integer::DIGIT integer::HIGH_BIT;
const std::string integer::B16 = "0123456789abcdef";

void integer::trim(){                              // remove top 0 digits to save memory
    while (!_value.empty() && !_value[0]){
        _value.pop_front();
    }
    if (_value.empty()){                           // change sign to false if _value is 0
        _sign = false;
    }
}

// Constructors
integer::integer() :
    _sign(false),
    _value()
{}

integer::integer(const REP & rhs, const bool & sign) :
    _sign(sign),
    _value(rhs)
{
    trim();
}

integer::integer(const integer & copy) :
    _sign(copy._sign),
    _value(copy._value)
{
    trim();
}

integer::integer(const bool & b) :
    _sign(false),
    _value(1, b)
{}

integer::integer(const uint8_t & val){
    setFromZ(val, 8);
}

integer::integer(const uint16_t & val){
    setFromZ(val, 16);
}

integer::integer(const uint32_t & val){
    setFromZ(val, 32);
}

integer::integer(const uint64_t & val){
    setFromZ(val, 64);
}

integer::integer(const int8_t & val){
    setFromZ(val, 8);
}

integer::integer(const int16_t & val){
    setFromZ(val, 16);
}

integer::integer(const int32_t & val){
    setFromZ(val, 32);
}

integer::integer(const int64_t & val){
    setFromZ(val, 64);
}

integer::integer(const std::string & val, const uint16_t & base)
{
    std::string::const_iterator it = val.begin();

    if (it != val.end()){
        bool sign = false;
        if ((2 <= base) && (base <= 16)){
            if (val[0] == '-'){
                sign = true;
                it++;
            }
        }
        *this = integer(it, val.end(), base);
        _sign = sign;
    }

    trim();
}

//  RHS input args only

// Assignment integer::operator

const integer & integer::operator=(const integer & rhs){
    _sign = rhs._sign;
    _value = rhs._value;
    return *this;
}

const integer & integer::operator=(const bool & rhs){
    _value.clear();
    _value.push_back(rhs);
    return *this;
}

const integer & integer::operator=(const uint8_t & rhs){
    _value.clear();
    *this += rhs;
    return *this;
}

const integer & integer::operator=(const uint16_t & rhs){
    _value.clear();
    *this += rhs;
    return *this;
}

const integer & integer::operator=(const uint32_t & rhs){
    _value.clear();
    *this += rhs;
    return *this;
}

const integer & integer::operator=(const uint64_t & rhs){
    _value.clear();
    *this += rhs;
    return *this;
}

const integer & integer::operator=(const int8_t & rhs){
    _value.clear();
    *this += rhs;
    return *this;
}

const integer & integer::operator=(const int16_t & rhs){
    _value.clear();
    *this += rhs;
    return *this;
}

const integer & integer::operator=(const int32_t & rhs){
    _value.clear();
    *this += rhs;
    return *this;
}

const integer & integer::operator=(const int64_t & rhs){
    _value.clear();
    *this += rhs;
    return *this;
}

// Typecast integer::operators
integer::operator bool() const{
    return !_value.empty();
}

integer::operator uint8_t() const{
    if (_value.empty()){
        return 0;
    }
    uint8_t out = static_cast <uint8_t> (_value.back() & 255);
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator uint16_t() const{
    uint16_t out = 0;
    for(uint8_t x = 0; x < std::min(_value.size(), 2 / sizeof(DIGIT)); x++){
        out += static_cast <uint16_t> (_value[_value.size() - x - 1]) << (x * BITS);
    }
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator uint32_t() const{
    uint32_t out = 0;
    for(uint8_t x = 0; x < std::min(_value.size(), 4 / sizeof(DIGIT)); x++){
        out += static_cast <uint32_t> (_value[_value.size() - x - 1]) << (x * BITS);
    }
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator uint64_t() const{
    uint64_t out = 0;
    for(uint8_t x = 0; x < std::min(_value.size(), 8 / sizeof(DIGIT)); x++){
        out += static_cast <uint64_t> (_value[_value.size() - x - 1]) << (x * BITS);
    }
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator int8_t() const{
    if (_value.empty()){
        return 0;
    }
    int8_t out = static_cast <uint8_t> (_value.back() & 255);
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator int16_t() const{
    int16_t out = 0;
    for(uint8_t x = 0; x < std::min(_value.size(), 2 / sizeof(DIGIT)); x++){
        out += static_cast <int16_t> (_value[_value.size() - x - 1]) << (x * BITS);
    }
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator int32_t() const{
    int32_t out = 0;
    for(uint8_t x = 0; x < std::min(_value.size(), 4 / sizeof(DIGIT)); x++){
        out += static_cast <int32_t> (_value[_value.size() - x - 1]) << (x * BITS);
    }
    if (_sign){
        out = -out;
    }
    return out;
}

integer::operator int64_t() const{
    int64_t out = 0;
    for(uint8_t x = 0; x < std::min(_value.size(), 8 / sizeof(DIGIT)); x++){
        out += static_cast <int64_t> (_value[_value.size() - x - 1]) << (x * BITS);
    }
    if (_sign){
        out = -out;
    }
    return out;
}

// Bitwise integer::operators
integer integer::operator&(const integer & rhs) const{
    REP out;
    for(REP::const_reverse_iterator i = _value.rbegin(), j = rhs._value.rbegin(); (i != _value.rend()) && (j != rhs._value.rend()); i++, j++){
        out.push_front(*i & *j);
    }
    return integer(out, _sign & rhs._sign);
}

integer integer::operator&(const bool & rhs) const{
    return *this & integer(rhs);
}

integer integer::operator&(const uint8_t & rhs) const{
    return *this & integer(rhs);
}

integer integer::operator&(const uint16_t & rhs) const{
    return *this & integer(rhs);
}

integer integer::operator&(const uint32_t & rhs) const{
    return *this & integer(rhs);
}

integer integer::operator&(const uint64_t & rhs) const{
    return *this & integer(rhs);
}

integer integer::operator&(const int8_t & rhs) const{
    return *this & integer(rhs);
}

integer integer::operator&(const int16_t & rhs) const{
    return *this & integer(rhs);
}

integer integer::operator&(const int32_t & rhs) const{
    return *this & integer(rhs);
}

integer integer::operator&(const int64_t & rhs) const{
    return *this & integer(rhs);
}

integer integer::operator&=(const integer & rhs){
    *this = *this & rhs;
    trim();
    return *this;
}

integer integer::operator&=(const bool & rhs){
    *this &= integer(rhs);
    return *this;
}

integer integer::operator&=(const uint8_t & rhs){
    *this &= integer(rhs);
    return *this;
}

integer integer::operator&=(const uint16_t & rhs){
    *this &= integer(rhs);
    return *this;
}

integer integer::operator&=(const uint32_t & rhs){
    *this &= integer(rhs);
    return *this;
}

integer integer::operator&=(const uint64_t & rhs){
    *this &= integer(rhs);
    return *this;
}

integer integer::operator&=(const int8_t & rhs){
    *this &= integer(rhs);
    return *this;
}

integer integer::operator&=(const int16_t & rhs){
    *this &= integer(rhs);
    return *this;
}

integer integer::operator&=(const int32_t & rhs){
    *this &= integer(rhs);
    return *this;
}

integer integer::operator&=(const int64_t & rhs){
    *this &= integer(rhs);
    return *this;
}

integer integer::operator|(const integer & rhs) const{
    REP out;
    REP::const_reverse_iterator i = _value.rbegin(), j = rhs._value.rbegin();
    for(; (i != _value.rend()) && (j != rhs._value.rend()); i++, j++){
        out.push_front(*i | *j);
    }
    while (i != _value.rend()){
        out.push_front(*i++);
    }
    while (j != rhs._value.rend()){
        out.push_front(*j++);
    }
    return integer(out, _sign | rhs._sign);
}

integer integer::operator|(const bool & rhs) const{
    return *this | integer(rhs);
}

integer integer::operator|(const uint8_t & rhs) const{
    return *this | integer(rhs);
}

integer integer::operator|(const uint16_t & rhs) const{
    return *this | integer(rhs);
}

integer integer::operator|(const uint32_t & rhs) const{
    return *this | integer(rhs);
}

integer integer::operator|(const uint64_t & rhs) const{
    return *this | integer(rhs);
}

integer integer::operator|(const int8_t & rhs) const{
    return *this | integer(rhs);
}

integer integer::operator|(const int16_t & rhs) const{
    return *this | integer(rhs);
}

integer integer::operator|(const int32_t & rhs) const{
    return *this | integer(rhs);
}

integer integer::operator|(const int64_t & rhs) const{
    return *this | integer(rhs);
}

integer integer::operator|=(const integer & rhs){
    *this = *this | rhs;
    trim();
    return *this;
}

integer integer::operator|=(const bool & rhs){
    *this |= integer(rhs);
    return *this;
}

integer integer::operator|=(const uint8_t & rhs){
    *this |= integer(rhs);
    return *this;
}

integer integer::operator|=(const uint16_t & rhs){
    *this |= integer(rhs);
    return *this;
}

integer integer::operator|=(const uint32_t & rhs){
    *this |= integer(rhs);
    return *this;
}

integer integer::operator|=(const uint64_t & rhs){
    *this |= integer(rhs);
    return *this;
}

integer integer::operator|=(const int8_t & rhs){
    *this |= integer(rhs);
    return *this;
}

integer integer::operator|=(const int16_t & rhs){
    *this |= integer(rhs);
    return *this;
}

integer integer::operator|=(const int32_t & rhs){
    *this |= integer(rhs);
    return *this;
}

integer integer::operator|=(const int64_t & rhs){
    *this |= integer(rhs);
    return *this;
}

integer integer::operator^(const integer & rhs) const{
    REP out;
    REP::const_reverse_iterator i = _value.rbegin(), j = rhs._value.rbegin();
    for(; (i != _value.rend()) && (j != rhs._value.rend()); i++, j++){
        out.push_front(*i ^ *j);
    }
    while (i != _value.rend()){
        out.push_front(*i++);
    }
    while (j != rhs._value.rend()){
        out.push_front(*j++);
    }
    return integer(out, _sign ^ rhs._sign);
}

integer integer::operator^(const bool & rhs) const{
    return *this ^ integer(rhs);
}

integer integer::operator^(const uint8_t & rhs) const{
    return *this ^ integer(rhs);
}

integer integer::operator^(const uint16_t & rhs) const{
    return *this ^ integer(rhs);
}

integer integer::operator^(const uint32_t & rhs) const{
    return *this ^ integer(rhs);
}

integer integer::operator^(const uint64_t & rhs) const{
    return *this ^ integer(rhs);
}

integer integer::operator^(const int8_t & rhs) const{
    return *this ^ integer(rhs);
}

integer integer::operator^(const int16_t & rhs) const{
    return *this ^ integer(rhs);
}

integer integer::operator^(const int32_t & rhs) const{
    return *this ^ integer(rhs);
}

integer integer::operator^(const int64_t & rhs) const{
    return *this ^ integer(rhs);
}

integer integer::operator^=(const integer & rhs){
    *this = *this ^ rhs;
    return *this;
}

integer integer::operator^=(const bool & rhs){
    *this ^= integer(rhs);
    return *this;
}

integer integer::operator^=(const uint8_t & rhs){
    *this ^= integer(rhs);
    return *this;
}

integer integer::operator^=(const uint16_t & rhs){
    *this ^= integer(rhs);
    return *this;
}

integer integer::operator^=(const uint32_t & rhs){
    *this ^= integer(rhs);
    return *this;
}

integer integer::operator^=(const uint64_t & rhs){
    *this ^= integer(rhs);
    return *this;
}

integer integer::operator^=(const int8_t & rhs){
    *this ^= integer(rhs);
    return *this;
}

integer integer::operator^=(const int16_t & rhs){
    *this ^= integer(rhs);
    return *this;
}

integer integer::operator^=(const int32_t & rhs){
    *this ^= integer(rhs);
    return *this;
}

integer integer::operator^=(const int64_t & rhs){
    *this ^= integer(rhs);
    return *this;
}

integer integer::operator~(){
    REP out = _value;
    for(REP_SIZE_T i = 1; i < out.size(); i++){
        out[i] ^= NEG1;
    }
    DIGIT mask = HIGH_BIT;
    while (!(out[0] & mask)){
        mask >>= 1;
    }
    while (mask){
        out[0] ^= mask;
        mask >>= 1;
    }
    return integer(out, _sign);
}

// Bit Shift integer::operators

// left bit shift. sign is maintained
integer integer::operator<<(const integer & shift) const{
    if (!*this || !shift){
        return *this;
    }
    if (shift < 0){
        throw std::runtime_error("Error: Negative shift amount");
    }
    integer quo = shift / BITS;  // number of zeros to add to the back
    DIGIT rem = shift % BITS;    // individual bits to shift
    REP out = _value;

    // do this part first to avoid shifting zeros
    out.push_front(0);           // extra digit for shifting into
    out.push_back(0);            // extra digit for shifting from
    for(REP_SIZE_T i = 0; i < (out.size() - 1); i++){
        out[i] = (out[i] << rem) | (out[i + 1] >> (BITS - rem));
    }

    if (!out[0]){               // if the top digit is still 0
        out.pop_front();        // remove it
    }

    if (!quo){                  // if there was no need for the 0 at the end
        out.pop_back();         // remove it
    }
    else{
        // push back zeros, excluding the one already there
        for(integer i = 1; i < quo; i++){
            out.push_back(0);
        }
    }
    return integer(out, _sign);
}

integer integer::operator<<(const bool & shift) const{
    return *this << integer(shift);
}

integer integer::operator<<(const uint8_t & shift) const{
    return *this << integer(shift);
}

integer integer::operator<<(const uint16_t & shift) const{
    return *this << integer(shift);
}

integer integer::operator<<(const uint32_t & shift) const{
    return *this << integer(shift);
}

integer integer::operator<<(const uint64_t & shift) const{
    return *this << integer(shift);
}

integer integer::operator<<(const int8_t & shift) const{
    return *this << integer(shift);
}

integer integer::operator<<(const int16_t & shift) const{
    return *this << integer(shift);
}

integer integer::operator<<(const int32_t & shift) const{
    return *this << integer(shift);
}

integer integer::operator<<(const int64_t & shift) const{
    return *this << integer(shift);
}

integer integer::operator<<=(const integer & shift){
    *this = *this << integer(shift);
    trim();
    return *this;
}

integer integer::operator<<=(const bool & shift){
    *this <<= integer(shift);
    return *this;
}

integer integer::operator<<=(const uint8_t & shift){
    *this <<= integer(shift);
    return *this;
}

integer integer::operator<<=(const uint16_t & shift){
    *this <<= integer(shift);
    return *this;
}

integer integer::operator<<=(const uint32_t & shift){
    *this <<= integer(shift);
    return *this;
}

integer integer::operator<<=(const uint64_t & shift){
    *this <<= integer(shift);
    return *this;
}

integer integer::operator<<=(const int8_t & shift){
    *this <<= integer(shift);
    return *this;
}

integer integer::operator<<=(const int16_t & shift){
    *this <<= integer(shift);
    return *this;
}

integer integer::operator<<=(const int32_t & shift){
    *this <<= integer(shift);
    return *this;
}

integer integer::operator<<=(const int64_t & shift){
    *this <<= integer(shift);
    return *this;
}

// right bit shift. sign is maintained
integer integer::operator>>(const integer & shift) const{
    if (shift < 0){
        throw std::runtime_error("Error: Negative shift amount");
    }
    if (shift >= bits()){
        return 0;
    }

    integer quo = shift / BITS;     // number of digits to pop off
    DIGIT rem = shift % BITS;       // number of bits to shift afterwards
    REP out = _value;

    for(integer i = 0; i < quo; i++){
        out.pop_back();
    }
    if (rem){
        out.push_front(0);          // extra 0 for shifting from
        for(REP_SIZE_T i = 1; i < out.size(); i++){
            out[out.size() - i] = (out[out.size() - i - 1] << (BITS - rem)) | (out[out.size() - i] >> rem);
        }
        out.pop_front();
    }
    return integer(out, _sign);
}

integer integer::operator>>(const bool & shift) const{
    return *this >> integer(shift);
}

integer integer::operator>>(const uint8_t & shift) const{
    return *this >> integer(shift);
}

integer integer::operator>>(const uint16_t & shift) const{
    return *this >> integer(shift);
}

integer integer::operator>>(const uint32_t & shift) const{
    return *this >> integer(shift);
}

integer integer::operator>>(const uint64_t & shift) const{
    return *this >> integer(shift);
}

integer integer::operator>>(const int8_t & shift) const{
    return *this >> integer(shift);
}

integer integer::operator>>(const int16_t & shift) const{
    return *this >> integer(shift);
}

integer integer::operator>>(const int32_t & shift) const{
    return *this >> integer(shift);
}

integer integer::operator>>(const int64_t & shift) const{
    return *this >> integer(shift);
}

integer integer::operator>>=(const integer & shift){
    *this = *this >> integer(shift);
    trim();
    return *this;
}

integer integer::operator>>=(const bool & shift){
    *this = *this >> integer(shift);
    return *this;
}

integer integer::operator>>=(const uint8_t & shift){
    *this = *this >> integer(shift);
    return *this;
}

integer integer::operator>>=(const uint16_t & shift){
    *this = *this >> integer(shift);
    return *this;
}

integer integer::operator>>=(const uint32_t & shift){
    *this = *this >> integer(shift);
    return *this;
}

integer integer::operator>>=(const uint64_t & shift){
    *this = *this >> integer(shift);
    return *this;
}

integer integer::operator>>=(const int8_t & shift){
    *this = *this >> integer(shift);
    return *this;
}

integer integer::operator>>=(const int16_t & shift){
    *this = *this >> integer(shift);
    return *this;
}

integer integer::operator>>=(const int32_t & shift){
    *this = *this >> integer(shift);
    return *this;
}

integer integer::operator>>=(const int64_t & shift){
    *this = *this >> integer(shift);
    return *this;
}

// Logical integer::operators
bool integer::operator!(){
    return !static_cast <bool> (*this);
}

// Comparison integer::operators
bool integer::operator==(const integer & rhs) const{
    return ((_sign == rhs._sign) && (_value == rhs._value));
}

bool integer::operator==(const bool & rhs) const{
    return *this == integer(rhs);
}

bool integer::operator==(const uint8_t & rhs) const{
    return *this == integer(rhs);
}

bool integer::operator==(const uint16_t & rhs) const{
    return *this == integer(rhs);
}

bool integer::operator==(const uint32_t & rhs) const{
    return *this == integer(rhs);
}

bool integer::operator==(const uint64_t & rhs) const{
    return *this == integer(rhs);
}

bool integer::operator==(const int8_t & rhs) const{
    return *this == integer(rhs);
}

bool integer::operator==(const int16_t & rhs) const{
    return *this == integer(rhs);
}

bool integer::operator==(const int32_t & rhs) const{
    return *this == integer(rhs);
}

bool integer::operator==(const int64_t & rhs) const{
    return *this == integer(rhs);
}

bool integer::operator!=(const integer & rhs) const{
    return !(*this == rhs);
}

bool integer::operator!=(const bool & rhs) const{
    return (*this != integer(rhs));
}

bool integer::operator!=(const uint8_t & rhs) const{
    return (*this != integer(rhs));
}

bool integer::operator!=(const uint16_t & rhs) const{
    return (*this != integer(rhs));
}

bool integer::operator!=(const uint32_t & rhs) const{
    return (*this != integer(rhs));
}

bool integer::operator!=(const uint64_t & rhs) const{
    return (*this != integer(rhs));
}

bool integer::operator!=(const int8_t & rhs) const{
    return (*this != integer(rhs));
}

bool integer::operator!=(const int16_t & rhs) const{
    return (*this != integer(rhs));
}

bool integer::operator!=(const int32_t & rhs) const{
    return (*this != integer(rhs));
}

bool integer::operator!=(const int64_t & rhs) const{
    return (*this != integer(rhs));
}

// operator> not considering signs
bool integer::gt(const integer & lhs, const integer & rhs) const{
    if (lhs._value.size() > rhs._value.size()){
        return true;
    }
    if (lhs._value.size() < rhs._value.size()){
        return false;
    }
    if (lhs._value == rhs._value){
        return false;
    }
    for(REP_SIZE_T i = 0; i < lhs._value.size(); i++){
        if (lhs._value[i] != rhs._value[i]){
            return lhs._value[i] > rhs._value[i];
        }
    }
    return false;
}

bool integer::operator>(const integer & rhs) const{
    if (_sign & !rhs._sign){               // - > +
        return false;
    }
    else if (!_sign & rhs._sign){          // + > -
        return true;
    }
    else if (_sign & rhs._sign){           // - > -
        return !gt(*this, rhs);
    }
    // else (!_sign & !rhs._sign)          // + > +
    return gt(*this, rhs);
}

bool integer::operator>(const bool & rhs) const{
    return *this > integer(rhs);
}

bool integer::operator>(const uint8_t & rhs) const{
    return *this > integer(rhs);
}

bool integer::operator>(const uint16_t & rhs) const{
    return *this > integer(rhs);
}

bool integer::operator>(const uint32_t & rhs) const{
    return *this > integer(rhs);
}

bool integer::operator>(const uint64_t & rhs) const{
    return *this > integer(rhs);
}

bool integer::operator>(const int8_t & rhs) const{
    return *this > integer(rhs);
}

bool integer::operator>(const int16_t & rhs) const{
    return *this > integer(rhs);
}

bool integer::operator>(const int32_t & rhs) const{
    return *this > integer(rhs);
}

bool integer::operator>(const int64_t & rhs) const{
    return *this > integer(rhs);
}

bool integer::operator>=(const integer & rhs) const{
    return ((*this > rhs) | (*this == rhs));
}

bool integer::operator>=(const bool & rhs) const{
    return *this >= integer(rhs);
}

bool integer::operator>=(const uint8_t & rhs) const{
    return *this >= integer(rhs);
}

bool integer::operator>=(const uint16_t & rhs) const{
    return *this >= integer(rhs);
}

bool integer::operator>=(const uint32_t & rhs) const{
    return *this >= integer(rhs);
}

bool integer::operator>=(const uint64_t & rhs) const{
    return *this >= integer(rhs);
}

bool integer::operator>=(const int8_t & rhs) const{
    return *this >= integer(rhs);
}

bool integer::operator>=(const int16_t & rhs) const{
    return *this >= integer(rhs);
}

bool integer::operator>=(const int32_t & rhs) const{
    return *this >= integer(rhs);
}

bool integer::operator>=(const int64_t & rhs) const{
    return *this >= integer(rhs);
}

// operator< not considering signs
bool integer::lt(const integer & lhs, const integer & rhs) const{
    if (lhs._value.size() < rhs._value.size()){
        return true;
    }
    if (lhs._value.size() > rhs._value.size()){
        return false;
    }
    if (lhs._value == rhs._value){
        return false;
    }
    for(REP_SIZE_T i = 0; i < lhs._value.size(); i++){
        if (lhs._value[i] != rhs._value[i]){
            return lhs._value[i] < rhs._value[i];
        }
    }
    return false;
}

bool integer::operator<(const integer & rhs) const{
    if (_sign & !rhs._sign){                   // - < +
        return true;
    }
    else if (!_sign & rhs._sign){              // + < -
        return false;
    }
    else if (_sign & rhs._sign){               // - < -
        return !lt(*this, rhs);
    }
    // else (!_sign & !rhs._sign)              // + < +
    return lt(*this, rhs);
}

bool integer::operator<(const bool & rhs) const{
    return *this < integer(rhs);
}

bool integer::operator<(const uint8_t & rhs) const{
    return *this < integer(rhs);
}

bool integer::operator<(const uint16_t & rhs) const{
    return *this < integer(rhs);
}

bool integer::operator<(const uint32_t & rhs) const{
    return *this < integer(rhs);
}

bool integer::operator<(const uint64_t & rhs) const{
    return *this < integer(rhs);
}

bool integer::operator<(const int8_t & rhs) const{
    return *this < integer(rhs);
}

bool integer::operator<(const int16_t & rhs) const{
    return *this < integer(rhs);
}

bool integer::operator<(const int32_t & rhs) const{
    return *this < integer(rhs);
}

bool integer::operator<(const int64_t & rhs) const{
    return *this < integer(rhs);
}

bool integer::operator<=(const integer & rhs) const{
    return ((*this < rhs) | (*this == rhs));
}

bool integer::operator<=(const bool & rhs) const{
    return *this <= integer(rhs);
}

bool integer::operator<=(const uint8_t & rhs) const{
    return *this <= integer(rhs);
}

bool integer::operator<=(const uint16_t & rhs) const{
    return *this <= integer(rhs);
}

bool integer::operator<=(const uint32_t & rhs) const{
    return *this <= integer(rhs);
}

bool integer::operator<=(const uint64_t & rhs) const{
    return *this <= integer(rhs);
}

bool integer::operator<=(const int8_t & rhs) const{
    return *this <= integer(rhs);
}

bool integer::operator<=(const int16_t & rhs) const{
    return *this <= integer(rhs);
}

bool integer::operator<=(const int32_t & rhs) const{
    return *this <= integer(rhs);
}

bool integer::operator<=(const int64_t & rhs) const{
    return *this <= integer(rhs);
}

// Arithmetic integer::operators
integer integer::add(const integer & lhs, const integer & rhs) const{
    REP out;
    REP::const_reverse_iterator i = lhs._value.rbegin(), j = rhs._value.rbegin();
    bool carry = false;
    DOUBLE_DIGIT sum;
    for(; ((i != lhs._value.rend()) && (j != rhs._value.rend())); i++, j++){
        sum = static_cast <DOUBLE_DIGIT> (*i) + static_cast <DOUBLE_DIGIT> (*j) + carry;
        out.push_front(sum);
        carry = (sum > NEG1);
    }
    for(; i != lhs._value.rend(); i++){
        sum = static_cast <DOUBLE_DIGIT> (*i) + carry;
        out.push_front(sum);
        carry = (sum > NEG1);
    }
    for(; j != rhs._value.rend(); j++){
        sum = static_cast <DOUBLE_DIGIT> (*j) + carry;
        out.push_front(sum);
        carry = (sum > NEG1);
    }
    if (carry){
        out.push_front(1);
    }
    return integer(out);
}

integer integer::operator+(const integer & rhs) const{
    if (!rhs){
        return *this;
    }
    if (!*this){
        return rhs;
    }

    integer out = *this;
    if (gt(out, rhs)){                      // lhs > rhs
        if (_sign == rhs._sign){            // same sign: lhs + rhs
            out = add(out, rhs);
        }
        else{                               // different signs: lhs - rhs
            out = sub(out, rhs);
        }
        out._sign = _sign;                  // lhs sign dominates
    }
    else if (lt(out, rhs)){                 // lhs < rhs
        if (_sign == rhs._sign){            // same sign: rhs + lhs
            out = add(rhs, out);
        }
        else{                               // different sign: rhs - lhs
            out = sub(rhs, out);
        }
        out._sign = rhs._sign;              // rhs sign dominates
    }
    else{                                   // lhs == rhs
        if (_sign == rhs._sign){            // same sign: double value
            out <<= 1;
            out._sign = _sign;
        }
        else{                               // different signs: 0
            return 0;
        }
    }
    out.trim();
    return out;
}

integer integer::operator+(const bool & rhs) const{
    return *this + integer(rhs);
}

integer integer::operator+(const uint8_t & rhs) const{
    return *this + integer(rhs);
}

integer integer::operator+(const uint16_t & rhs) const{
    return *this + integer(rhs);
}

integer integer::operator+(const uint32_t & rhs) const{
    return *this + integer(rhs);
}

integer integer::operator+(const uint64_t & rhs) const{
    return *this + integer(rhs);
}

integer integer::operator+(const int8_t & rhs) const{
    return *this + integer(rhs);
}

integer integer::operator+(const int16_t & rhs) const{
    return *this + integer(rhs);
}

integer integer::operator+(const int32_t & rhs) const{
    return *this + integer(rhs);
}

integer integer::operator+(const int64_t & rhs) const{
    return *this + integer(rhs);
}

integer integer::operator+=(const integer & rhs){
    *this = *this + rhs;
    return *this;
}

integer integer::operator+=(const bool & rhs){
    *this = *this + rhs;
    return *this;
}

integer integer::operator+=(const uint8_t & rhs){
    *this = *this + rhs;
    return *this;
}

integer integer::operator+=(const uint16_t & rhs){
    return *this += integer(rhs);
}

integer integer::operator+=(const uint32_t & rhs){
    *this = *this + rhs;
    return *this;
}

integer integer::operator+=(const uint64_t & rhs){
    *this = *this + rhs;
    return *this;
}

integer integer::operator+=(const int8_t & rhs){
    *this = *this + rhs;
    return *this;
}

integer integer::operator+=(const int16_t & rhs){
    *this = *this + rhs;
    return *this;
}

integer integer::operator+=(const int32_t & rhs){
    *this = *this + rhs;
    return *this;
}

integer integer::operator+=(const int64_t & rhs){
    *this = *this + rhs;
    return *this;
}

// Subtraction as done by hand
integer integer::long_sub(const integer & lhs, const integer & rhs) const{
    // rhs always smaller than lhs
    integer out = lhs;
    REP_SIZE_T lsize = out._value.size() - 1;
    REP_SIZE_T rsize = rhs._value.size() - 1;
    for(REP_SIZE_T x = 0; x < rsize + 1; x++){
        // if rhs digit is smaller than lhs digit, subtract
        if (rhs._value[rsize - x] <= out._value[lsize - x]){
            out._value[lsize - x] -= rhs._value[rsize - x];
        }
        else{// carry
            REP_SIZE_T y = lsize - x - 1;
            while (!out._value[y]){
                y--;
            }
            out._value[y]--;
            y++;
            for(; y < lsize - x; y++){
                out._value[y] = NEG1;
            }
            out._value[y] = static_cast <DOUBLE_DIGIT> (out._value[y]) + (static_cast <uint64_t> (1) << BITS) - rhs._value[rsize - x];
        }
    }
    return out;
}

//// Two's Complement Subtraction
//integer integer::two_comp_sub(const integer & lhs, const integer & rhs){
//    rhs = rhs.twos_complement(lhs.bits());
//    return add(lhs, rhs) & (~(integer(1) << lhs.bits()));   // Flip bits to get max of 1 << x
//}

integer integer::sub(const integer & lhs, const integer & rhs) const{
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
    // return two_comp_sub(lhs, rhs);
}

integer integer::operator-(const integer & rhs) const{
    integer out = *this;
    if (gt(out, rhs)){              // if lhs > rhs
        if (_sign == rhs._sign){    // same sign: lhs - rhs
            out = sub(out, rhs);
        }
        else{
            out = add(out, rhs);    // different signs: lhs + rhs
        }
        out._sign = _sign;          // lhs sign dominates
    }
    else if (lt(out, rhs)){         // if lhs < rhs
        if (_sign == rhs._sign){    // same sign: rhs - lhs
            out = sub(rhs, out);
        }
        else{                       // different sign: rhs + lhs
            out = add(out, rhs);
        }
        out._sign = rhs._sign;      // rhs sign dominates
    }
    else{                           // if lhs == rhs
        if (_sign == rhs._sign){    // same signs: double value
            return 0;
        }
        else{                       // different signs: 0
            out <<= 1;
            out._sign = _sign;
        }
    }
    out.trim();
    return out;
}

integer integer::operator-(const bool & rhs) const{
    return *this - integer(rhs);
}

integer integer::operator-(const uint8_t & rhs) const{
    return *this - integer(rhs);
}

integer integer::operator-(const uint16_t & rhs) const{
    return *this - integer(rhs);
}

integer integer::operator-(const uint32_t & rhs) const{
    return *this - integer(rhs);
}

integer integer::operator-(const uint64_t & rhs) const{
    return *this - integer(rhs);
}

integer integer::operator-(const int8_t & rhs) const{
    return *this - integer(rhs);
}

integer integer::operator-(const int16_t & rhs) const{
    return *this - integer(rhs);
}

integer integer::operator-(const int32_t & rhs) const{
    return *this - integer(rhs);
}

integer integer::operator-(const int64_t & rhs) const{
    return *this - integer(rhs);
}

integer integer::operator-=(const integer & rhs){
    *this = *this - rhs;
    return *this;
}

integer integer::operator-=(const bool & rhs){
    *this -= integer(rhs);
    return *this;
}

integer integer::operator-=(const uint8_t & rhs){
    *this -= integer(rhs);
    return *this;
}

integer integer::operator-=(const uint16_t & rhs){
    return *this -= integer(rhs);
}

integer integer::operator-=(const uint32_t & rhs){
    *this -= integer(rhs);
    return *this;
}

integer integer::operator-=(const uint64_t & rhs){
    *this -= integer(rhs);
    return *this;
}

integer integer::operator-=(const int8_t & rhs){
    *this -= integer(rhs);
    return *this;
}

integer integer::operator-=(const int16_t & rhs){
    *this -= integer(rhs);
    return *this;
}

integer integer::operator-=(const int32_t & rhs){
    *this -= integer(rhs);
    return *this;
}

integer integer::operator-=(const int64_t & rhs){
    *this -= integer(rhs);
    return *this;
}

// // Peasant Multiplication
// integer integer::peasant(const integer & lhs, const integer & rhs) const{
   // integer rhs_copy = rhs;
   // integer sum = 0;
   // for(REP_SIZE_T x = 0; x < lhs.bits(); x++){
      // if (lhs[x]){
          // sum += add(sum, rhs_copy);
       // }
      // rhs_copy <<= 1;
   // }
   // return sum;
// }

// // Recurseive Peasant Algorithm
// integer integer::recursive_peasant(const integer & lhs, const integer & rhs) const{
   // if (!rhs){
       // return 0;
   // }
   // if (rhs & 1){
       // return lhs + recursive_peasant(lhs << 1, rhs >> 1);
   // }
   // return recursive_peasant(lhs << 1, rhs >> 1);
// }

// // Recursive Multiplication
// integer integer::recursive_mult(const integer & lhs, const integer & rhs) const{
   // if (!rhs){
      // return 0;
   // }
   // integer z = recursive_mult(lhs, rhs >> 1);
   // if (!(rhs & 1)){
      // return z << 1;
   // }
   // return add(lhs, z << 1);
// }

// // Karatsuba Algorithm
// integer integer::karatsuba(const integer & lhs, const integer & rhs, integer bm) const{
  // // b is REP = 256
  // // m is chars = 4
  // // bm is max _value = b ^ m

  // if ((lhs <= bm) | (rhs <= bm))
      // return peasant(lhs, rhs);

  // std::pair <integer, integer> x = dm(lhs, bm);
  // std::pair <integer, integer> y = dm(rhs, bm);
  // integer x0 = x.second;
  // integer x1 = x.first;
  // integer y0 = y.second;
  // integer y1 = y.first;

  // integer z0 = karatsuba(x0, y0);
  // integer z2 = karatsuba(x1, y1);
  // integer z1 = sub(sub(karatsuba(add(x1, x0), add(y1, y0)), z2), z0);
  // return add(karatsuba(add(karatsuba(z2, bm), z1), bm), z0);
// }

// // Toom-Cook multiplication
// // as described at http://en.wikipedia.org/wiki/Toom%E2%80%93Cook_multiplications
// // This implementation is a bit weird. In the pointwise Multiplcation step, using
// // operator* and long_mult works, but everything else fails.
// // It's also kind of slow.
// integer integer::toom_cook_3(integer m, integer n, integer bm){
  // if ((m <= bm) | (n <= bm)){
      // return peasant(m, n);
   // }

  // // Splitting
  // integer i = integer(std::max(m.log(3), n.log(3))) / 3 + 1;
  // integer bi = integer(3).pow(i);
  // integer B = 1;
  // integer REP = 10;
  // while (B < bi){
      // B *= REP;
   // }

  // integer M[3], N[3];
  // for(uint8_t i = 0; i < 3; i++){
      // std::pair <integer, integer> tm = dm(m, B);
      // std::pair <integer, integer> tn = dm(n, B);
      // m = tm.first;
      // n = tn.first;
      // M[i] = tm.second;
      // N[i] = tn.second;
  // }

  // // Evaluation
  // //             {0,             1,                 -1,                         -2,                             inf}
  // integer p[5] = {M[0], M[0] + M[1] + M[2], M[0] - M[1] + M[2], M[0] - M[1] - M[1] + M[2] + M[2] + M[2] + M[2], M[2]};
  // integer q[5] = {N[0], N[0] + N[1] + N[2], N[0] - N[1] + N[2], N[0] - N[1] - N[1] + N[2] + N[2] + N[2] + N[2], N[2]};

  // // Pointwise Multiplication
  // integer r[5];
  // for(uint8_t i = 0; i < 5; i++)
      // r[i] = p[i] * q[i];                 // don't understand why only integer::operator* and long_mult can be used here

  // // Interpolation
  // integer r0 = r[0];
  // integer r4 = r[4];
  // integer r3 = (r[3] - r[1]) / 3;
  // integer r1 = (r[1] - r[2]) / 2;
  // integer r2 = r[2] - r[0];
  // r3 = (r2 - r3) / 2 + r4 + r4;
  // r2 = r2 + r1 - r4;
  // r1 = r1 - r3;

  // // Recomposition
  // return peasant(peasant(peasant(peasant(r4, B) + r3, B) + r2, B) + r1, B) + r0;
// }

// // Long multiplication
// integer integer::long_mult(const integer & lhs, const integer & rhs) const{
   // unsigned int zeros = 0;
   // integer row, out = 0;
   // for(REP::const_reverse_iterator i = lhs._value.rbegin(); i != lhs._value.rend(); i++){
       // row._value = REP(zeros++, 0); // zeros on the right hand side
       // DIGIT carry = 0;
       // for(REP::const_reverse_iterator j = rhs._value.rbegin(); j != rhs._value.rend(); j++){
           // DOUBLE_DIGIT prod = (DOUBLE_DIGIT) *i * (DOUBLE_DIGIT) *j + carry;// multiply through
           // row._value.push_front(prod & NEG1);
           // carry = prod >> BITS;
       // }
       // if (carry){
           // row._value.push_front(carry);
       // }
       // out = add(out, row);
   // }
   // return out;
// }

//Private FFT helper function
int integer::fft(std::deque<double>& data, bool dir) const
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
integer integer::fft_mult(const integer& lhs, const integer& rhs) const{
     //Convert each integer to input wanted by fft()
     size_t size = 1;
     while (size < lhs._value.size()*2){
          size <<= 1;
     }
     while (size < rhs._value.size()*2){
          size <<= 1;
     }

     std::deque<double> lhs_fft;
     lhs_fft.resize(size*2, 0);
     for (size_t i = 0; i < lhs._value.size(); i++){
          lhs_fft[i*2] = double(lhs._value[lhs._value.size()-1-i]);
     }

     std::deque<double> rhs_fft;
     rhs_fft.resize(size*2, 0);
     for (size_t i = 0; i < rhs._value.size(); i++){
          rhs_fft[i*2] = double(rhs._value[rhs._value.size()-1-i]);
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
          out._value.push_front(DIGIT(current+0.0001));
     }

     //Finish up
     return out;
}

integer integer::operator*(const integer & rhs) const{
    // quick checks
    if (!*this || !rhs){                 // if multiplying by 0
        return 0;
    }
    if (*this == 1){                     // if multiplying by 1
        return rhs;
    }
    if (rhs == 1){                       // if multiplying by 1
        return *this;
    }

    // integer out = peasant(*this, rhs);
    // integer out = recursive_peasant(*this, rhs);
    // integer out = recursive_mult(*this, rhs);
    // integer out = karatsuba(*this, rhs);
    // integer out = toom_cook_3(*this, rhs);
    // integer out = long_mult(*this, rhs);
    integer out = fft_mult(*this, rhs);
    out._sign = _sign ^ rhs._sign;
    out.trim();
    return out;
}

integer integer::operator*(const bool & rhs) const{
    return *this * integer(rhs);
}

integer integer::operator*(const uint8_t & rhs) const{
    return *this * integer(rhs);
}

integer integer::operator*(const uint16_t & rhs) const{
    return *this * integer(rhs);
}

integer integer::operator*(const uint32_t & rhs) const{
    return *this * integer(rhs);
}

integer integer::operator*(const uint64_t & rhs) const{
    return *this * integer(rhs);
}

integer integer::operator*(const int8_t & rhs) const{
    return *this * integer(rhs);
}

integer integer::operator*(const int16_t & rhs) const{
    return *this * integer(rhs);
}

integer integer::operator*(const int32_t & rhs) const{
    return *this * integer(rhs);
}

integer integer::operator*(const int64_t & rhs) const{
    return *this * integer(rhs);
}

integer integer::operator*=(const integer & rhs){
    *this = *this * rhs;
    return *this;
}

integer integer::operator*=(const bool & rhs){
    *this = *this * rhs;
    return *this;
}

integer integer::operator*=(const uint8_t & rhs){
    *this = *this * rhs;
    return *this;
}

integer integer::operator*=(const uint16_t & rhs){
    return *this *= integer(rhs);
}

integer integer::operator*=(const uint32_t & rhs){
    *this = *this * rhs;
    return *this;
}

integer integer::operator*=(const uint64_t & rhs){
    *this = *this * rhs;
    return *this;
}

integer integer::operator*=(const int8_t & rhs){
    *this = *this * rhs;
    return *this;
}

integer integer::operator*=(const int16_t & rhs){
    *this = *this * rhs;
    return *this;
}

integer integer::operator*=(const int32_t & rhs){
    *this = *this * rhs;
    return *this;
}

integer integer::operator*=(const int64_t & rhs){
    *this = *this * rhs;
    return *this;
}

// // Naive Division: keep subtracting until lhs == 0
// std::pair <integer, integer> integer::naive_div(const integer & lhs, const integer & rhs) const{
    // std::pair <integer, integer> qr (0, lhs);
    // while (qr.second >= rhs){
        // qr.second -= rhs;
        // qr.first++;
    // }
    // return qr;
// }

// // Long Division returning both quotient and remainder
// std::pair <integer, integer> integer::long_div(const integer & lhs, const integer & rhs) const{
   // std::pair <integer, integer> qr(0, lhs);
   // integer copyd = rhs;
   // integer adder = 1;
   // integer shift = qr.second.bits() - copyd.bits();
    // copyd <<= shift;
    // adder <<= shift;
   // // while (qr.second > copyd){
       // // copyd <<= 1;
       // // adder <<= 1;
   // // }
   // while (qr.second >= rhs){
       // if (qr.second >= copyd){
           // qr.second -= copyd;
           // qr.first |= adder;
       // }
       // copyd >>= 1;
       // adder >>= 1;
   // }
   // return qr;
// }

// // Recursive Division that returns both the quotient and remainder
// // Recursion took up way too much memory
// std::pair <integer, integer> integer::recursive_divmod(const integer & lhs, const integer & rhs) const{
   // std::pair <integer, integer> qr;
   // if (!lhs){
       // qr.first = 0;
       // qr.second = 0;
       // return qr;
   // }
   // qr = recursive_divmod(lhs >> 1, rhs);
   // qr.first <<= 1;
   // qr.second <<= 1;
   // if (lhs & 1)
       // qr.second++;
   // if (qr.second >= rhs){
       // qr.second -= rhs;
       // qr.first++;
   // }
   // return qr;
// }

// Non-Recursive version of above algorithm
std::pair <integer, integer> integer::non_recursive_divmod(const integer & lhs, const integer & rhs) const{
    std::pair <integer, integer> qr (0, 0);
    for(REP_SIZE_T x = lhs.bits(); x > 0; x--){
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
std::pair <integer, integer> integer::dm(const integer & lhs, const integer & rhs) const{
    if (!rhs){                           // divide by 0 error
        throw std::runtime_error("Error: division or modulus by 0");
    }
    std::pair <integer, integer> out;
    if (rhs == 1){                      // divide by 1 check
        out.first = lhs;
        out.second = 0;
        return out;
    }
    if (lhs == rhs){                    // divide by same _value check
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
    // return naive_div(lhs, rhs);
    // return long_div(lhs, rhs);
    // return recursive_divmod(lhs, rhs);
    return non_recursive_divmod(lhs, rhs);
}

integer integer::operator/(const integer & rhs) const{
    integer out = dm(*this, rhs).first;
    out._sign = _sign ^ rhs._sign;
    out.trim();
    return out;
}

integer integer::operator/(const bool & rhs) const{
    return *this / integer(rhs);
}

integer integer::operator/(const uint8_t & rhs) const{
    return *this / integer(rhs);
}

integer integer::operator/(const uint16_t & rhs) const{
    return *this / integer(rhs);
}

integer integer::operator/(const uint32_t & rhs) const{
    return *this / integer(rhs);
}

integer integer::operator/(const uint64_t & rhs) const{
    return *this / integer(rhs);
}

integer integer::operator/(const int8_t & rhs) const{
    return *this / integer(rhs);
}

integer integer::operator/(const int16_t & rhs) const{
    return *this / integer(rhs);
}

integer integer::operator/(const int32_t & rhs) const{
    return *this / integer(rhs);
}

integer integer::operator/(const int64_t & rhs) const{
    return *this / integer(rhs);
}

integer integer::operator/=(const integer & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator/=(const bool & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator/=(const uint8_t & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator/=(const uint16_t & rhs){
    return *this /= integer(rhs);
}

integer integer::operator/=(const uint32_t & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator/=(const uint64_t & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator/=(const int8_t & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator/=(const int16_t & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator/=(const int32_t & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator/=(const int64_t & rhs){
    *this = *this / rhs;
    return *this;
}

integer integer::operator%(const integer & rhs) const{
    bool s1 = _sign,
         s2 = rhs._sign;
    integer out = dm(*this, rhs).second;
    if (!out._value.empty()){
        if (s1 == s2){
            out._sign = s1;
        }
        else{
            out = rhs - out;
            out._sign = s2;
        }
    }
    out.trim();
    return out;
}

integer integer::operator%(const bool & rhs) const{
    return *this % integer(rhs);
}

integer integer::operator%(const uint8_t & rhs) const{
    return *this % integer(rhs);
}

integer integer::operator%(const uint16_t & rhs) const{
    return *this % integer(rhs);
}

integer integer::operator%(const uint32_t & rhs) const{
    return *this % integer(rhs);
}

integer integer::operator%(const uint64_t & rhs) const{
    return *this % integer(rhs);
}

integer integer::operator%(const int8_t & rhs) const{
    return *this % integer(rhs);
}

integer integer::operator%(const int16_t & rhs) const{
    return *this % integer(rhs);
}

integer integer::operator%(const int32_t & rhs) const{
    return *this % integer(rhs);
}

integer integer::operator%(const int64_t & rhs) const{
    return *this % integer(rhs);
}

integer integer::operator%=(const integer & rhs){
    *this = *this % rhs;
    return *this;
}

integer integer::operator%=(const bool & rhs){
    *this = *this % rhs;
    return *this;
}

integer integer::operator%=(const uint8_t & rhs){
    *this = *this % rhs;
    return *this;
}

integer integer::operator%=(const uint16_t & rhs){
    return *this %= integer(rhs);
}

integer integer::operator%=(const uint32_t & rhs){
    *this = *this % rhs;
    return *this;
}

integer integer::operator%=(const uint64_t & rhs){
    *this = *this % rhs;
    return *this;
}

integer integer::operator%=(const int8_t & rhs){
    *this = *this % rhs;
    return *this;
}

integer integer::operator%=(const int16_t & rhs){
    *this = *this % rhs;
    return *this;
}

integer integer::operator%=(const int32_t & rhs){
    *this = *this % rhs;
    return *this;
}

integer integer::operator%=(const int64_t & rhs){
    *this = *this % rhs;
    return *this;
}

// Increment integer::operator
const integer & integer::operator++(){
    *this += 1;
    return *this;
}

integer integer::operator++(int){
    integer temp(*this);
    ++*this;
    return temp;
}

// Decrement integer::operator
const integer & integer::operator--(){
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
integer integer::operator-() const{
    integer out = *this;
    if (out._value.size()){
        out._sign = !out._sign;
    }
    return out;
}

// get private _values
bool integer::sign() const{
    return _sign;                    // false = pos, true = neg
}

// get number of bits
integer::REP_SIZE_T integer::bits() const{
    if (_value.empty()){
        return 0;
    }
    unsigned int out = _value.size() * BITS;
    DIGIT mask = HIGH_BIT;
    while (!(_value[0] & mask)){
        out--;
        mask >>= 1;
    }
    return out;
}

// get number of bytes
integer::REP_SIZE_T integer::bytes() const{
    return digits() * BITS >> 3;
}

// get number of digits
integer::REP_SIZE_T integer::digits() const{
    return _value.size();
}

// get internal data
integer::REP integer::data() const{
    return _value;
}

// Miscellaneous Functions
integer integer::twos_complement(unsigned int bits) const{
    integer::REP out = _value;
    for(REP_SIZE_T i = 1; i < out.size(); i++){
        out[i] ^= NEG1;
    }
    integer::DIGIT mask = HIGH_BIT;
    while (!(out[0] & mask)){
        mask >>= 1;
    }
    integer top = integer(1) << (static_cast <uint64_t> (out.size() - 1) * BITS);
    while (mask){
        out[0] ^= mask;
        mask >>= 1;
        top <<= 1;
    }
    integer OUT(out, _sign);
    while (bits){
        OUT ^= top;
        top <<= 1;
        bits--;
    }
    return OUT + 1;
}

// returns positive _value of *this
integer integer::abs() const{
    integer out = *this;
    out._sign = false;
    return out;
}

// fills an integer with 1s
void integer::fill(const uint64_t & b){
    _value = REP(b / BITS, NEG1);
    if (b % BITS){
        _value.push_front((1 << (b % BITS)) - 1);
    }
}

// get bit, where 0 is the lsb and bits() - 1 is the msb
bool integer::operator[](const unsigned int & b) const{
    if (b >= bits()){ // if given index is larger than bits in this _value, return 0
        return 0;
    }
    return (_value[_value.size() - (b / BITS) - 1] >> (b % BITS)) & 1;
}

// Output value as a string from base 2 to 16, or base 256
std::string integer::str(const uint16_t & base, const unsigned int & length) const{
    std::string out = "";
    if (base == 256){
        if (_value.empty()){
            out = std::string(1, 0);
        }
        for(REP_SIZE_T x = 0; x < _value.size(); x++){
            out += std::string(1, _value[x]);
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
        if ((base < 2) || (base > 16)){                     // if base outside of 2 <= base <= 16
            throw std::runtime_error("Error: Bad base: " + integer(base).str());
        }

        integer rhs = abs();                                // use absolute value to make sure index stays small

        if (*this == 0){
            out = "0";
        }
        else{
            std::pair <integer, integer> qr;
            do{
                qr = dm(rhs, base);
                out = B16[qr.second] + out;
                rhs = qr.first;
            } while (rhs);
        }

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

// Bitwise Operators
integer operator&(const bool & lhs, const integer & rhs){
    return integer(lhs) & rhs;
}

integer operator&(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) & rhs;
}

integer operator&(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) & rhs;
}

integer operator&(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) & rhs;
}

integer operator&(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) & rhs;
}

integer operator&(const int8_t & lhs, const integer & rhs){
    return integer(lhs) & rhs;
}

integer operator&(const int16_t & lhs, const integer & rhs){
    return integer(lhs) & rhs;
}

integer operator&(const int32_t & lhs, const integer & rhs){
    return integer(lhs) & rhs;
}

integer operator&(const int64_t & lhs, const integer & rhs){
    return integer(lhs) & rhs;
}

bool operator&=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) & rhs));
}

uint8_t operator&=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) & rhs));
}

uint16_t operator&=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) & rhs));
}

uint32_t operator&=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) & rhs));
}

uint64_t operator&=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) & rhs));
}

int8_t operator&=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) & rhs));
}

int16_t operator&=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) & rhs));
}

int32_t operator&=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) & rhs));
}

int64_t operator&=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) & rhs));
}

integer operator|(const bool & lhs, const integer & rhs){
    return integer(lhs) | rhs;
}

integer operator|(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) | rhs;
}

integer operator|(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) | rhs;
}

integer operator|(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) | rhs;
}

integer operator|(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) | rhs;
}

integer operator|(const int8_t & lhs, const integer & rhs){
    return integer(lhs) | rhs;
}

integer operator|(const int16_t & lhs, const integer & rhs){
    return integer(lhs) | rhs;
}

integer operator|(const int32_t & lhs, const integer & rhs){
    return integer(lhs) | rhs;
}

integer operator|(const int64_t & lhs, const integer & rhs){
    return integer(lhs) | rhs;
}

bool operator|=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) | rhs));
}

uint8_t operator|=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) | rhs));
}

uint16_t operator|=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) | rhs));
}

uint32_t operator|=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) | rhs));
}

uint64_t operator|=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) | rhs));
}

int8_t operator|=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) | rhs));
}

int16_t operator|=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) | rhs));
}

int32_t operator|=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) | rhs));
}

int64_t operator|=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) | rhs));
}

integer operator^(const bool & lhs, const integer & rhs){
    return integer(lhs) ^ rhs;
}

integer operator^(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) ^ rhs;
}

integer operator^(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) ^ rhs;
}

integer operator^(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) ^ rhs;
}

integer operator^(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) ^ rhs;
}

integer operator^(const int8_t & lhs, const integer & rhs){
    return integer(lhs) ^ rhs;
}

integer operator^(const int16_t & lhs, const integer & rhs){
    return integer(lhs) ^ rhs;
}

integer operator^(const int32_t & lhs, const integer & rhs){
    return integer(lhs) ^ rhs;
}

integer operator^(const int64_t & lhs, const integer & rhs){
    return integer(lhs) ^ rhs;
}

bool operator^=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) ^ rhs));
}

uint8_t operator^=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) ^ rhs));
}

uint16_t operator^=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) ^ rhs));
}

uint32_t operator^=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) ^ rhs));
}

uint64_t operator^=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) ^ rhs));
}

int8_t operator^=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) ^ rhs));
}

int16_t operator^=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) ^ rhs));
}

int32_t operator^=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) ^ rhs));
}

int64_t operator^=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) ^ rhs));
}

// Bitshift operators
integer operator<<(const bool & lhs, const integer & rhs){
    return integer(lhs) << rhs;
}

integer operator<<(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) << rhs;
}

integer operator<<(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) << rhs;
}

integer operator<<(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) << rhs;
}

integer operator<<(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) << rhs;
}

integer operator<<(const int8_t & lhs, const integer & rhs){
    return integer(lhs) << rhs;
}

integer operator<<(const int16_t & lhs, const integer & rhs){
    return integer(lhs) << rhs;
}

integer operator<<(const int32_t & lhs, const integer & rhs){
    return integer(lhs) << rhs;
}

integer operator<<(const int64_t & lhs, const integer & rhs){
    return integer(lhs) << rhs;
}

bool operator<<=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) << rhs));
}

uint8_t operator<<=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) << rhs));
}

uint16_t operator<<=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) << rhs));
}

uint32_t operator<<=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) << rhs));
}

uint64_t operator<<=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) << rhs));
}

int8_t operator<<=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) << rhs));
}

int16_t operator<<=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) << rhs));
}

int32_t operator<<=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) << rhs));
}

int64_t operator<<=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) << rhs));
}

integer operator>>(const bool & lhs, const integer & rhs){
    return integer(lhs) >> rhs;
}

integer operator>>(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) >> rhs;
}

integer operator>>(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) >> rhs;
}

integer operator>>(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) >> rhs;
}

integer operator>>(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) >> rhs;
}

integer operator>>(const int8_t & lhs, const integer & rhs){
    return integer(lhs) >> rhs;
}

integer operator>>(const int16_t & lhs, const integer & rhs){
    return integer(lhs) >> rhs;
}

integer operator>>(const int32_t & lhs, const integer & rhs){
    return integer(lhs) >> rhs;
}

integer operator>>(const int64_t & lhs, const integer & rhs){
    return integer(lhs) >> rhs;
}

bool operator>>=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) >> rhs));
}

uint8_t operator>>=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) >> rhs));
}

uint16_t operator>>=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) >> rhs));
}

uint32_t operator>>=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) >> rhs));
}

uint64_t operator>>=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) >> rhs));
}

int8_t operator>>=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) >> rhs));
}

int16_t operator>>=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) >> rhs));
}

int32_t operator>>=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) >> rhs));
}

int64_t operator>>=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) >> rhs));
}

// Comparison Operators
bool operator==(bool & lhs, const integer & rhs){
    return rhs == lhs;
}

bool operator==(uint8_t & lhs, const integer & rhs){
    return rhs == lhs;
}

bool operator==(uint16_t & lhs, const integer & rhs){
    return rhs == lhs;
}

bool operator==(uint32_t & lhs, const integer & rhs){
    return rhs == lhs;
}

bool operator==(uint64_t & lhs, const integer & rhs){
    return rhs == lhs;
}

bool operator==(int8_t & lhs, const integer & rhs){
    return rhs == lhs;
}

bool operator==(int16_t & lhs, const integer & rhs){
    return rhs == lhs;
}

bool operator==(int32_t & lhs, const integer & rhs){
    return rhs == lhs;
}

bool operator==(int64_t & lhs, const integer & rhs){
    return rhs == lhs;
}

bool operator!=(bool & lhs, const integer & rhs){
    return rhs != lhs;
}

bool operator!=(uint8_t & lhs, const integer & rhs){
    return rhs != lhs;
}

bool operator!=(uint16_t & lhs, const integer & rhs){
    return rhs != lhs;
}

bool operator!=(uint32_t & lhs, const integer & rhs){
    return rhs != lhs;
}

bool operator!=(uint64_t & lhs, const integer & rhs){
    return rhs != lhs;
}

bool operator!=(int8_t & lhs, const integer & rhs){
    return rhs != lhs;
}

bool operator!=(int16_t & lhs, const integer & rhs){
    return rhs != lhs;
}

bool operator!=(int32_t & lhs, const integer & rhs){
    return rhs != lhs;
}

bool operator!=(int64_t & lhs, const integer & rhs){
    return rhs != lhs;
}

bool operator>(const bool & lhs, const integer & rhs){
    return rhs < lhs;
}

bool operator>(const uint8_t & lhs, const integer & rhs){
    return rhs < lhs;
}

bool operator>(const uint16_t & lhs, const integer & rhs){
    return rhs < lhs;
}

bool operator>(const uint32_t & lhs, const integer & rhs){
    return rhs < lhs;
}

bool operator>(const uint64_t & lhs, const integer & rhs){
    return rhs < lhs;
}

bool operator>(const int8_t & lhs, const integer & rhs){
    return rhs < lhs;
}

bool operator>(const int16_t & lhs, const integer & rhs){
    return rhs < lhs;
}

bool operator>(const int32_t & lhs, const integer & rhs){
    return rhs < lhs;
}

bool operator>(const int64_t & lhs, const integer & rhs){
    return rhs < lhs;
}

bool operator>=(bool & lhs, const integer & rhs){
    return rhs <= lhs;
}

bool operator>=(uint8_t & lhs, const integer & rhs){
    return rhs <= lhs;
}

bool operator>=(uint16_t & lhs, const integer & rhs){
    return rhs <= lhs;
}

bool operator>=(uint32_t & lhs, const integer & rhs){
    return rhs <= lhs;
}

bool operator>=(uint64_t & lhs, const integer & rhs){
    return rhs <= lhs;
}

bool operator>=(int8_t & lhs, const integer & rhs){
    return rhs <= lhs;
}

bool operator>=(int16_t & lhs, const integer & rhs){
    return rhs <= lhs;
}

bool operator>=(int32_t & lhs, const integer & rhs){
    return rhs <= lhs;
}

bool operator>=(int64_t & lhs, const integer & rhs){
    return rhs <= lhs;
}

bool operator<(const bool & lhs, const integer & rhs){
    return rhs > lhs;
}

bool operator<(const uint8_t & lhs, const integer & rhs){
    return rhs > lhs;
}

bool operator<(const uint16_t & lhs, const integer & rhs){
    return rhs > lhs;
}

bool operator<(const uint32_t & lhs, const integer & rhs){
    return rhs > lhs;
}

bool operator<(const uint64_t & lhs, const integer & rhs){
    return rhs > lhs;
}

bool operator<(const int8_t & lhs, const integer & rhs){
    return rhs > lhs;
}

bool operator<(const int16_t & lhs, const integer & rhs){
    return rhs > lhs;
}

bool operator<(const int32_t & lhs, const integer & rhs){
    return rhs > lhs;
}

bool operator<(const int64_t & lhs, const integer & rhs){
    return rhs > lhs;
}

bool operator<=(bool & lhs, const integer & rhs){
    return rhs >= lhs;
}

bool operator<=(uint8_t & lhs, const integer & rhs){
    return rhs >= lhs;
}

bool operator<=(uint16_t & lhs, const integer & rhs){
    return rhs >= lhs;
}

bool operator<=(uint32_t & lhs, const integer & rhs){
    return rhs >= lhs;
}

bool operator<=(uint64_t & lhs, const integer & rhs){
    return rhs >= lhs;
}

bool operator<=(int8_t & lhs, const integer & rhs){
    return rhs >= lhs;
}

bool operator<=(int16_t & lhs, const integer & rhs){
    return rhs >= lhs;
}

bool operator<=(int32_t & lhs, const integer & rhs){
    return rhs >= lhs;
}

bool operator<=(int64_t & lhs, const integer & rhs){
    return rhs >= lhs;
}

// Arithmetic Operators
integer operator+(const bool & lhs, const integer & rhs){
    return integer(lhs) + rhs;
}

integer operator+(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) + rhs;
}

integer operator+(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) + rhs;
}

integer operator+(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) + rhs;
}

integer operator+(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) + rhs;
}

integer operator+(const int8_t & lhs, const integer & rhs){
    return integer(lhs) + rhs;
}

integer operator+(const int16_t & lhs, const integer & rhs){
    return integer(lhs) + rhs;
}

integer operator+(const int32_t & lhs, const integer & rhs){
    return integer(lhs) + rhs;
}

integer operator+(const int64_t & lhs, const integer & rhs){
    return integer(lhs) + rhs;
}

bool operator+=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) + rhs));
}

uint8_t operator+=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) + rhs));
}

uint16_t operator+=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) + rhs));
}

uint32_t operator+=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) + rhs));
}

uint64_t operator+=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) + rhs));
}

int8_t operator+=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) + rhs));
}

int16_t operator+=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) + rhs));
}

int32_t operator+=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) + rhs));
}

int64_t operator+=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) + rhs));
}

integer operator-(const bool & lhs, const integer & rhs){
    return integer(lhs) - rhs;
}

integer operator-(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) - rhs;
}

integer operator-(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) - rhs;
}

integer operator-(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) - rhs;
}

integer operator-(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) - rhs;
}

integer operator-(const int8_t & lhs, const integer & rhs){
    return integer(lhs) - rhs;
}

integer operator-(const int16_t & lhs, const integer & rhs){
    return integer(lhs) - rhs;
}

integer operator-(const int32_t & lhs, const integer & rhs){
    return integer(lhs) - rhs;
}

integer operator-(const int64_t & lhs, const integer & rhs){
    return integer(lhs) - rhs;
}

bool operator-=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) - rhs));
}

uint8_t operator-=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) - rhs));
}

uint16_t operator-=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) - rhs));
}

uint32_t operator-=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) - rhs));
}

uint64_t operator-=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) - rhs));
}

int8_t operator-=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) - rhs));
}

int16_t operator-=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) - rhs));
}

int32_t operator-=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) - rhs));
}

int64_t operator-=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) - rhs));
}

integer operator*(const bool & lhs, const integer & rhs){
    return integer(lhs) * rhs;
}

integer operator*(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) * rhs;
}

integer operator*(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) * rhs;
}

integer operator*(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) * rhs;
}

integer operator*(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) * rhs;
}

integer operator*(const int8_t & lhs, const integer & rhs){
    return integer(lhs) * rhs;
}

integer operator*(const int16_t & lhs, const integer & rhs){
    return integer(lhs) * rhs;
}

integer operator*(const int32_t & lhs, const integer & rhs){
    return integer(lhs) * rhs;
}

integer operator*(const int64_t & lhs, const integer & rhs){
    return integer(lhs) * rhs;
}

bool operator*=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) * rhs));
}

uint8_t operator*=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) * rhs));
}

uint16_t operator*=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) * rhs));
}

uint32_t operator*=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) * rhs));
}

uint64_t operator*=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) * rhs));
}

int8_t operator*=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) * rhs));
}

int16_t operator*=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) * rhs));
}

int32_t operator*=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) * rhs));
}

int64_t operator*=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) * rhs));
}

integer operator/(const bool & lhs, const integer & rhs){
    return integer(lhs) / rhs;
}

integer operator/(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) / rhs;
}

integer operator/(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) / rhs;
}

integer operator/(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) / rhs;
}

integer operator/(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) / rhs;
}

integer operator/(const int8_t & lhs, const integer & rhs){
    return integer(lhs) / rhs;
}

integer operator/(const int16_t & lhs, const integer & rhs){
    return integer(lhs) / rhs;
}

integer operator/(const int32_t & lhs, const integer & rhs){
    return integer(lhs) / rhs;
}

integer operator/(const int64_t & lhs, const integer & rhs){
    return integer(lhs) / rhs;
}

bool operator/=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) / rhs));
}

uint8_t operator/=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) / rhs));
}

uint16_t operator/=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) / rhs));
}

uint32_t operator/=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) / rhs));
}

uint64_t operator/=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) / rhs));
}

int8_t operator/=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) / rhs));
}

int16_t operator/=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) / rhs));
}

int32_t operator/=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) / rhs));
}

int64_t operator/=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) / rhs));
}

integer operator%(const bool & lhs, const integer & rhs){
    return integer(lhs) % rhs;
}

integer operator%(const uint8_t & lhs, const integer & rhs){
    return integer(lhs) % rhs;
}

integer operator%(const uint16_t & lhs, const integer & rhs){
    return integer(lhs) % rhs;
}

integer operator%(const uint32_t & lhs, const integer & rhs){
    return integer(lhs) % rhs;
}

integer operator%(const uint64_t & lhs, const integer & rhs){
    return integer(lhs) % rhs;
}

integer operator%(const int8_t & lhs, const integer & rhs){
    return integer(lhs) % rhs;
}

integer operator%(const int16_t & lhs, const integer & rhs){
    return integer(lhs) % rhs;
}

integer operator%(const int32_t & lhs, const integer & rhs){
    return integer(lhs) % rhs;
}

integer operator%(const int64_t & lhs, const integer & rhs){
    return integer(lhs) % rhs;
}

bool operator%=(bool & lhs, const integer & rhs){
    return (lhs = static_cast <bool> (integer(lhs) % rhs));
}

uint8_t operator%=(uint8_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint8_t> (integer(lhs) % rhs));
}

uint16_t operator%=(uint16_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint16_t> (integer(lhs) % rhs));
}

uint32_t operator%=(uint32_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint32_t> (integer(lhs) % rhs));
}

uint64_t operator%=(uint64_t & lhs, const integer & rhs){
    return (lhs = static_cast <uint64_t> (integer(lhs) % rhs));
}

int8_t operator%=(int8_t & lhs, const integer & rhs){
    return (lhs = static_cast <int8_t> (integer(lhs) % rhs));
}

int16_t operator%=(int16_t & lhs, const integer & rhs){
    return (lhs = static_cast <int16_t> (integer(lhs) % rhs));
}

int32_t operator%=(int32_t & lhs, const integer & rhs){
    return (lhs = static_cast <int32_t> (integer(lhs) % rhs));
}

int64_t operator%=(int64_t & lhs, const integer & rhs){
    return (lhs = static_cast <int64_t> (integer(lhs) % rhs));
}

// IO integer::operators
std::ostream & operator<<(std::ostream & stream, const integer & rhs){
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
std::string makebin(const integer & value, const unsigned int & size){
    // Changes a _value into its binary string
    return value.str(2, size);
}

std::string makehex(const integer & value, const unsigned int & size){
    // Changes a _value into its hexadecimal string
    return value.str(16, size);
}

std::string makeascii(const integer & value, const unsigned int & size){
    // Changes a _value into ASCII
    return value.str(256, size);
}

integer abs(const integer & value){
    return value.abs();
}
