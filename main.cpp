// inserting into a Vector

#include <iostream>

#include "containers/map/avl.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include "containers/map/map.hpp"

#include <iostream>
#include <map>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
   ft::map<char,int> mymap;

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  // show content:
  ft::map<char,int>::reverse_iterator rit;
  for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
  {
    std::cout << rit->first << " => " << rit->second << '\n';
    std::cout << "before segfault"<< std::endl;

  }

  return 0;
}