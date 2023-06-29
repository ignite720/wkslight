#include "bar.h"

#include <iostream>

template<typename T>
void Bar<T>::print(T value)
{
	std::cout << "Bar: " << value << std::endl;
}

/* explicitly instantiate the template class */
template
class Bar<int>;

template
class Bar<float>;