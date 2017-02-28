#include "./PCPB.h"

PCPB::PCPB(SymAlg * instance, const std::string & iv)
  : algo(instance) {
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, 0);
    }
  }

std::string PCPB::encrypt(const std::string & data){
    std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    uint32_t x = 0;
    while (x < temp.size()){
        std::string block = temp.substr(x, blocksize);
        out += algo -> encrypt(unhexlify(makehex(integer(hexlify(block), 16) ^ integer(hexlify(IV), 16), blocksize << 1)));
        IV = unhexlify(makehex(integer(hexlify(out.substr(out.size() - blocksize, blocksize)), 16) ^ integer(hexlify(block), 16), blocksize << 1));
        x += blocksize;
    }
    return out;
}

std::string PCPB::decrypt(const std::string & data){
    std::string out = "";
    std::string IV = const_IV;
    uint32_t x = 0;
    while (x < data.size()){
        std::string block = data.substr(x, blocksize);
        out += unhexlify(makehex(integer(hexlify(algo -> decrypt(block)), 16) ^ integer(hexlify(IV), 16), blocksize << 1));
        IV = unhexlify(makehex(integer(hexlify(out.substr(out.size() - blocksize, blocksize)), 16) ^ integer(hexlify(block), 16), blocksize << 1));
        x += blocksize;
    }
    return remove_padding(out);
}
