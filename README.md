# FilES

Ransomware attacks are increasing daily with most attackers
holding data ransom by encrypting it and threatening to sell/publish it.
Data can easily be stolen - why not encrypt it so that any stolen data is
useless for attackers? FilES - or File Encryption Software (A play on "AES")
provides such functionality, providing access to a multitude of cryptographic
algorithms for keeping your data private and secure.

## Goal
Provide a GUI tool to encrypt files with AES-256, One-Time Pads,
and RSA while also providing a section for finding the hashes of files.

## Progress

AES encryption and Key/IV saving has been completed, actual File
Interface and GUI still in progress

## Build

To build this library, simply clone the respository. Then, setup
vcpkg in the local directory according to vcpkg instructions for your
OS. 
After that, install the dependencies in .vcpkg_deps.txt either
separately or altogether with the command:

```bash
./vcpkg/vcpkg install "@.vcpkg_deps.txt"
```
Follow any instructions vcpkg gives you to succesfully build these libs.
Lastly, simply build the library as you would any cmake project, minding the
Vcpkg cmake command line argument (once again in the tutorial).