#ifndef FILES_CRYPTO_HPP
#define FILES_CRYPTO_HPP
#include <iostream>
#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

#include <iostream>
#include <fstream>


typedef unsigned char byte;
namespace crypto{
    void hash(byte *input, unsigned long sizeOfInput, byte *result);
    void hash(std::string str, byte* result);
    std::string toHex(byte * input, int size);
    std::string toHex(std::vector<byte> vec);

    class FileWorker{
    private:
        std::ifstream inStream;
        std::ofstream outStream;

        int length;
    public:
        explicit FileWorker();
        ~FileWorker();
        std::vector<byte> readNextByte();
        void write(std::vector<byte> data);

        void setWriting(const std::string& fileName);

        void setReading(std::string fileName);
    };

    class KeyWorker : FileWorker{};
    class PlainReader : FileWorker{};
    class CipherWriter : FileWorker{};
    class TextWriter : FileWorker{};

    class AES{
    private:
        CryptoPP::SecByteBlock key;
        CryptoPP::SecByteBlock iv; // Random
        CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption encMachine;
        CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption decMachine;
    public:
        AES(const CryptoPP::SecByteBlock& inputKey, const CryptoPP::SecByteBlock& inputIV);
        static CryptoPP::SecByteBlock getSecureIV();
        std::vector<byte> encrypt(std::vector<byte> plain);
        std::vector<byte> decrypt(std::vector<byte> ciphertext);
    };
}

#endif //FILES_CRYPTO_HPP
