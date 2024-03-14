#pragma once
#include <string>

namespace GreeterLib {

	class Greeter {
	public:
		Greeter(std::string& usrInp);
		std::string greet();
	protected:
		void setName(std::string _name);

	private:
		std::string name;
	};

}