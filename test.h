#ifndef TEST_H_
#define TEST_H_

// teszteléshez használt osztályok
#include "menetrend.h"
#include "vonat.h"
#include "jegy.h"
#include "utvonal.h"
#include "ido.h"
#include "allomas.h"
#include "kocsi.h"

// perzisztencia vizsgálatához
#include <sstream>

// memória helyes használatának ellőrzéséhez
#include "memtrace.h"
// teszteléshez használt makrók
#include "gtest_lite.h"

// Programhoz tartozó teszteket futtató függvény
// @param void
// @return void
void test();

#endif /* TEST_H_ */