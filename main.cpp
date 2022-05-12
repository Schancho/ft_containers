// inserting into a Vector

#include <iostream>

#include "containers/map/avl.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include "containers/map/map.hpp"
#include <vector>
#include <iostream>
#include <map>
#include "containers/vector/Vector.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

    ft::Vector<int> lower_bound_test(std::map<int, int> mp) {
    ft::Vector<int> v;
    std::map<int, int > mp2;
    mp.insert(std::make_pair(10, 10));
    mp2.insert(std::make_pair(10, 10));
    
    mp.insert(std::make_pair(20, 20));
    mp.insert(std::make_pair(30, 30));
    mp.insert(std::make_pair(40, 40));
    mp.insert(std::make_pair(50, 50));
    mp.insert(std::make_pair(60, 60));
    mp2.insert(std::make_pair(20, 20));
    mp2.insert(std::make_pair(30, 30));
    mp2.insert(std::make_pair(40, 40));
    mp2.insert(std::make_pair(50, 50));
    mp2.insert(std::make_pair(60, 60));
    std::map<int, int>::iterator it;
    
        it = mp.lower_bound(10);
        v.push_back(it->first);
   
   
        it = mp2.lower_bound(30);
        v.push_back(it->first);
   
    std::map<int, int> mp3;
    for (int i = 0, j = 0; i < 50 * 10; ++i, ++j) {
        mp3.insert(std::make_pair(i, j));
    }

    mp3.lower_bound(49 * 10);

    return v;
}

int main ()
{
  std::map<int,int> mymap;
 ft::Vector<int> v;
  v = lower_bound_test(mymap);
// std::map<char,int> mymap;
//   std::map<char,int>::iterator itlow,itup;

//  // mymap['a']=20;
//   mymap['b']=40;
//   mymap['c']=60;
//   mymap['d']=80;
//   mymap['e']=100;

//   itlow=mymap.lower_bound ('a');  // itlow points to b
//   itup=mymap.upper_bound ('d');   // itup points to e (not d!)

//   //mymap.erase(itlow,itup);        // erases [itlow,itup)

//   // print content:
//   for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';

  return 0;
}