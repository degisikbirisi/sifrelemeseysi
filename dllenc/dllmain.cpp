// dllmain.cpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <Windows.h>
#include "mylib.h"
#include "pch.h"

extern "C" {

    __declspec(dllexport) std::string base64_encode(const std::string& in) {
        const std::string base64_chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

        std::string out;
        int val = 0, valb = -6;
        for (unsigned char c : in) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                out.push_back(base64_chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6) out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (out.size() % 4) out.push_back('=');
        return out;
    }

    __declspec(dllexport) std::string rot13(const std::string& input) {
        std::string output = input;
        for (char& c : output) {
            if (c >= 'a' && c <= 'z') {
                c = 'a' + (c - 'a' + 13) % 26;
            }
            else if (c >= 'A' && c <= 'Z') {
                c = 'A' + (c - 'A' + 13) % 26;
            }
        }
        return output;
    }

    __declspec(dllexport) std::string rot47(const std::string& input) {
        std::string output = input;
        for (char& c : output) {
            if (c >= 33 && c <= 126) {
                c = 33 + (c - 33 + 47) % 94;
            }
        }
        return output;
    }

    __declspec(dllexport) std::string toHex(const std::string& input) {
        std::stringstream hexStream;
        for (char c : input) {
            hexStream << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)c;
        }
        return hexStream.str();
    }

    __declspec(dllexport) std::string complexEncoding(const std::string& input) {
        std::string output = input;

        for (int i = 0; i < 8; ++i) {
            output = base64_encode(output);
        }

        output = rot13(output);

        output = rot47(output);

        output = toHex(output);

        for (int i = 0; i < 3; ++i) {
            output = base64_encode(output);
        }

        for (int i = 0; i < 1; ++i) {
            output = toHex(output);
        }

        output = base64_encode(output);

        return output;
    }

}
