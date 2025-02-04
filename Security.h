#ifndef SECURITY_H
#define SECURITY_H

#include <string>

class Security {
    public:
        static std::string encrypt(const std::string &data);
};

#endif