#include "Security.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

std::string Security::encrypt(const std::string &data){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)data.c_str(), data.length(), hash);

    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
        

}