#include "./ECB.h"

ECB::ECB(SymAlg * instance, std::string iv)
: algo(instance){
    blocksize = algo -> blocksize() >> 3;
}

std::string ECB::encrypt(std::string data){
    data = pkcs5(data, blocksize);
    for(unsigned x = 0; x < data.size() / blocksize; x++){
        data = data.substr(0, blocksize * x) + algo -> encrypt(data.substr(blocksize * x, blocksize)) + data.substr(blocksize * x + blocksize, data.size() - blocksize * x + blocksize);
    }
    return data;
}

std::string ECB::decrypt(std::string data){
    for(unsigned int x = 0; x < data.size() / blocksize; x++){
        data = data.substr(0, blocksize * x) + algo -> decrypt(data.substr(blocksize * x, blocksize)) + data.substr(blocksize * x + blocksize, data.size() - blocksize * x + blocksize);
    }
    return remove_padding(data);
}
