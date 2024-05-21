#ifndef TEST_H_
#define TEST_H_

/// Teszteléskor vizsgált osztályok.
#include "menetrend.h"
#include "vonat.h"
#include "jegy.h"
#include "utvonal.h"
#include "ido.h"
#include "allomas.h"
#include "kocsi.h"

/// Perzisztencia vizsgálatához.
#include <sstream>
#include <iostream>

/// Memória helyes használatának ellőrzéséhez.
#include "memtrace.h"
/// Teszteléshez használt makrók.
#include "gtest_lite.h"

/// Programhoz tartozó teszteket futtató függvény.
void test();

#endif /* TEST_H_ */