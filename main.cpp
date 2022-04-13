// inserting into a Vector
#include <iostream>
#include "Vector.hpp"

int main ()
{
  ft::Vector<int> myVector (3,100);
  ft::Vector<int>::iterator it;

  it = myVector.begin();
  it = myVector.insert ( it , 200 );

  myVector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myVector.begin();

  ft::Vector<int> anotherVector (2,400);
  myVector.insert (it+2,anotherVector.begin(),anotherVector.end());

  int myarray [] = { 501,502,503 };
  myVector.insert (myVector.begin(), myarray, myarray+3);

  // std::cout << "myVector contains:";
  for (it=myVector.begin(); it<myVector.end(); it++)
    std::cout << ' ' << *it;
  // std::cout << '\n';

  return 0;
}