// inserting into a Vector

#include <iostream>
#include "containers/Vector.hpp"
int main()
{
  // constructors used in the same order as described above:
  ft::Vector<int> myvector (3,100);
  ft::Vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

   myvector.insert (it,2,300);

  // // "it" no longer valid, get a new one:
  // it = myvector.begin();

  // ft::Vector<int> anothervector (2,400);
  // myvector.insert (it+2,anothervector.begin(),anothervector.end());

  // int myarray [] = { 501,502,503 };
  // myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';
  return 0;

}