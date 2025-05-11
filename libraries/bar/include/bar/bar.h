#pragma once

#include <iostream>
#include <typeinfo>

#include "bar/bar_api.h"

template<typename T>
class BAR_API Bar {
public:
    void print(T value) {
        std::cout << "Bar<" << typeid(T).name() << ">.print() => " << value << std::endl;
    }
};

/* forward declaration for template */
#if 0
template class BAR_API Bar<int>;
template class BAR_API Bar<float>;
#endif