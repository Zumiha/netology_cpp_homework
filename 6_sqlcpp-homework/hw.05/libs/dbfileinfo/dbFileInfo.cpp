#include "dbFileInfo.h"

namespace dbconnect {
    std::string FileInfo (std::string & _filename) {
        std::ifstream file (_filename);

        std::istream_iterator<std::string> start(file), end;
        std::vector<std::string> info_vect(start, end);
        file.close();

        std::stringstream ss;
        ss << "host="+info_vect[0] + " port=" + info_vect[1] + " dbname=" + info_vect[2] + " user=" + info_vect[3] + " password=" + info_vect[4]; 

        std::string connection_info = ss.str();
        return connection_info;
    }
}
