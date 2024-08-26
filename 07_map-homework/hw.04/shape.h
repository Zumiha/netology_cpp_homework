#pragma once
#include <stdexcept>
#include<string>

enum Type {
	LINE,
	SQUARE,
	CIRLCE,
	CUBE,
	CYLINDER
};

struct pointCoord {
	double p_x{};
	double p_y{};
	double p_z{};
	bool operator==(const pointCoord &_a) const {
		if (p_x == _a.p_x && p_y == _a.p_y && p_z == _a.p_z) return true;	
	}; 
	bool operator||(const pointCoord &_a) const {
		if 		(p_x == _a.p_x && p_y == _a.p_y) {return true;}
		else if (p_y == _a.p_y && p_z == _a.p_z) {return true;}	
		else if (p_x == _a.p_x && p_z == _a.p_z) {return true;}
	}; 
};

class Shape {
public:
	Shape(Type extType);
	~Shape();
	double virtual calcLength(pointCoord point_one, pointCoord point_two) const;
	bool virtual checkEquality(pointCoord _a, pointCoord _b) const;
	double virtual calcArea() const;
	double virtual calcVolume() const;
	int getType() {
		return type; 
	}
protected:
	std::string shape_name;
	Type type;
};

class Line : public Shape {
public:
	Line(pointCoord _a, pointCoord _b) : Shape (LINE), dot_A(_a), dot_B(_b) {};
	~Line () {};
private:
	pointCoord dot_A;
	pointCoord dot_B;
};

class Square : public Shape {
public:
	Square(pointCoord _a, pointCoord _b) : Shape (SQUARE), dot_A(_a), dot_B(_b) {};
	~Square () {};
	bool virtual checkEquality(pointCoord _a, pointCoord _b) const override;
	double calcArea() const override;
private:
	pointCoord dot_A;
	pointCoord dot_B;
};

class Circle : public Shape {
public:
	Circle(pointCoord _a, double _radius) : Shape (CIRLCE), dot_A(_a), radius(_radius) {};
	~Circle () {};
private:
	pointCoord dot_A;
	double radius;
};

class Cube : public Shape {
public:
	Cube(pointCoord _a, pointCoord _b, pointCoord _c) : Shape (CUBE), dot_A(_a), dot_B(_b), dot_C(_c) {};
	~Cube () {};
	bool checkEquality(pointCoord _a, pointCoord _b, pointCoord _c) const;
private:
	pointCoord dot_A;
	pointCoord dot_B;
	pointCoord dot_C;
};

class Cylinder : public Shape {
public:
	Cylinder(pointCoord _a, double _radius, pointCoord _h) : Shape (CYLINDER), dot_A(_a), radius(_radius), dot_H(_h) {};
	~Cylinder () {};
private:
	pointCoord dot_A;
	double radius;
	pointCoord dot_H;
};

