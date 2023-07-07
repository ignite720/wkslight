#pragma once

#include "bar_api.h"

template<typename T>
class Bar
{
public:
	void print(T value);
};

/* forward declaration for template */
TEMPLATE_EXTERN template
class BAR_API Bar<int>;

TEMPLATE_EXTERN template
class BAR_API Bar<float>;