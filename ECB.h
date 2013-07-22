// Electronic Codebook

#include "includes.h"
#include "SymAlg.h"

#ifndef __ECB__
#define __ECB__
class ECB{
  private:
    SymAlg * algo;
    uint8_t blocksize;

  public:
    ECB(SymAlg * instance, std::string iv = "");
    std::string encrypt(std::string data);
    std::string decrypt(std::string data);
};
#endif
