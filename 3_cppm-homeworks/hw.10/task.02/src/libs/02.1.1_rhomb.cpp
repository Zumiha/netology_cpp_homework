#include "02.1.1_rhomb.h"

Rhombus::Rhombus(int abcd, int AC, int BD) : Parallelogram(abcd, abcd, AC, BD) {
    setName("Ромб");
}