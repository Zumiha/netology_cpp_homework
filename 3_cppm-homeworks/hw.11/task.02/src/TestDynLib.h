#pragma once
#include <string>

namespace LeaverLib {

	class Leaver {
	public:
		Leaver(std::string& usrInp);
		std::string leave();
	protected:
		void setName(std::string _name);

	private:
		std::string name;
	};

}