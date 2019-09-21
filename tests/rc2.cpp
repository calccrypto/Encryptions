#include <gtest/gtest.h>

#include "common/includes.h"
#include "Encryptions/RC2.h"

#include "testvectors/rc/rc2rfc2268.h"

TEST(RC2, rfc2268) {
    sym_test <RC2> (RC2_RFC2268);
}
