#include "stack_pointer.h"

namespace nespp {
    void StackPointer::inc() {
        value++;
    }

    void StackPointer::dec() {
        value--;
    }
}