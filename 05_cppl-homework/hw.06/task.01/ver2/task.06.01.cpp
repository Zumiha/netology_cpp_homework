#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

//Data struct dropped
//Used std::pair

int main()
{
    std::string string { "Hello world!!" };
    std::map<char, int> map_str;

    for (const auto &item : string){
        int count = std::count(string.begin(), string.end(), item);
        map_str.insert(std::make_pair(item, count));
    }

    if (map_str.size() > 0){
        std::vector<std::pair<char, int>> data;
        for (const auto &it : map_str)
            data.push_back(it);

        std::sort(data.begin(), data.end(), 
        [](std::pair<char, int> &_data_char_1, std::pair<char, int> &_data_char_2){ return _data_char_1.second > _data_char_2.second; });

        std::cout << "[IN]: " << string << std::endl;
        std::cout << "[OUT]: " << std::endl;
        for (size_t i = 0; i < data.size(); i++){
            std::cout << data[i].first << ": " << data[i].second << std::endl;
        }
    }
}
