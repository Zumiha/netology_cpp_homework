#include "BigInt.h"



BigInt::BigInt(const std::string& str) : number(str), length(static_cast<int>(number.length())) {
	int count = 0;
	while (this->number[count] == '0' && this->number.length() - count > 1) {
		count++;
	}
	this->number = this->number.substr(count); 

}
BigInt::BigInt(const long& str) : number(std::to_string(str)), length(static_cast<int>(number.length())) {}

BigInt::BigInt(BigInt&& other) noexcept {		
	length = other.length;
	number = std::move(other.number);
}

const std::string& BigInt::getValue() const {
	return number;
}

const int BigInt::getLength() const {
	return length;
}

BigInt& BigInt::operator=(const BigInt& other) {
	if (this != &other)
	{
		this->length = other.length;
		this->number = other.number;
	}
	return *this;
}

BigInt& BigInt::operator=(BigInt&& other) noexcept {
	std::swap(number, other.number);
	return *this;
}

BigInt BigInt::operator+(const BigInt& other) {

	std::string num2 = other.getValue(); 
	size_t len1 = this->getLength(), len2 = other.getLength(); 
	size_t length = 1 + std::max(len1, len2); 
	char* result = new char[length+1] {'\0'};

	for (size_t i = 0; i < length - 1; i++) {
		int j = length - 1 - i;
		result[j] += ((i < len2) ? (num2[len2 - 1 - i] - 48) : 0) + ((i < len1) ? (number[len1 - 1 - i] - 48) : 0); 
		result[j - 1] = result[j] / 10; 
		result[j] = result[j] % 10 + 48; 
	}
	result[0] += 48;	

	return BigInt(std::string(result));
}


BigInt BigInt::operator*(int other) const {
	std::string mult_num= std::to_string(other);
	if (number == "0" || mult_num == "0") {
		return 0;
	}

	size_t len1 = this->getLength(), len2 = mult_num.length(); 
	size_t length = len1 + len2;

	int* a = new int[length];
	int* b = new int[length];
	char* result = new char[length + 1] {'\0'};

	for (size_t i = 0; i < length; i++) {
		a[i] = (i < len1) ? (number[len1 - 1 - i] - '0') : 0;
		b[i] = (i < len2) ? (mult_num[len2 - 1 - i] - '0') : 0;
		result[i] = 0;
	}
	for (size_t i = 0; i < len1; i++) {
		for (size_t j = 0; j < len2; j++) {
			result[length - 1 - (i + j)] += a[i] * b[j];
			result[length - 1 - (i + j + 1)] += result[length - 1 - (i + j)] / 10;
			result[length - 1 - (i + j)] %= 10;
		}
	}
	for (size_t i = 0; i < length; i++)
		result[length - 1 - i] += '0';

	return BigInt(std::string(result));	
}

std::ostream& operator<<(std::ostream& os, const BigInt& bi) {
	os << bi.number;
	return os;
}