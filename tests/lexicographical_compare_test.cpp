#include <iostream>
#include "../utils/lexicographical_compare.hpp"

#define GREEN "\e[1;32m"
#define DEFAULT "\e[0;37m"

bool mycomp(char c1, char c2)
{
  return std::tolower(c1) < std::tolower(c2);
}

int main()
{
  std::cout << GREEN;
  std::cout << "***********************************************************" << std::endl;
  std::cout << "*                            STD TEST                     *" << std::endl;
  std::cout << "***********************************************************" << std::endl;
  std::cout << DEFAULT;
  {
    char foo[] = "Apple";
    char bar[] = "apartment";

    std::cout << std::boolalpha;

    std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

    std::cout << "Using default comparison (operator<): ";
    std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9);
    std::cout << '\n';

    std::cout << "Using mycomp as comparison object: ";
    std::cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp);
    std::cout << '\n';
  }

  std::cout << GREEN;
  std::cout << "***********************************************************" << std::endl;
  std::cout << "*                            FT  TEST                     *" << std::endl;
  std::cout << "***********************************************************" << std::endl;
  std::cout << DEFAULT;
  {
    char foo[] = "Apple";
    char bar[] = "apartment";

    std::cout << std::boolalpha;

    std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

    std::cout << "Using default comparison (operator<): ";
    std::cout << ft::lexicographical_compare(foo, foo + 5, bar, bar + 9);
    std::cout << '\n';

    std::cout << "Using mycomp as comparison object: ";
    std::cout << ft::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp);
    std::cout << '\n';
  }

  return 0;
}
