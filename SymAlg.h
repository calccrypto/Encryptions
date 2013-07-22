#include <iostream>

#ifndef __SYMALG__
#define __SYMALG__
class SymAlg{
    protected:
        bool keyset;

    public:
        virtual std::string encrypt(std::string DATA) = 0;
        virtual std::string decrypt(std::string DATA) = 0;
        virtual unsigned int blocksize() = 0;
};
#endif
