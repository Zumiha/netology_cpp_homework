#pragma once
#include <string>
#include <fstream>
#include <iostream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class FileCommand : public LogCommand {
public:
    explicit FileCommand(const std::string& extr_path) : file_path(extr_path) {}

    void print(const std::string& message) override {
        std::ofstream logfile(file_path);
        logfile << message;
        logfile.close();
    }
private:
    std::string file_path;
};

void print(LogCommand& command, const std::string& message) {
    command.print(message);
};