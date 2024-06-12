#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>

Shape::Shape(Type extType) : type(extType) {
	switch (extType) {
	case LINE: this->shape_name = "Line"; break;
	case SQUARE: this->shape_name = "Rectangle"; break;
	case CIRLCE: this->shape_name = "Circle"; break;
	case CUBE: this->shape_name = "Parallelepiped"; break;
	case CYLINDER: this->shape_name = "Cylinder"; break;
	default: this->shape_name = "Figure"; break;
	}		
}
Shape::~Shape() {}

double Shape::calcLength(pointCoord point_one, pointCoord point_two) const {
	return std::sqrt(
		std::pow(point_one.p_x - point_two.p_x, 2) + 
		std::pow(point_one.p_y - point_two.p_y, 2) + 
		std::pow(point_one.p_z - point_two.p_z, 2) );
}

bool Shape::checkEquality(pointCoord _a, pointCoord _b) const {
	if (_a == _b) {throw std::length_error("Invalid vector length. Must not be zero.");} 
	else {return false;}
};

Line::Line(pointCoord _a, pointCoord _b) : Shape (LINE), dot_A(_a), dot_B(_b) {checkEquality(_a, _b);}
Line::~Line () {}

Square::Square(pointCoord _a, pointCoord _b) : Shape (SQUARE), dot_A(_a), dot_B(_b) {checkEquality(_a, _b);};
Square::~Square () {};
bool Square::checkEquality(pointCoord _a, pointCoord _b) const {
	if (_a == _b) {throw std::length_error("Invalid vector length. Must not be zero.");}
	else if (_a || _b) {throw std::length_error("Vertexes collision. Vertexes must form 2D figure.");}
	else {return false;}
};

Circle::Circle(pointCoord _a, double _radius) : Shape (CIRLCE), dot_A(_a), radius(_radius) {
	if (_radius <= 0) throw std::length_error("Invalid vector length. Radius must be more than zero.");
};
Circle::~Circle () {};


Cube::Cube(pointCoord _a, pointCoord _b, pointCoord _c) : Shape (CUBE), dot_A(_a), dot_B(_b), dot_C(_c) {checkEquality(_a, _b, _c);};
Cube::~Cube () {};
bool Cube::checkEquality(pointCoord _a, pointCoord _b, pointCoord _c) const {
	if (((_a || _b) && (_b || _c)) || ((_a || _b) && (_a || _c))) {throw ("Vertexes collision. Vertexes must form 3D figure.");}
	else {return false;}
};

Cylinder::Cylinder(pointCoord _a, double _radius, pointCoord _h) : Shape (CYLINDER), dot_A(_a), radius(_radius), dot_H(_h)  {
	if (_radius <= 0) throw std::length_error("Invalid vector length. Radius must be more than zero.");
	checkEquality(_a, _h);
};
Cylinder::~Cylinder () {};