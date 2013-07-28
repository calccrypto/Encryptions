// Cipher Feedback

#include "../common/includes.h"
#include "../common/integer.h"
#include "SymAlg.h"

#ifndef __CFB__
#define __CFB__
class CFB{
  private:
    SymAlg * algo;
    std::string const_IV;
    uint8_t blocksize;

  public:
    CFB(SymAlg * instance, std::string iv = "");
    std::string encrypt(std::string data);
    std::string decrypt(std::string data);
};
#endif
