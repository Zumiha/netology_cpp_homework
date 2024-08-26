#include <iostream>
#include <Windows.h>

unsigned int reGcd(int a, int b) {
	if (b < 0) {
		b *= -1;
		a *= -1;
	}
	if (b == 0) { return a; }
	else { return reGcd(b, a % b); };
};

class Fraction {

public:
	Fraction() {
		setFraction(0, 1);
	}

	Fraction(int numerator, int denominator) {
		setFraction(numerator, denominator);
	}

	void setFraction(int a, int b) {
		numerator_ = a;
		denominator_ = b;
	}

	friend std::ostream& operator<<(std::ostream& outstr, const Fraction& a) {
		outstr << a.numerator_ << '/' << a.denominator_;
		return outstr;
	}

	Fraction operator+(const Fraction& other) {
		Fraction tmp;
		tmp.numerator_ = (this->numerator_ * other.denominator_) + (other.numerator_ * this->denominator_);
		tmp.denominator_ = this->denominator_ * other.denominator_;
		redFraction(&tmp);
		return tmp;
	}

	Fraction operator-(const Fraction& other) {
		Fraction tmp;
		tmp.numerator_ = (this->numerator_ * other.denominator_) - (other.numerator_ * this->denominator_);
		tmp.denominator_ = (this->denominator_ * other.denominator_);
		redFraction(&tmp);
		return tmp;
	}

	Fraction operator-() {
		return Fraction(-numerator_, denominator_);
	}

	Fraction operator*(const Fraction& other) {
		Fraction tmp;
		tmp.numerator_ = this->numerator_ * other.numerator_;
		tmp.denominator_ = this->denominator_ * other.denominator_;
		redFraction(&tmp);
		return tmp;
	}

	Fraction operator/(const Fraction& other) {
		Fraction tmp;
		tmp.numerator_ = this->numerator_ * other.denominator_;
		tmp.denominator_ = this->denominator_ * other.numerator_;
		redFraction(&tmp);
		return tmp;
	}

	Fraction operator++() {
		this->numerator_ = this->numerator_ + this->denominator_;
		redFraction(this);
		return *this;
	}

	Fraction operator++(int) {
		Fraction temp = *this;
		++(*this);
		return temp;
	}

	Fraction operator--() {
		this->numerator_ = this->numerator_ - this->denominator_;
		redFraction(this);
		return *this;
	}

	Fraction operator--(int) {
		Fraction temp = *this;
		--(*this);
		return temp;
	}


protected:

	void redFraction(Fraction* a) {
		unsigned int mmtr = reGcd(a->numerator_, a->denominator_);
		if (mmtr > 1) {
			a->numerator_ /= mmtr;
			a->denominator_ /= mmtr;
		};
	}

private:
	int numerator_;
	int denominator_;

};

void displayTest(Fraction& frc1, Fraction& frc2) {
	std::cout << std::endl;

	std::cout << frc1 << " + " << frc2 << " = " << (frc1 + frc2) << std::endl;
	std::cout << frc1 << " - " << frc2 << " = " << (frc1 - frc2) << std::endl;
	std::cout << frc1 << " * " << frc2 << " = " << (frc1 * frc2) << std::endl;
	std::cout << frc1 << " / " << frc2 << " = " << (frc1 / frc2) << std::endl;

	std::cout << "++" << frc1 << " * " << frc2 << " = " << (++frc1 * frc2) << std::endl;
	std::cout << "Значение дроби 1 = " << frc1 << std::endl;
	std::cout << "--" << frc1 << " * " << frc2 << " = " << (--frc1 * frc2) << std::endl;
	std::cout << "Значение дроби 1 = " << frc1 << std::endl;

	std::cout << frc1 << "++" << " * " << frc2 << " = " << (frc1++ * frc2) << std::endl;
	std::cout << "Значение дроби 1 = " << frc1 << std::endl;
	std::cout << frc1 << "--" << " * " << frc2 << " = " << (frc1-- * frc2) << std::endl;
	std::cout << "Значение дроби 1 = " << frc1 << std::endl;


};

int main() {

	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);

	int nom = 0, den = 0;
	Fraction frc1;
	std::cout << "Введите числитель дроби 1: ";
	std::cin >> nom;
	std::cout << "Введите знаменатель дроби 1: ";
	std::cin >> den;
	frc1.setFraction(nom, den);

	Fraction frc2;
	std::cout << "Введите числитель дроби 2: ";
	std::cin >> nom;
	std::cout << "Введите знаменатель дроби 2: ";
	std::cin >> den;
	frc2.setFraction(nom, den);

	displayTest(frc1, frc2);

	return 0;
}