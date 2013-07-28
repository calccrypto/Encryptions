#include "./CFB.h"
CFB::CFB(SymAlg * instance, std::string iv)
  : algo(instance) {
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, '\x00');
    }
}

std::string CFB::encrypt(std::string data){
    data = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    while (data.size()){
        IV = unhexlify(makehex(integer(hexlify(algo ->encrypt(IV)), 16) ^ integer(hexlify(data.substr(0, blocksize)), 16), blocksize << 1));
        out += IV;
        data = data.substr(blocksize, data.size() - blocksize);
    }
    return out;
}

std::string CFB::decrypt(std::string data){
    std::string out = "";
    std::string IV = const_IV;
    while (data.size()){
        out += unhexlify(makehex(integer(hexlify(algo ->encrypt(IV)), 16) ^ integer(hexlify(data.substr(0, blocksize)), 16), blocksize << 1));
        IV = data.substr(0, blocksize);
        data = data.substr(blocksize, data.size() - blocksize);
    }
    return remove_padding(out);
}
