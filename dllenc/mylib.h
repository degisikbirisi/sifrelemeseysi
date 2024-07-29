// mylib.h
#ifndef MYLIB_H
#define MYLIB_H

#include <string>

extern "C" {
    __declspec(dllexport) std::string base64_encode(const std::string& in);
    __declspec(dllexport) std::string rot13(const std::string& input);
    __declspec(dllexport) std::string rot47(const std::string& input);
    __declspec(dllexport) std::string toHex(const std::string& input);
    __declspec(dllexport) std::string complexEncoding(const std::string& input);
}

#endif // MYLIB_H
