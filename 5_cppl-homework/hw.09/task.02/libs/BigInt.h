#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class BigInt
{
private:
	std::string number;
	int length = 0;

public:
	BigInt(const std::string& str);
	BigInt(const long& str);
	BigInt(BigInt&& other) noexcept;

	const std::string& getValue() const;
	const int getLength() const;

	BigInt& operator=(const BigInt& other);
	BigInt& operator=(BigInt&& other) noexcept;

	BigInt operator+(const BigInt& other);

	BigInt operator*(const BigInt& other) const;
	BigInt operator*(int other) const;

	friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
};