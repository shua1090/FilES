#include "../FES.hpp"

#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <iostream>
#include <utility>

void crypto::hash(byte *input, unsigned long sizeOfInput, byte *result) {
    CryptoPP::SHA3_256 sha;
    sha.CalculateDigest(result, input, sizeOfInput);
}

void crypto::hash(std::string str, byte* result){
    byte strToArr[str.size()];
    for (int i = 0; i < str.size(); i++){
        strToArr[i] = str[i];
    }
    hash(strToArr, sizeof strToArr, result);
}

// Don't Forget to Delete!
byte* crypto::hash(std::string str){
    byte * result = new byte[32];
    hash(std::move(str), result);
    return result;
}

std::string crypto::toHex(byte * input, int size) {
    std::string output;

    CryptoPP::HexEncoder encoder;
    encoder.Put(input, size);
    encoder.MessageEnd();

    CryptoPP::word64 readyBytes = encoder.MaxRetrievable();
    if (readyBytes){
        output.resize(readyBytes);
        encoder.Get((byte*) &output[0], output.size());
    }
    return output;
}

std::string crypto::toHex(std::vector<byte> vec) {
    return toHex(&vec[0], vec.size());
}


