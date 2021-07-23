#include <utility>

#include<cstdio>
#include "../crypto.hpp"

namespace crypto::io {
    /// File Writer Definitions:
    FileWriter::FileWriter(const std::string &path) {
        outStream = std::ofstream(path, std::ios::out | std::ios::binary | std::ios::app);
    }
    FileWriter::~FileWriter() { outStream.close(); }
    void FileWriter::write(std::vector<byte> data) {
        outStream.write(reinterpret_cast<const char *>(&data[0]), data.size());
    }

    /// File Reader Definitions:
    FileReader::FileReader(const std::string &path) {
        inStream = std::ifstream(path, std::ios::in | std::ios::binary);
        inStream.seekg(0, std::ifstream::end);
        length = inStream.tellg();
        inStream.seekg(0, std::ifstream::beg);
    }
    FileReader::~FileReader() { inStream.close(); }
    std::vector<byte> FileReader::readNextNBytes(int n) {
        if (inStream.tellg() == -1 || inStream.tellg() == length) return std::vector<byte>(0);
        std::vector<byte> dat(n);
        inStream.read(reinterpret_cast<char *>(&dat[0]), (long) dat.size());
        unsigned long size;
        if (inStream.tellg() == -1 || inStream.tellg() == length){
            size = length % n;
        } else size = n;
//        std::cout << "Size: " << size << "-" << n << std::endl;
//        std::cout << "A: " << a << " - B: " << b << std::endl;
//        std::cout << "Predict A" << a + 128 << std::endl;
        dat.resize(size);
        return dat;
    }

    /// KeyReader/Writer
    CryptoPP::SecByteBlock KeyWorker::readKey(const std::string& fileName) {
        FileReader fr(fileName);
        auto temp = fr.readNextNBytes(32);
        CryptoPP::SecByteBlock key(&temp[0], 32);;
        return key;
    }
    CryptoPP::SecByteBlock KeyWorker::readIV(const std::string& fileName) {
        FileReader fr(fileName);
        fr.inStream.seekg(32);
        CryptoPP::SecByteBlock iv(&fr.readNextNBytes(16)[0], 16);
        return iv;
    }
    void KeyWorker::writeKey(const std::string& fileName, CryptoPP::SecByteBlock key) {
        FileWriter fw(fileName);
        std::vector <byte> keyVec;
        keyVec.insert(keyVec.end(), std::begin(key), std::end(key));
        fw.write(keyVec);
    }
    void KeyWorker::writeIV(const std::string &fileName, CryptoPP::SecByteBlock iv) {
        FileWriter fw(fileName);
        fw.outStream.seekp(32);
        std::vector <byte> keyVec;
        keyVec.insert(keyVec.end(), std::begin(iv), std::end(iv));
        fw.write(keyVec);
    }
    void KeyWorker::writeKeyWithIV(const std::string &fileName, const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) {
        std::remove(fileName.c_str());
        writeKey(fileName, key);
        writeIV(fileName, iv);
    }

    /// FileWorker
    std::vector<byte> FileWorker::read(int recommendedSize) {
        int n;
        if (recommendedSize > 0) n = recommendedSize;
        else if (FileReader::length > 64000000) n = 64000000;
        else if (FileReader::length > 32000000) n = 32000000;
        else if (FileReader::length > 16000000) n = 16000000;
        else if (FileReader::length > 4000000) n = 4000000;
        else if (FileReader::length > 2000000) n = 2000000;
        else if (FileReader::length > 1000) n = 1000;
        else n = 128;
        return FileReader::readNextNBytes(n);
    }
}