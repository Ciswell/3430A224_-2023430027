#include <iostream>

double squsre(double x) {

return x*x;

}

void print_square(double x) {

    std::cout << "the square of " << x << "is " << squsre(x) << "\n";
}

int main()
{
        print_square(1.2345);
        print_square(5.555);
}