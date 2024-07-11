#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>

enum Type {
	WARN,
	ERR,
	FATERR,
	UNKW
};

class LogMessage {
public:
	LogMessage(Type ext_type, const std::string& ext_message) : err_type(ext_type), message_text(ext_message) {}
	Type type() const {return err_type;}
	const std::string& message() const {return message_text;}

private:
	Type err_type;
	std::string message_text;
};

class LogHandler {
public:
    LogHandler(LogHandler* handler = nullptr) : next_handler(handler) {}
    virtual ~LogHandler() = default;
    virtual void handleMessage(const LogMessage& message_obj) = 0;
	void setHandler(LogHandler* handler) {next_handler = handler;}
    void printLog (const LogMessage& message) {std::cout << "Log: " << message.message() << "\n";}

protected:
	LogHandler* next_handler;
};

class Warning : public LogHandler {
public:
    void handleMessage(const LogMessage& message) override {
        if (message.type() == WARN) {printLog(message);}
        else {next_handler->handleMessage(message);}
    }
};

class Error : public LogHandler {
private:
    std::ofstream log_file;

public:
    Error(const std::string& filename) {
        log_file.open(filename, std::ofstream::app);
        if (!(log_file.is_open())) {throw std::runtime_error("Log file couldnot be found or cannot write to file...");}
    }
    ~Error() {if(log_file.is_open()) log_file.close();}

    void handleMessage(const LogMessage& message) override {
        if (message.type() == ERR) {
            log_file << "Log: " << message.message() << "\n"; log_file.close();
            printLog(message);
        }
        else {next_handler->handleMessage(message);}
    }
};

class FatalError : public LogHandler {
public:
    void handleMessage(const LogMessage& message) override {
        if (message.type() == FATERR) {throw std::runtime_error(message.message());}
        else {next_handler->handleMessage(message);}
    }
};

class Unknown : public LogHandler {
public:
    void handleMessage(const LogMessage& message) override {
        if (message.type() == UNKW) {throw std::runtime_error(message.message());}
        else {next_handler->handleMessage(message);}
    }
};