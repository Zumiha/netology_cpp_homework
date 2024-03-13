#include <iostream>
#include <fstream>
#include <string>

class Address
{
public:
	Address() : Address("", "", 0, 0) {}

	Address(std::string c, std::string s, int h, int f) {
		setCity(c);
		setStreet(s);
		setHouse(h);
		setAprt(f);
	}

	std::string exportAddress() {
		std::string result = "";
		result += this->City;
		result += ", ";
		result += this->Street;
		result += ", ";
		result += std::to_string(this->House);
		result += ", ";
		result += std::to_string(this->Aprt);
		result += '\n';

		return result;
	}

	void setCity(std::string c) {
		this->City = c;
	}

	void setStreet(std::string s) {
		this->Street = s;
	}

	void setHouse(int h) {
		this->House = h;
	}

	void setAprt(int f) {
		this->Aprt = f;
	}


	void sortAdrs(Address* _a, int size) {
		if (size <= 0) return;

		int i = 1;
		while (i < size) {
			int j = i;

			while ((j > 0) && ((_a + j - 1)->City) <= ((_a + j)->City)) {
				std::swap(*(_a + j), *(_a + j - 1));
				--j;
			}
			i++;
		}
	}

private:
	std::string City;
	std::string Street;
	int House;
	int Aprt;
};

int main()
{
	setlocale(LC_ALL, "Russian");

	std::string file_in = "in.txt";
	std::ifstream file_to_read(file_in);

	if (!file_to_read.is_open()) {
		std::cerr << "Невозможно открыть файл. Файл не найден." << std::endl;
		return 404;
	}

	std::string current_str;
	file_to_read >> current_str;
	int sizeN = std::stoi(current_str);

	if (sizeN <= 0) {
		std::cerr << "Неправильный формат строки адресов." << std::endl;
		return 8;
	}

	Address* arrAdrs = new Address[sizeN];

	for (int i = 0; i < sizeN; ++i) {
		std::string city;
		file_to_read >> city;
		std::string street;
		file_to_read >> street;
		std::string house;
		file_to_read >> house;
		std::string apart;
		file_to_read >> apart;
		arrAdrs[i] = Address(city, street, stoi(house), stoi(apart));
	}

	file_to_read.close();

	arrAdrs->sortAdrs(arrAdrs, sizeN);

	std::string file_out = "out.txt";
	std::ofstream file_to_write(file_out);

	file_to_write << sizeN << std::endl;

	for (int i = sizeN - 1; i >= 0; --i) {
		file_to_write << (arrAdrs + i)->exportAddress();
	}

	file_to_write.close();

	delete[] arrAdrs;

	return 0;
}