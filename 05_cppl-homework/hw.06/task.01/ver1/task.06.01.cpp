#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

struct Data
{
public:
    std::string symb;
    size_t count;
};

int main()
{
    std::string string { "Hello world!!" };
    std::map<char, int> map_str;

    for (const auto &item : string){
        int count = std::count(string.begin(), string.end(), item);
        map_str.insert(std::make_pair(item, count));
    }

    if (map_str.size() > 0){
        std::vector<Data> data;
        for (const auto &it : map_str){
            Data new_item;
            new_item.symb = it.first;
            new_item.count = it.second;
            data.push_back(new_item);
        }

        std::sort(data.begin(), data.end(), [](Data &_symb, Data &_count) { return _symb.count > _count.count; });

        std::cout << "[IN]: " << string << std::endl;
        std::cout << "[OUT]: " << std::endl;
        for (size_t i = 0; i < data.size(); i++){
            std::cout << data[i].symb << ": " << data[i].count << std::endl;
        }
    }
}
