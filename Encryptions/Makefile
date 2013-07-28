# Encryptions Makefile

CC=g++
LFLAGS=
CFLAGS=-std=c++11 -Wall -c

all: AES.o Blowfish.o Camellia.o CAST128.o CAST256.o CBC.o CFB.o CTR.o DES.o DESX.o ECB.o Encryptions.o error.o GOST.o IDEA.o MISTY1.o OFB.o RC2.o RC4.o RC5.o RC6.o RC_PQ.o SAFERK64.o SEED.o Skipjack.o TDES.o TEA.o XTEA.o

AES.o: AES.cpp AES.h AES_Const.h ../common/cryptomath.h error.h SymAlg.h
	$(CC) $(CFLAGS) AES.cpp

Blowfish.o: Blowfish.cpp Blowfish.h Blowfish_Const.h error.h SymAlg.h
	$(CC) $(CFLAGS) Blowfish.cpp

Camellia.o: Camellia.cpp Camellia.h Camellia_Const.h ../common/integer.h ../common/cryptomath.h error.h SymAlg.h
	$(CC) $(CFLAGS) Camellia.cpp

CAST128.o: CAST128.cpp CAST128.h CAST128_Const.h ../common/cryptomath.h error.h SymAlg.h
	$(CC) $(CFLAGS) CAST128.cpp

CAST256.o: CAST256.cpp CAST256.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) CAST256.cpp

CBC.o: CBC.cpp CBC.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CC) $(CFLAGS) CBC.cpp

CFB.o: CFB.cpp CFB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CC) $(CFLAGS) CFB.cpp

CTR.o: CTR.cpp CTR.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CC) $(CFLAGS) CTR.cpp

DES.o: DES.cpp DES.h DES_Const.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) DES.cpp

DESX.o: DESX.cpp DESX.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) DESX.cpp

ECB.o: ECB.cpp ECB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CC) $(CFLAGS) ECB.cpp

Encryptions.o: Encryptions.cpp Encryptions.h ../common/includes.h ../common/cryptomath.h error.h SymAlg.h AES.h Blowfish.h Camellia.h CAST128.h CAST256.h CBC.h CFB.h CTR.h DES.h DESX.h ECB.h GOST.h IDEA.h MISTY1.h OFB.h RC2.h RC4.h RC5.o RC6.h SAFERK64.h SEED.h Skipjack.h SymAlg.h TDES.h TEA.h XTEA.h
	$(CC) $(CFLAGS) Encryptions.cpp

error.o: error.cpp error.h ../common/includes.h
	$(CC) $(CFLAGS) error.cpp

GOST.o: GOST.cpp GOST.h GOST_Const.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CC) $(CFLAGS) GOST.cpp

IDEA.o: IDEA.cpp IDEA.h  ../common/includes.h ../common/integer.h SymAlg.h
	$(CC) $(CFLAGS) IDEA.cpp

MISTY1.o: MISTY1.cpp MISTY1.h MISTY1_Const.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) MISTY1.cpp

OFB.o: OFB.cpp OFB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CC) $(CFLAGS) OFB.cpp

PCPB.h: PCPB.cpp PCPB.h ../common/includes.h ../common/integer.h SymAlg.h
	$(CC) $(CFLAGS) PCPB.cpp

RC2.o: RC2.cpp RC2.h RC2_Const.h ../common/cryptomath.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) RC2.cpp

RC4.o: RC4.cpp RC4.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) RC4.cpp

RC5.o: RC5.cpp RC5.h ../common/cryptomath.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) RC5.cpp

RC6.o: RC6.cpp RC6.h ../common/cryptomath.h ../common/integer.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) RC6.cpp

RC_PQ.o: RC_PQ.cpp RC_PQ.h
	$(CC) $(CFLAGS) RC_PQ.cpp

SAFERK64.o: SAFERK64.cpp SAFERK64.h SAFERK64_Const.h ../common/cryptomath.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) SAFERK64.cpp

SEED.o: SEED.cpp SEED.h SEED_Const.h ../common/cryptomath.h ../common/integer.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) SEED.cpp

Skipjack.o: Skipjack.cpp Skipjack.h Skipjack_Const.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) Skipjack.cpp

TDES.o: TDES.cpp TDES.h DES.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) TDES.cpp

TEA.o: TEA.cpp TEA.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) TEA.cpp

XTEA.o: XTEA.cpp XTEA.h ./error.h ./SymAlg.h
	$(CC) $(CFLAGS) XTEA.cpp

clean:
	rm -f *.o
