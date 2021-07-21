#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>

#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>

#include "crypto.hpp"

#include <iostream>
#include <cryptopp/modes.h>
#include <vector>

int main(){
    using namespace crypto::io;

//    auto iv = crypto::AES::getSecureIV();
//    auto key = CryptoPP::SecByteBlock (crypto::hash("Password"), 32);
//    KeyWorker::writeKeyWithIV("KeyData.key", key, iv);
    auto loadIV = KeyWorker::readIV("KeyData.key");
    auto loadKey = KeyWorker::readKey("KeyData.key");



    FileWorker plaintext("plain.txt");
    std::remove("recovered.txt");
    FileWorker recovered("recovered.txt");
    FileWorker ciphertext("encrypted.enc");

    crypto::AES dase(loadKey, loadIV);

    std::vector<byte> chunk;
    while (true) {
        chunk = ciphertext.read(128);
        if (chunk.empty()) break;
        recovered.writeData(crypto::unpad(dase.decrypt(chunk)));
    }


}