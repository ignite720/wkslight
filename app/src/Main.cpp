#include <foo.h>
#include <bar.h>

int main(int argc, char* argv[])
{
    {
        {
            foo_print(10.0);
            foo_printi(20);
            foo_printi64(30000123456789);

            Foo foo;
            foo.print(40);
        }

        {
            Bar<int> bar;
            bar.print(100);

            Bar<float> bar2;
            bar2.print(101.0f);

#if 0
            Bar<double> bar3; // LNK2019
            bar3.print(201.0);
#endif
        }
    }
	return 0;
}