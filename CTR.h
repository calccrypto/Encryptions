// Counter

#include "includes.h"
#include "integer.h"
#include "SymAlg.h"

#ifndef __CTR__
#define __CTR__
class CTR{
  private:
    SymAlg * algo;
    std::string const_IV;
    uint8_t blocksize;

  public:
    CTR(SymAlg * instance, std::string iv = "");
    std::string encrypt(std::string data);
    std::string decrypt(std::string data);
};
#endif
