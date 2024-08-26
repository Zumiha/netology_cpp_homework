#include <iostream>

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

#include "ValError.h"


int main()
{
    setlocale(LC_ALL, "Russian");

    Figure* f = nullptr;

    try {
        Figure fig1;
        f = &fig1;
        f -> printInfo();
    } catch (ValExcept & ve) {
        std::cout << ve.what() << std::endl;
    }          

//triangles

    try {
        Triangle triAngle_1(10, 20, 20, 50, 60, 70);
        f = &triAngle_1;
        f -> printInfo();
    } catch (ValExcept & ve) {
        std::cout << ve.what() << std::endl;
    }

    try {
       RightTriangle triAngle_2(10, 20, 20, 30, 60, 90);
       f = &triAngle_2;
       f -> printInfo();
    } catch (ValExcept & ve) {
       std::cout << ve.what() << std::endl;
    }

    try {
       IsoTriangle triAngle_3(15, 20, 15, 50, 80, 50);
       f = &triAngle_3;
       f -> printInfo();
    } catch (ValExcept & ve) {
       std::cout << ve.what() << std::endl;
    }

    try {
       EquiTriangle triAngle_4(20, 20, 20, 60, 60, 60);
       f = &triAngle_4;
       f -> printInfo();
    } catch (ValExcept & ve) {
       std::cout << ve.what() << std::endl;
    }


//quadrilaterals

    try {
       Quadrilateral tetrAngle_1(10, 20, 30, 40, 90, 90, 90, 90);
       f = &tetrAngle_1;
       f -> printInfo();
    } catch (ValExcept & ve) {
       std::cout << ve.what() << std::endl;
    }

    try {
       Parallelogram tetrAngle_4(50, 40, 50, 40, 50, 130, 50, 130);
       f = &tetrAngle_4;
       f -> printInfo();
    } catch (ValExcept & ve) {
       std::cout << ve.what() << std::endl;
    }

    try {
       Rhombus tetrAngle_5(20, 20, 20, 20, 80, 100, 80, 100);
       f = &tetrAngle_5;
       f -> printInfo();
    } catch (ValExcept & ve) {
       std::cout << ve.what() << std::endl;
    }

    try {
       Rectangle tetrAngle_2(10, 20, 10, 20, 90, 90, 90, 90);
       f = &tetrAngle_2;
       f -> printInfo();
    } catch (ValExcept & ve) {
       std::cout << ve.what() << std::endl;
    }

    try {
       Square tetrAngle_3(10, 10, 10, 10, 90, 90, 90, 90);
       f = &tetrAngle_3;
       f -> printInfo();
    } catch (ValExcept & ve) {
       std::cout << ve.what() << std::endl;
    }

    return 0;
}