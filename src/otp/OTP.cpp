#include "../FES.hpp"

#include <SFML/Window.hpp>

#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // _WIN32

void sleep(int milliseconds){
    #ifdef _WIN32
    Sleep(milliseconds);
    #else
    usleep(milliseconds * 1000);
    #endif // _WIN32
}

inline bool isTooClose(int x1, int y1, int x2, int y2){
    if (((x2 > x1 + 20) || (x2 < x1-20)) || ((y2 > y1 + 20) || (y2 < y1-20)))
        return false;
    return true;
}
inline std::vector<byte> xorData(std::vector<byte> data1, std::vector<byte> data2){
    std::vector<byte> resultData;
    resultData.reserve(data1.size());
    for (int i = 0; i < data1.size(); i++){
        resultData.push_back(data1[i] ^ data2[i]);
    }

    return resultData;
}
namespace crypto{

    std::vector<byte> OTP::getRandomVectorMouse() {
        std::vector<byte> randomVals;
        int x1 = 0;
        int y1 = 0;
        CryptoPP::AutoSeededRandomPool prng;
        byte rngHolder;
        while (randomVals.size() < 128){
            auto a = sf::Mouse::getPosition();

            prng.GenerateBlock(&rngHolder, 1);

            if (!isTooClose(x1, y1, a.x, a.y)){
                x1 = a.x;
                y1 = a.y;
                if (x1 == 0 && y1 != 0) randomVals.push_back((x1) % 255);
                else if (y1 == 0 && x1 != 0) randomVals.push_back((y1) % 255);
                else randomVals.push_back((x1 * y1) % 255);
                sleep (rngHolder % 50);
            } else {
                sleep(10);
            }
        }

        return randomVals;
    }

    std::string OTP::saveNewKey(unsigned long long amountOfBytes, std::string filePath) {
        using namespace io;

        std::remove(filePath.c_str());

        FileWorker fw(filePath);

        unsigned long long i = 0;

        CryptoPP::AutoSeededRandomPool prng;
        std::vector<byte> randomVals;
        std::vector<byte> totalVals(1024);

        while (i < amountOfBytes){

            if (i % (unsigned long long) ((int)(crypto::DataSizes::MEBIBYTE)) == 0){
                std::cout << "Move your mouse a bit (" << i << "/" << amountOfBytes  << " bytes collected)" <<
                std::endl;
                randomVals = getRandomVectorMouse();
                prng.IncorporateEntropy(&randomVals[0], randomVals.size());
            }

            if (i + totalVals.size() > amountOfBytes){
                totalVals.resize((i+totalVals.size() - amountOfBytes));
            }

            prng.GenerateBlock(&totalVals[0], totalVals.size());
            fw.writeData(totalVals);
            i += totalVals.size();
        }
        return filePath;
    }

    void OTP::encrypt(const std::string& plainTextPath, const std::string& encryptedTextPath) {
        using crypto::io::FileWorker;

        std::remove(encryptedTextPath.c_str());
        FileWorker plain_file(plainTextPath);
        FileWorker encrypt_file(encryptedTextPath);

        FileWorker key_file(this->pathToKey);
        if (plain_file.getSize() > key_file.getSize()){throw std::exception();}

        std::vector<byte> plainline;
        while (!(plainline = plain_file.read(KIBIBYTE)).empty()){

            std::vector<byte> keyline = key_file.read(KIBIBYTE);
            keyline.resize(plainline.size());

            std::vector<byte> cipherline = xorData(plainline, keyline);
            encrypt_file.writeData(cipherline);
        }
    }

    void OTP::decrypt(const std::string& encrypted_text_path, const std::string& recovered_text_path) {
        using crypto::io::FileWorker;

        std::remove(recovered_text_path.c_str());
        FileWorker encrypted_file(encrypted_text_path);
        FileWorker recovered_file(recovered_text_path);

        FileWorker key_file(this->pathToKey);
        if (encrypted_file.getSize() > key_file.getSize()){throw std::exception();}

        std::vector<byte> encrypted_line;
        while (!(encrypted_line = encrypted_file.read(KIBIBYTE)).empty()){

            std::vector<byte> keyline = key_file.read(KIBIBYTE);
            keyline.resize(encrypted_line.size());

            std::vector<byte> recovered_line = xorData(encrypted_line, keyline);
            recovered_file.writeData(recovered_line);
        }
    }

}