#include "../utils/equal.hpp"
#include <iostream>  // std::cout
#include <algorithm> // std::equal
#include <vector>    // std::vector
#include "../vector/vector.hpp"

#define GREEN "\e[1;32m"
#define DEFAULT "\e[0;37m"


bool mypredicate(int i, int j)
{
  return (i == j);
}

int main()
{
  std::cout << GREEN;
  std::cout << "***********************************************************" << std::endl;
  std::cout << "*                            STD TEST                     *" << std::endl;
  std::cout << "***********************************************************" << std::endl;
  std::cout << DEFAULT;
  {

    int myints[] = {20, 40, 60, 80, 100};          //   myints: 20 40 60 80 100
    std::vector<int> myvector(myints, myints + 5); // myvector: 20 40 60 80 100

    // using default comparison:
    if (std::equal(myvector.begin(), myvector.end(), myints))
      std::cout << "The contents of both sequences are equal.\n";
    else
      std::cout << "The contents of both sequences differ.\n";

    myvector[3] = 81; // myvector: 20 40 60 81 100

    // using predicate comparison:
    if (std::equal(myvector.begin(), myvector.end(), myints, mypredicate))
      std::cout << "The contents of both sequences are equal.\n";
    else
      std::cout << "The contents of both sequences differ.\n";
  }
  std::cout << GREEN;
  std::cout << "***********************************************************" << std::endl;
  std::cout << "*                            FT  TEST                     *" << std::endl;
  std::cout << "***********************************************************" << std::endl;
  std::cout << DEFAULT;
  {
    int myints[] = {20, 40, 60, 80, 100};         //   myints: 20 40 60 80 100
    ft::vector<int> myvector(myints, myints + 5); // myvector: 20 40 60 80 100

    // using default comparison:
    if (ft::equal(myvector.begin(), myvector.end(), myints))
      std::cout << "The contents of both sequences are equal.\n";
    else
      std::cout << "The contents of both sequences differ.\n";

    myvector[3] = 81; // myvector: 20 40 60 81 100

    // using predicate comparison:
    if (ft::equal(myvector.begin(), myvector.end(), myints, mypredicate))
      std::cout << "The contents of both sequences are equal.\n";
    else
      std::cout << "The contents of both sequences differ.\n";
  }

  return 0;
}