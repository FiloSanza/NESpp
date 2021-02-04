#include "register.h"
#include "program_status.h"

namespace nespp {

    template<typename T>
    Register<T>::Register(std::string name) : name{std::move(name)}, value(0) {}

    template<typename T>
    T Register<T>::get_value() {
        return value;
    }

    template<typename T>
    std::string Register<T>::get_name() {
        return name;
    }

    template<typename T>
    void Register<T>::set_value(T val) {
        value = val;
    }

    template class Register<uint8_t>;
    template class Register<uint16_t>;
    template class Register<std::bitset<FLAG_NUM>>;
}