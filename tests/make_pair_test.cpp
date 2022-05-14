#include "../utils/make_pair.hpp"

// make_pair example
#include <utility>  // std::pair
#include <iostream> // std::cout

#define GREEN "\e[1;32m"
#define DEFAULT "\e[0;37m"



int main()
{
    std::cout << GREEN;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "*                            STD TEST                     *" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << DEFAULT;
    {
        std::pair<int, int> foo;
        std::pair<int, int> bar;

        foo = std::make_pair(10, 20);
        bar = std::make_pair(10.5, 'A'); // ok: implicit conversion from pair<double,char>

        std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
        std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
    }
    std::cout << GREEN;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "*                            FT  TEST                     *" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << DEFAULT;
    {
        ft::pair<int, int> foo;
        ft::pair<int, int> bar;

        foo = ft::make_pair(10, 20);
        bar = ft::make_pair(10.5, 'A'); // ok: implicit conversion from pair<double,char>

        std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
        std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
    }
    return 0;
}