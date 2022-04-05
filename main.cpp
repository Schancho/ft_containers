#include "Vector.hpp"


int main()
{
     ft::Vector<int> v(4);



    v.push_back(1);
    v.push_back(2);
    ft::Vector<int>::const_iterator it =   v.begin();
    ft::Vector<int>::iterator it1 =   v.begin();


    std::cout << *it << std::endl;
    ++it ;
    std::cout << *it << std::endl;

    // v.print();
}