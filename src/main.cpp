#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>

#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>

#include "crypto.hpp"

#include <iostream>
#include <cryptopp/modes.h>
#include <vector>

#include<SFML/Window.hpp>
#include<SFML/Window/Mouse.hpp>

int main(){
    using namespace crypto::io;

    auto start = std::chrono::high_resolution_clock::now();

    auto keyworker = crypto::AESWorker::loadKeyFile("KeyData.key");

    keyworker.encryptToFile("plain1.png", "encrypted.png");
    keyworker.decryptToFile("encrypted.png", "recovered.png");

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " microseconds" << std::endl;
}