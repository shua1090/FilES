#include "crypto.hpp"



namespace crypto{
    FileWorker::FileWorker() {
    }

    void FileWorker::setWriting(const std::string& fileName){
        outStream = std::ofstream(fileName, std::ios::out|std::ios::binary);
    }
    void FileWorker::setReading(std::string fileName){
        inStream = std::ifstream(fileName, std::ios::in|std::ios::binary);
        inStream.seekg (0, std::ifstream::end);
        length = inStream.tellg();
        inStream.seekg (0, std::ifstream::beg);
    }

    std::vector<byte> FileWorker::readNextByte() {
        if (inStream.tellg() == -1 || inStream.tellg() == length) return std::vector<byte>(0);
        std::vector<byte> dat(128);
        inStream.read(reinterpret_cast<char *>(&dat[0]), 128);

        inStream.sync();
        return dat;
    }

    void FileWorker::write(std::vector<byte> data) {
        outStream.write(reinterpret_cast<const char *>(&data[0]), data.size());
    }

    FileWorker::~FileWorker() {
        inStream.close();
        outStream.close();
    }


}