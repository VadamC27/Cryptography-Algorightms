CXX = g++

CXXFLAGS = -std=c++11 -Wall 
LDFLAGS = -lssl -lcrypto

SOURCES = main.cpp pseudorandom-sequences-bbs/bbs.cpp pseudorandom-sequences-bbs/bbs_tests.cpp cryptography_utils.cpp rsa-algorithm/rsa.cpp dh-algorithm/dh.cpp hash-functions/hash_tests.cpp block-ciphers/block_ciphers.cpp block-ciphers/cbc_own.cpp

EXECUTABLE = program.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	
.PHONY: all
