#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <exception>

struct SectionData {
    std::string name;
    std::map<std::string, std::string> var_val;
};

class IniParser {
public:
    IniParser(std::string str);
    ~IniParser();

    template <typename T> T getValue (const std::string &request_string) {
        std::string str = getKeyValue(request_string);
        std::istringstream ss(str);
        T num;
        ss >> num;
        return num;
    }

private:
    std::string request_line;
    std::string file_name;
    std::ifstream file;
    std::vector<SectionData> SectionsData{};
    int line_count = 0;


    void parseFile(std::string &f_name);

    SectionData* getSecPtr(const std::string& section_name);

    const std::string getKeyValue(const std::string& _sec_name, const std::string& _var_name);

    void trimString(std::string &str);

    void removeComment(std::string& str);

    bool checkDelim (const std::string &_str, char _a);
    bool checkDelim (const std::string &_str, char _a, char _b);

    bool checkDubles (const std::string &_str, char _a);

    bool checkDubles (const std::string &_str, char _a, char _b);

    std::string getKeyValue(const std::string &request);
};