// Cipher Block Chaining
#ifndef __CBC__
#define __CBC__

#include "../common/includes.h"
#include "../common/integer.h"
#include "SymAlg.h"

class CBC{
  private:
    SymAlg * algo;
    std::string const_IV;
    uint8_t blocksize;

  public:
    CBC(SymAlg * instance, const std::string & iv = "");
    std::string encrypt(const std::string & data);
    std::string decrypt(const std::string & data);
};
#endif
