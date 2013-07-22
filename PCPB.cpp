#include "PCPB.h"

PCPB::PCPB(SymAlg * instance, std::string iv)
  : algo(instance) {
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, '\x00');
    }
  }

std::string PCPB::encrypt(std::string data){
    data = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    while (data.size()){
        std::string temp = data.substr(0, blocksize);
        out += algo ->encrypt(unhexlify(makehex(integer(hexlify(temp), 16) ^ integer(hexlify(IV), 16), blocksize << 1)));
        IV = unhexlify(makehex(integer(hexlify(out.substr(out.size() - blocksize, blocksize)), 16) ^ integer(hexlify(temp), 16), blocksize << 1));
        data = data.substr(blocksize, data.size() - blocksize);
    }
    return out;
}

std::string PCPB::decrypt(std::string data){
    std::string out = "";
    std::string IV = const_IV;
    while (data.size()){
        std::string temp = data.substr(0, blocksize);
        out += unhexlify(makehex(integer(hexlify(algo ->decrypt(temp)), 16) ^ integer(hexlify(IV), 16), blocksize << 1));
        IV = unhexlify(makehex(integer(hexlify(out.substr(out.size() - blocksize, blocksize)), 16) ^ integer(hexlify(temp), 16), blocksize << 1));
        data = data.substr(blocksize, data.size() - blocksize);
    }
    return remove_padding(out);
}
