# Cryptography algorithms


Own implementation of algorithms frequently used in cryptography and tests of results and/or performance. All of the code is written in C++, some of the functions require the OpenSSL library. Compiles with make (requires g++ compiler).


## I. BBS
BBS is an algorithm for generating pseudo-random strings of bits. Program is capable of generating such an algorithm and tests it with own implementation of FIPS tests.


## II. RSA
Algorithm generates a set of keys - public and private for asymmetric encryption. Keys can be tested on user chosen ASCII-char messages.


## III. Diffie-Helman
Algorithm for generating session key that can be used in public channels.


## IV. Hash-functions tests
Tests of OpenSSL hash functions against different inputs.


## V. Block-Ciphers
Tests of OpenSSL block-ciphers algorithms against different inputs. Tests are also performed on files with intended errors so it is possible to compare outputs of different modes. Own implementation of CBC mode based on ECB.
