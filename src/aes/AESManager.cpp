#include "../FES.hpp"

namespace crypto{
    AESWorker AESWorker::loadKeyFile(const std::string& fileName) {
        CryptoPP::SecByteBlock key = crypto::io::AES_Key_Worker::readKey(fileName);
        CryptoPP::SecByteBlock iv = crypto::io::AES_Key_Worker::readIV(fileName);
        return AESWorker(key, iv);
    }

    void AESWorker::saveKeyFile(const std::string& fileName, const CryptoPP::SecByteBlock& inputKey, const CryptoPP::SecByteBlock& inputIV,
                                bool overwrite) {
        if (overwrite) std::remove(fileName.c_str());
        io::AES_Key_Worker::writeKey(fileName, inputKey);
        io::AES_Key_Worker::writeIV(fileName, inputIV);
    }

    void AESWorker::encryptToFile(const std::string& plainTextFileName, const std::string& ciphertextFileName, bool overwrite) {
        if (overwrite) std::remove(ciphertextFileName.c_str());

        io::FileWorker frplain(plainTextFileName);
        io::FileWorker fwcipher(ciphertextFileName);

        std::vector<byte> plainline;
        while (!(plainline = frplain.read()).empty()){
            std::vector<byte> cipherline = AES::encrypt(plainline);
            fwcipher.writeData(cipherline);
        }
        std::cout << "Encryption Done!" << std::endl;
    }

    void AESWorker::decryptToFile(const std::string& ciphertextFileName, const std::string& recoveredFileName, bool overwrite) {
        if (overwrite) std::remove(recoveredFileName.c_str());

        io::FileWorker frcipher(ciphertextFileName);
        io::FileWorker fwrecover(recoveredFileName);

        std::vector<byte> cipherline;
        while (!(cipherline = frcipher.read(-1)).empty()){
            std::vector<byte> recoverline = AES::decrypt(cipherline);
            fwrecover.writeData(recoverline);
        }
    }
}