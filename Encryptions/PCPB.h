// Propagating Cipher - Block Chaining

#include "../common/includes.h"
#include "../common/integer.h"
#include "SymAlg.h"

#ifndef __PCPB__
#define __PCPB__
class PCPB{
  private:
    SymAlg * algo;
    std::string const_IV;
    uint8_t blocksize;

  public:
    PCPB(SymAlg * instance, const std::string & iv = "");
    std::string encrypt(const std::string & data);
    std::string decrypt(const std::string & data);
};
#endif
