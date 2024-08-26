#include "TestDynLib.h"

namespace LeaverLib {

	Leaver::Leaver(std::string& usrInp) {
		setName(usrInp);
	}

	std::string Leaver::leave() {
		return "До свидания, " + this->name + "!\n";
	}

	void Leaver::setName(std::string _name) {
		this->name = _name;
	}

	std::string name;
}