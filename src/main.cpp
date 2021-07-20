#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>

#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>

#include "crypto.hpp"

#include <iostream>
#include <cryptopp/modes.h>
#include <vector>
//int main(){
//    using namespace CryptoPP;
//    using namespace crypto;
//    CryptoPP::SecByteBlock a = crypto::AES::getSecureIV();
//    byte result[32];
//    hash("password", result);
//
//    CryptoPP::SecByteBlock kye(result, sizeof(result));
//    crypto::AES ase(kye, a);
//    std::vector<byte> plain;
//
//    byte data[] = "Hello Adi. I am Computer. I will be your downfall. Enjoy life while you can!";
//
//    plain.insert( plain.end(), std::begin(data), std::end(data) );
//
//    std::cout << "Original Data: " << plain.data() << std::endl;
//
//    auto start = std::chrono::high_resolution_clock::now();
//    std::vector<byte> ciphertext = ase.encrypt(plain);
//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//
//    std::cout << "Encryption time: " << duration.count() << " ms" << std::endl;
//    std::cout << "Encrypted Data (128 bits): " << ciphertext.data() << std::endl;
//
//    start = std::chrono::high_resolution_clock::now();
//    std::vector<byte> recovery = ase.decrypt(ciphertext);
//    stop = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//
//    std::cout << "Decryption time: " << duration.count() << " ms" << std::endl;
//    std::cout << "Decrypted Data: " << recovery.data() << std::endl;
//}

int main(){
    crypto::FileWorker plainText;
    crypto::FileWorker cipherText;
    plainText.setReading("test.txt");
    cipherText.setWriting("cipher.txt");

    byte hashResult[32];
    crypto::hash("Password", hashResult);

    CryptoPP::SecByteBlock key(hashResult, sizeof hashResult);
    CryptoPP::SecByteBlock iv = crypto::AES::getSecureIV();

    crypto::AES ase(key, iv);
    while (true){
        std::vector<byte> plainTextBytes = plainText.readNextByte();
        if (plainTextBytes.empty()) break;
        auto temp = ase.encrypt(plainTextBytes);
        cipherText.write(temp);
        std::cout<< "Temp size: " << temp.size() << std::endl;
    }
    plainText.~FileWorker();
    cipherText.~FileWorker();

    crypto::FileWorker newCipherText;
    newCipherText.setReading("cipher.txt");

    while (true){
        std::vector<byte> plainBytesDaya = newCipherText.readNextByte();
        if (plainBytesDaya.empty() || plainBytesDaya.capacity() == 0) break;
        std::cout << "Before: " <<  crypto::toHex(plainBytesDaya) <<std::endl;
//        std::cout << ase.decrypt(plainBytesDaya).data() << std::endl;
        std::cout << ase.decrypt(plainBytesDaya).data() << std::endl;
    }
}