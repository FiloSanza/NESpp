#ifndef NESPP_REGISTER_H
#define NESPP_REGISTER_H

#include <string>

namespace nespp {

    template<typename T>
    class Register {
    public:
        void set_value(T value);

        T get_value();

        std::string get_name();

        Register<T>() = delete;

        explicit Register<T>(std::string name);

    protected:
        T value;
        std::string name;
    };

}

#endif //NESPP_REGISTER_H
