#include "Vector.hpp"


// int main()
// {
//      ft::Vector<int> v;



//     v.push_back(1);
//     v.push_back(2);
//     v.push_back(25);
//     ft::Vector<int>::reverse_iterator it =   v.rbegin();
//     ft::Vector<int>::iterator it1 =   v.begin();


//     std::cout << *it << std::endl;
//     ++it ;
//     std::cout << *it << std::endl;
//     ++it ;
//     std::cout << *it << std::endl;
//     ++it ;
//     std::cout << *it << std::endl;

    
//     // v.print();
// }

#include <iostream>
//#include <vector>

int main ()
{
   // constructors used in the same order as described above:
  ft::Vector<int> first;                                // empty vector of ints
  ft::Vector<int> second (4,100);                       // four ints with value 100
  ft::Vector<int> third (second.begin(),second.end());  // iterating through second
  ft::Vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  ft::Vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (ft::Vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}