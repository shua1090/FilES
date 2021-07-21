#ifndef FILES_CRYPTO_HPP
#define FILES_CRYPTO_HPP
#include <iostream>
#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

#include <iostream>
#include <fstream>
#include <utility>


typedef unsigned char byte;
namespace crypto{
    void hash(byte *input, unsigned long sizeOfInput, byte *result);
    void hash(std::string str, byte* result);
    std::string toHex(byte * input, int size);
    std::string toHex(std::vector<byte> vec);
    byte *hash(std::string str);

    inline std::vector<byte> pad(std::vector<byte> vec, long padNum){
        if (padNum == 0) return vec;
        vec[127] = padNum;
        return vec;
    }
    inline std::vector<byte> unpad(std::vector<byte> vec){
        if (vec.empty()) return vec;
        int padNum = vec[127];
        if (padNum == 0) return vec;

        for (int i = 126; i > padNum;i--){
            if (vec[i] != 0) {
                return vec;
            }
        }
        std::vector<byte> unpaddedArr;
        unpaddedArr.resize( padNum);

        for (int i = 0; i < padNum; i++){
            unpaddedArr[i] = vec[i];
        }
        return unpaddedArr;
    }

    namespace io{
        class FileIOManager{};
        class FileWriter : FileIOManager {
        private:
            std::ofstream outStream;
            explicit FileWriter(const std::string& path);
             ~FileWriter();
            void close(){this->~FileWriter();}
            void write(std::vector<byte> data);
            friend class KeyWorker;
            friend class FileWorker;
        };
        class FileReader : FileIOManager {
        private:
            long length;
            std::ifstream inStream;
            explicit FileReader(const std::string& path);
             ~FileReader();
             void close(){this->~FileReader();}
            std::vector<byte> readNextNBytes(int n);
             friend class KeyWorker;
             friend class FileWorker;
        };

        class KeyWorker{
        public:
            static CryptoPP::SecByteBlock readKey(const std::string& fileName);
            static CryptoPP::SecByteBlock readIV(const std::string& fileName);
            static void writeKeyWithIV(const std::string& fileName, const CryptoPP::SecByteBlock& key,
                                       const CryptoPP::SecByteBlock& iv);
            static void writeKey(const std::string& fileName, CryptoPP::SecByteBlock key);
            static void writeIV(const std::string &fileName, CryptoPP::SecByteBlock iv);
        };
        class FileWorker : FileWriter, FileReader{
        public:
            explicit FileWorker(const std::string &path) : FileReader(path), FileWriter(path){};
            void writeData(std::vector<byte> data){ FileWriter::write(std::move(data));}
            std::vector<byte> read(int n, bool doPad = false);
        };
    }

    class AES{
    private:
        CryptoPP::SecByteBlock key;
        CryptoPP::SecByteBlock iv; // Random
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encMachine;
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decMachine;
    public:
        AES(const CryptoPP::SecByteBlock& inputKey, const CryptoPP::SecByteBlock& inputIV);
        static CryptoPP::SecByteBlock getSecureIV();
        std::vector<byte> encrypt(std::vector<byte> plain);
        std::vector<byte> decrypt(std::vector<byte> ciphertext);
    };

}

#endif //FILES_CRYPTO_HPP
