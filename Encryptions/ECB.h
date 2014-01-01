// Electronic Codebook

#include "../common/includes.h"
#include "SymAlg.h"

#ifndef __ECB__
#define __ECB__
class ECB{
  private:
    SymAlg * algo;
    uint8_t blocksize;

  public:
    ECB(SymAlg * instance, const std::string & iv = "");
    std::string encrypt(const std::string & data);
    std::string decrypt(const std::string & data);
};
#endif
