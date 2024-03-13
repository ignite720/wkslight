#pragma once

#include "bar_api.h"

#include <iostream>

template<typename T>
class BAR_API Bar
{
public:
	void print(T value) {
		std::cout << "Bar.print: " << value << std::endl;
	}
};

/* forward declaration for template */
//TEMPLATE_EXTERN template
//class BAR_API Bar<int>;

//TEMPLATE_EXTERN template
//class BAR_API Bar<float>;