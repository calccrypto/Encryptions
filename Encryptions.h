/*
Encryptions.h

Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef ENCRYPTIONS_H
#define ENCRYPTIONS_H

// common includes
#include "common/includes.h"
#include "common/cryptomath.h"
#include "Encryptions/SymAlg.h"

// Algorithms
#include "Encryptions/AES.h"
#include "Encryptions/Blowfish.h"
#include "Encryptions/Camellia.h"
#include "Encryptions/CAST128.h"
#include "Encryptions/CAST256.h"
#include "Encryptions/DES.h"
#include "Encryptions/DESX.h"
#include "Encryptions/GOST.h"
#include "Encryptions/IDEA.h"
#include "Encryptions/MISTY1.h"
#include "Encryptions/RC2.h"
#include "Encryptions/RC4.h"
#include "Encryptions/RC5.h"
#include "Encryptions/RC6.h"
#include "Encryptions/SAFERK64.h"
#include "Encryptions/SEED.h"
#include "Encryptions/Skipjack.h"
#include "Encryptions/TDES.h"
#include "Encryptions/TEA.h"
#include "Encryptions/Twofish.h"
#include "Encryptions/XTEA.h"

// Modes of Operation
#include "modes/ECB.h"
#include "modes/CBC.h"
#include "modes/CFB.h"
#include "modes/CTR.h"
#include "modes/OFB.h"
#include "modes/PCPB.h"

#endif