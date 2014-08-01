# Encryptions Makefile
CXX?=g++
LFLAGS=
CFLAGS=-std=c++11 -Wall -c

debug: CFLAGS += -g
debug: all

all: SymAlg.o AES.o Blowfish.o Camellia.o CAST128.o CAST256.o CBC.o CFB.o CTR.o DES.o DESX.o ECB.o Encryptions.o GOST.o IDEA.o MISTY1.o OFB.o RC2.o RC4.o RC5.o RC6.o RC_PQ.o SAFERK64.o SEED.o Skipjack.o TDES.o TEA.o Twofish.o XTEA.o

SymAlg.o: SymAlg.h SymAlg.cpp
	$(CXX) $(CFLAGS) SymAlg.cpp

AES.o: AES.cpp AES.h AES_Const.h ../common/cryptomath.h SymAlg.h
	$(CXX) $(CFLAGS) AES.cpp

Blowfish.o: Blowfish.cpp Blowfish.h Blowfish_Const.h SymAlg.h
	$(CXX) $(CFLAGS) Blowfish.cpp

Camellia.o: Camellia.cpp Camellia.h Camellia_Const.h ../common/integer.h ../common/cryptomath.h SymAlg.h
	$(CXX) $(CFLAGS) Camellia.cpp

CAST128.o: CAST128.cpp CAST128.h CAST128_Const.h ../common/cryptomath.h SymAlg.h
	$(CXX) $(CFLAGS) CAST128.cpp

CAST256.o: CAST256.cpp CAST256.h ./SymAlg.h
	$(CXX) $(CFLAGS) CAST256.cpp

CBC.o: CBC.cpp CBC.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CFLAGS) CBC.cpp

CFB.o: CFB.cpp CFB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CFLAGS) CFB.cpp

CTR.o: CTR.cpp CTR.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CFLAGS) CTR.cpp

DES.o: DES.cpp DES.h DES_Const.h ./SymAlg.h
	$(CXX) $(CFLAGS) DES.cpp

DESX.o: DESX.cpp DESX.h ./SymAlg.h
	$(CXX) $(CFLAGS) DESX.cpp

ECB.o: ECB.cpp ECB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CFLAGS) ECB.cpp

Encryptions.o: Encryptions.cpp Encryptions.h ../common/includes.h ../common/cryptomath.h SymAlg.h AES.h Blowfish.h Camellia.h CAST128.h CAST256.h CBC.h CFB.h CTR.h DES.h DESX.h ECB.h GOST.h IDEA.h MISTY1.h OFB.h RC2.h RC4.h RC5.o RC6.h SAFERK64.h SEED.h Skipjack.h SymAlg.h TDES.h TEA.h XTEA.h
	$(CXX) $(CFLAGS) Encryptions.cpp

GOST.o: GOST.cpp GOST.h GOST_Const.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CFLAGS) GOST.cpp

IDEA.o: IDEA.cpp IDEA.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CFLAGS) IDEA.cpp

MISTY1.o: MISTY1.cpp MISTY1.h MISTY1_Const.h ./SymAlg.h
	$(CXX) $(CFLAGS) MISTY1.cpp

OFB.o: OFB.cpp OFB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CFLAGS) OFB.cpp

PCPB.h: PCPB.cpp PCPB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CXX) $(CFLAGS) PCPB.cpp

RC2.o: RC2.cpp RC2.h RC2_Const.h ../common/cryptomath.h ./SymAlg.h
	$(CXX) $(CFLAGS) RC2.cpp

RC4.o: RC4.cpp RC4.h ./SymAlg.h
	$(CXX) $(CFLAGS) RC4.cpp

RC5.o: RC5.cpp RC5.h ../common/cryptomath.h ./SymAlg.h
	$(CXX) $(CFLAGS) RC5.cpp

RC6.o: RC6.cpp RC6.h ../common/cryptomath.h ../common/integer.h ./SymAlg.h
	$(CXX) $(CFLAGS) RC6.cpp

RC_PQ.o: RC_PQ.cpp RC_PQ.h
	$(CXX) $(CFLAGS) RC_PQ.cpp

SAFERK64.o: SAFERK64.cpp SAFERK64.h SAFERK64_Const.h ../common/cryptomath.h ./SymAlg.h
	$(CXX) $(CFLAGS) SAFERK64.cpp

SEED.o: SEED.cpp SEED.h SEED_Const.h ../common/cryptomath.h ../common/integer.h ./SymAlg.h
	$(CXX) $(CFLAGS) SEED.cpp

Skipjack.o: Skipjack.cpp Skipjack.h Skipjack_Const.h ./SymAlg.h
	$(CXX) $(CFLAGS) Skipjack.cpp

TDES.o: TDES.cpp TDES.h DES.h ./SymAlg.h
	$(CXX) $(CFLAGS) TDES.cpp

TEA.o: TEA.cpp TEA.h ./SymAlg.h
	$(CXX) $(CFLAGS) TEA.cpp

Twofish.o: Twofish.h Twofish.cpp SymAlg.h Twofish_Const.h
	$(CXX) $(CFLAGS) Twofish.cpp

XTEA.o: XTEA.cpp XTEA.h ./SymAlg.h
	$(CXX) $(CFLAGS) XTEA.cpp

clean:
	rm -f *.o *.a
