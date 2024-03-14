#include <iostream>
#include <sstream>

#include "0_Figure.h"

#include "01.0_triangle.h"
#include "01.1_rt.h"
#include "01.2_io.h"
#include "01.3_et.h"

#include "02.0_quadri.h"

#include "02.1.0_paral.h"

#include "02.1.1_rhomb.h"
#include "02.1.2.0_rect.h"
#include "02.1.2.1_squire.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    Figure* f;

    Triangle triAngle_1(10, 20, 30, 50, 60, 70);
    RightTriangle triAngle_2(10, 20, 30, 40, 50);
    IsoTriangle triAngle_3(10, 20, 50, 60);
    EquiTriangle triAngle_4(30);

    f = &triAngle_1; f->printInfo();
    f = &triAngle_2; f->printInfo();
    f = &triAngle_3; f->printInfo();
    f = &triAngle_4; f->printInfo();

    Quadrilateral tetrAngle_1(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle tetrAngle_2(10, 20);
    Square tetrAngle_3(20);
    Parallelogram tetrAngle_4(20, 30, 30, 40);
    Rhombus tetrAngle_5(30, 30, 40);

    f = &tetrAngle_1; f->printInfo();
    f = &tetrAngle_2; f->printInfo();
    f = &tetrAngle_3; f->printInfo();
    f = &tetrAngle_4; f->printInfo();
    f = &tetrAngle_5; f->printInfo();

    return 0;
}