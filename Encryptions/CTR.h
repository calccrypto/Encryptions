// Counter
#ifndef __CTR__
#define __CTR__

#include "../common/includes.h"
#include "../common/integer.h"
#include "SymAlg.h"

class CTR{
  private:
    SymAlg * algo;
    std::string const_IV;
    uint8_t blocksize;

  public:
    CTR(SymAlg * instance, const std::string & iv = "");
    std::string encrypt(const std::string & data);
    std::string decrypt(const std::string & data);
};
#endif
