// Cipher Block Chaining

#include "includes.h"
#include "integer.h"
#include "SymAlg.h"

#ifndef __CBC__
#define __CBC__
class CBC{
  private:
    SymAlg * algo;
    std::string const_IV;
    uint8_t blocksize;

  public:
    CBC(SymAlg * instance, std::string iv = "");
    std::string encrypt(std::string data);
    std::string decrypt(std::string data);
};
#endif
