#ifndef NESPP_HEXDUMP_H
#define NESPP_HEXDUMP_H

//https://stackoverflow.com/questions/7775991/how-to-get-hexdump-of-a-structure-data
//http://www.i42.co.uk/stuff/hexdump.htm

#include <string>
#include <stdio.h>
#include <ctype.h>

namespace nespp {

    class Hexdump {
    public:
        Hexdump() = delete;
        static void dump(std::string& description, const void* addr, int len);
        static void dump(std::string& description, const void* addr, int len, FILE* file);
    };

}

#endif //NESPP_HEXDUMP_H
