#include "crypto.hpp"

#include <cryptopp/osrng.h>
namespace crypto{
//    AES::AES(const CryptoPP::SecByteBlock& inputKey, const CryptoPP::SecByteBlock& inputIV) : key(inputKey), iv(inputIV){};
    AES::AES(const CryptoPP::SecByteBlock &inputKey, const CryptoPP::SecByteBlock &inputIV) {
        key = inputKey;
        iv = inputIV;
        encMachine.SetKeyWithIV(inputKey, sizeof inputKey, inputIV);
        decMachine.SetKeyWithIV(inputKey, sizeof inputKey, inputIV);
    }

    CryptoPP::SecByteBlock AES::getSecureIV() {
        CryptoPP::SecByteBlock newIV(128);
        CryptoPP::AutoSeededRandomPool prng;
        prng.GenerateBlock(newIV, newIV.size());
        return newIV;
    }

    std::vector<byte> AES::encrypt(std::vector<byte> plain) {
        std::vector<byte> cipher;

        cipher.resize(plain.size()+CryptoPP::AES::BLOCKSIZE);
        CryptoPP::ArraySink cs(&cipher[0], cipher.size());

        CryptoPP::ArraySource(plain.data(), plain.size(), true,
                    new CryptoPP::StreamTransformationFilter(encMachine, new CryptoPP::Redirector(cs),
                                                             CryptoPP::BlockPaddingSchemeDef::DEFAULT_PADDING));

        cipher.resize(cs.TotalPutLength());
        return cipher;
    }

    std::vector<byte> AES::decrypt(std::vector<byte> ciphertext) {
        std::vector<byte> recover;

        recover.resize(ciphertext.size());
        CryptoPP::ArraySink rs(&recover[0], recover.size());

        CryptoPP::ArraySource(ciphertext.data(), ciphertext.size(), true,
                    new CryptoPP::StreamTransformationFilter(decMachine, new CryptoPP::Redirector(rs),
                                                             CryptoPP::BlockPaddingSchemeDef::DEFAULT_PADDING));

        // Set recovered text length now that its known
        recover.resize(rs.TotalPutLength());

        return recover;
    }

}