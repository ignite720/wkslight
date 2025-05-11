#include "foo/foo.h"

class Foo::Impl {
public:
    void print(int n) {
        std::cout << FUNCTION_NAME << " => " << n << std::endl;
    }
};

Foo::Foo() : m_impl(new Impl()) {

}

Foo::~Foo() {
    SAFE_DELETE(m_impl);
}

void foo_print(double n) {
    printf("%s => %f\n", FUNCTION_NAME, n);
}

void foo_printi(int n) {
    printf("%s => %d\n", FUNCTION_NAME, n);
}

void foo_printi64(int64_t n) {
    printf("%s => %" PRId64 "/%" PRIi64 "/0x%" PRIx64 "\n", FUNCTION_NAME, n, n, n);
}

void Foo::print(int n) {
    PRINT_FUNCTION_NAME();
    
    m_impl->print(n);
}