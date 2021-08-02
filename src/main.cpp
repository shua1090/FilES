#include "FES.hpp"

#include <iostream>

//
//int main(){
//    crypto::OTP::saveNewKey((unsigned long long) (8LL * crypto::DataSizes::MEBIBYTE), "KEY");
//    crypto::OTP otp("KEY");
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    otp.encrypt("plain1.png", "encrypted.png");
//    otp.decrypt("encrypted.png", "recovered.png");
//
//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << duration.count() << " microseconds" << std::endl;
//}

/// Example AES Code:
/*
    using namespace crypto::io;

    auto start = std::chrono::high_resolution_clock::now();

    auto keyworker = crypto::AESWorker::loadKeyFile("KeyData.key");

    keyworker.encryptToFile("plain1.png", "encrypted.png");
    keyworker.decryptToFile("encrypted.png", "recovered.png");

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " microseconds" << std::endl;
*/