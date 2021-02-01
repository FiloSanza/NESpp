#include "hexdump.h"

namespace nespp {
    void Hexdump::dump(std::string& description, const void* addr, const int len) {
        dump(description, addr, len, stdout);
    }

    void Hexdump::dump(std::string& description, const void* addr, const int len, FILE* file) {
        const auto* mem_ptr = (const uint8_t*)addr;

        fprintf(file, "Start at %p\n", addr);
        if(!description.empty())
            fprintf(file, "%s:\n", description.c_str());

        std::string ascii_buf;

        for(int i=0; i<len; i++) {
            if ((i % 16) == 0) {
                if(!ascii_buf.empty()){
                    fprintf(file, "  %s\n", ascii_buf.c_str());     //print the ascii buffer
                    ascii_buf.clear();
                }
                fprintf(file, "  %04x ", i);                       //address offset
            }

            fprintf(file, " %02x", mem_ptr[i]);

            ascii_buf.push_back(isprint(mem_ptr[i]) ? (char)mem_ptr[i] : '.');
        }

        //padding
        for(int i=(int)ascii_buf.size() + 1; i<17; i++)
            fprintf(file, "    ");
        fprintf(file, "  %s\n", ascii_buf.c_str());
    }
}