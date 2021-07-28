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

    enum DataSizes{
        BYTE = 1,
        KIBIBYTE = 1024,
        MEBIBYTE = 1048576,
        GIBIBYTE = 1073741824,
    };

    namespace io{
        /// Backbones
        class FileIOManager{};
        class FileWriter : FileIOManager {
        private:
            std::ofstream outStream;
            explicit FileWriter(const std::string& path);
             ~FileWriter();
            void close(){this->~FileWriter();}
            void write(std::vector<byte> data);
            friend class AES_Key_Worker;
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
             friend class AES_Key_Worker;
             friend class FileWorker;
        };

        /// Implementations
        class AES_Key_Worker{
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
            std::vector<byte> read(int recommendedSize = -1);
            unsigned long long getSize(){return FileReader::length;}
        };
    }
    class AES{
    private:
        CryptoPP::SecByteBlock key;
        CryptoPP::SecByteBlock iv; // Random
        CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption encMachine;
        CryptoPP::OFB_Mode<CryptoPP::AES>::Decryption decMachine;
    public:
        AES(const CryptoPP::SecByteBlock& inputKey, const CryptoPP::SecByteBlock& inputIV);
        static CryptoPP::SecByteBlock getSecureIV();
        std::vector<byte> encrypt(std::vector<byte> plain);
        std::vector<byte> decrypt(std::vector<byte> ciphertext);
    };

    /// Highest Level Implementation of AES for File Usage
    class AESWorker : AES{
    public:
        AESWorker(const CryptoPP::SecByteBlock &inputKey, const CryptoPP::SecByteBlock &inputIv) : AES(inputKey, inputIv)
        {};
        static AESWorker loadKeyFile(const std::string& fileName);
        static void saveKeyFile(const std::string& fileName, const CryptoPP::SecByteBlock& inputKey, const CryptoPP::SecByteBlock& inputIV,
                                bool overwrite = true);

        void encryptToFile(const std::string& plainTextFileName, const std::string& ciphertextFileName, bool
        overwrite = true);
        void decryptToFile(const std::string& ciphertextFileName, const std::string& recoveredFileName, bool
        overwrite = true);
    };



    /// One Time Pad?
    class OTP{
    private:
        std::string pathToKey;

        static std::vector<byte> getRandomVectorMouse();
    public:
        /// Uses Mouse movements for random number

        OTP(const std::string& keyPath) : pathToKey(keyPath){};
        void deleteKey(){std::remove(pathToKey.c_str());};
        void encrypt(const std::string& plainTextPath, const std::string& encryptedTextPath);
        void decrypt(const std::string &encrypted_text_path, const std::string &recovered_text_path);

        static std::string saveNewKey(unsigned long long int amountOfBytes, std::string filePath);

    };
}

#endif //FILES_CRYPTO_HPP
