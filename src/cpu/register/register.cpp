#include "register.h"

namespace nespp {

    template<typename T>
    Register<T>::Register(std::string name) : name{name}, value(0) {}

    template<typename T>
    T Register<T>::get_value() {
        return value;
    }

    template<typename T>
    std::string Register<T>::get_name() {
        return name;
    }

    template<typename T>
    void Register<T>::set_value(T value) {
        this->value = value;
    }

}