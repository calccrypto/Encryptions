# Encryptions Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall -c

debug: CXXFLAGS += -g
debug: all

all: SymAlg.o AES.o Blowfish.o Camellia.o CAST128.o CAST256.o CBC.o CFB.o CTR.o DES.o DESX.o ECB.o Encryptions.o GOST.o IDEA.o MISTY1.o OFB.o RC2.o RC4.o RC5.o RC6.o RC_PQ.o SAFERK64.o SEED.o Skipjack.o TDES.o TEA.o Twofish.o XTEA.o

.PHONY: clean

SymAlg.o: SymAlg.h SymAlg.cpp
	$(CXX) $(CXXFLAGS) SymAlg.cpp

AES.o: AES.cpp AES.h AES_Const.h ../common/cryptomath.h ../common/includes.h SymAlg.h
	$(CXX) $(CXXFLAGS) AES.cpp

Blowfish.o: Blowfish.cpp Blowfish.h Blowfish_Const.h SymAlg.h
	$(CXX) $(CXXFLAGS) Blowfish.cpp

Camellia.o: Camellia.cpp Camellia.h Camellia_Const.h ../common/integer.h ../common/cryptomath.h SymAlg.h
	$(CXX) $(CXXFLAGS) Camellia.cpp

CAST128.o: CAST128.cpp CAST128.h CAST128_Const.h ../common/cryptomath.h SymAlg.h
	$(CXX) $(CXXFLAGS) CAST128.cpp

CAST256.o: CAST256.cpp CAST256.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) CAST256.cpp

CBC.o: CBC.cpp CBC.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CXXFLAGS) CBC.cpp

CFB.o: CFB.cpp CFB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CXXFLAGS) CFB.cpp

CTR.o: CTR.cpp CTR.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CXXFLAGS) CTR.cpp

DES.o: DES.cpp DES.h DES_Const.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) DES.cpp

DESX.o: DESX.cpp DESX.h ../common/includes.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) DESX.cpp

ECB.o: ECB.cpp ECB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CXXFLAGS) ECB.cpp

Encryptions.o: Encryptions.cpp Encryptions.h ../common/includes.h ../common/cryptomath.h SymAlg.h AES.h Blowfish.h Camellia.h CAST128.h CAST256.h CBC.h CFB.h CTR.h DES.h DESX.h ECB.h GOST.h IDEA.h MISTY1.h OFB.h RC2.h RC4.h RC5.o RC6.h SAFERK64.h SEED.h Skipjack.h SymAlg.h TDES.h TEA.h XTEA.h
	$(CXX) $(CXXFLAGS) Encryptions.cpp

GOST.o: GOST.cpp GOST.h GOST_Const.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CXXFLAGS) GOST.cpp

IDEA.o: IDEA.cpp IDEA.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CXXFLAGS) IDEA.cpp

MISTY1.o: MISTY1.cpp MISTY1.h MISTY1_Const.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) MISTY1.cpp

OFB.o: OFB.cpp OFB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CXXFLAGS) OFB.cpp

PCPB.h: PCPB.cpp PCPB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CXXFLAGS) PCPB.cpp

RC2.o: RC2.cpp RC2.h RC2_Const.h ../common/cryptomath.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) RC2.cpp

RC4.o: RC4.cpp RC4.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) RC4.cpp

RC5.o: RC5.cpp RC5.h ../common/cryptomath.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) RC5.cpp

RC6.o: RC6.cpp RC6.h ../common/cryptomath.h ../common/includes.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) RC6.cpp

RC_PQ.o: RC_PQ.cpp RC_PQ.h
	$(CXX) $(CXXFLAGS) RC_PQ.cpp

SAFERK64.o: SAFERK64.cpp SAFERK64.h SAFERK64_Const.h ../common/cryptomath.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) SAFERK64.cpp

SEED.o: SEED.cpp SEED.h SEED_Const.h ../common/cryptomath.h ../common/integer.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) SEED.cpp

Skipjack.o: Skipjack.cpp Skipjack.h Skipjack_Const.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) Skipjack.cpp

TDES.o: TDES.cpp TDES.h DES.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) TDES.cpp

TEA.o: TEA.cpp TEA.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) TEA.cpp

Twofish.o: Twofish.h Twofish.cpp SymAlg.h Twofish_Const.h
	$(CXX) $(CXXFLAGS) Twofish.cpp

XTEA.o: XTEA.cpp XTEA.h ./SymAlg.h
	$(CXX) $(CXXFLAGS) XTEA.cpp

clean:
	rm -f *.o
