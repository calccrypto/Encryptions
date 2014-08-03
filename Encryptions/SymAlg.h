#ifndef __SYMALG__
#define __SYMALG__

#include <iostream>
#include <memory>
#include <stdexcept>

class SymAlg{
    protected:
        bool keyset;

    public:
        typedef std::shared_ptr<SymAlg> Ptr;

        SymAlg();
        virtual ~SymAlg();
        virtual std::string encrypt(const std::string & DATA) = 0;
        virtual std::string decrypt(const std::string & DATA) = 0;
        virtual unsigned int blocksize() const = 0; // blocksize in bits
};
#endif
