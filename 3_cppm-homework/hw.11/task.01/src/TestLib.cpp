#include "TestLib.h"

namespace GreeterLib {

	Greeter::Greeter(std::string& usrInp) {
		setName(usrInp);
	}

	std::string Greeter::greet() {
		return "здравствуйте, " + this->name + "!\n";
	}

	void Greeter::setName(std::string _name) {
		this->name = _name;
	}

	std::string name;
}