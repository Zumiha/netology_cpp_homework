#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

class Observer {
private:
	static int static_counter;
	int obs_number;
public:
	Observer() {
		this->obs_number = ++Observer::static_counter;
	}
	int counterGetter() {return this->obs_number;}
    virtual void onWarning(const std::string& message, int subj_number) {}
    virtual void onError(const std::string& message, int subj_number) {}
    virtual void onFatalError(const std::string& message, int subj_number) {}
};

class WarningObserver : public Observer {
public:
	void onWarning(const std::string& message, int subj_number) override {std::cout << "Object #" << subj_number << " Warning: " << message << " from observer #" << counterGetter() << std::endl;}
};

class ErrorObserver : public Observer {
public:
	ErrorObserver(const std::string& _fileAdr) : file_path(_fileAdr) {}
    
	void onError(const std::string& message, int subj_number) override {
    	std::ofstream file_log(file_path, std::ios::app);
		if (file_log.is_open()) {file_log << "Object #" << subj_number << " Error: " << message << " from observer #" << counterGetter() <<std::endl;} 
		else {std::cerr << "Unable to open file: " << file_path << std::endl;}
	}
private:
    std::string file_path;
};

class FatErrorObserver : public Observer {
public:
	FatErrorObserver(const std::string& _fileAdr) : file_path(_fileAdr) {}

	void onFatalError(const std::string& message, int subj_number) override {
		std::cout << "Object #" << subj_number << " Fatal Error: " << message << " from observer #" << counterGetter() << std::endl;
		std::ofstream file_log(file_path, std::ios::app);
		if (file_log.is_open()) {file_log << "Object #" << subj_number << " Fatal Error: " << message << " from observer #" << counterGetter() << std::endl;}
		else {std::cerr << "Unable to open file: " << file_path << std::endl;}
	}
private:
    std::string file_path;
};

class Subject {
public:
	Subject() {
		this->subj_number = ++Subject::static_subj_counter;
	}
	int subj_counter()  {return this->subj_number;}
	void addObserver(Observer* _observer) {observers.push_back(_observer);}
	void removeObserver(Observer* _observer) {observers.erase(std::remove(observers.begin(), observers.end(), _observer), observers.end());}
	
	void warning(const std::string& message) const {
		for (auto it : observers) if (it) it->onWarning(message, subj_number);
	}
	void error(const std::string& message) const {
		for (auto it : observers) if (it) it->onError(message, subj_number);
	}
	void fatalError(const std::string& message) const {
		for (auto it : observers) if (it) it->onFatalError(message, subj_number);
	}
private:
	static int static_subj_counter;
	int subj_number;
    std::vector<Observer*> observers;
};

int Subject::static_subj_counter = 0;
int Observer::static_counter = 0;