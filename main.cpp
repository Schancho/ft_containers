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
#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
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
  std::vector<std::string> v1(10, "string1");
  std::vector<std::string> v2(10, "string2");
  v1 = v2;
  /*-----------------------------------------------------*/
  /*------------------ ft::vectors ---------------------*/
  ft::Vector<std::string> ft_v1(10, "string1");
  ft::Vector<std::string> ft_v2(10, "string2");
  ft_v1 = ft_v2;
  /*----------------------------------------------------*/
  /*------------------ strings to store the results ----*/
  std::string res, ft_res;
  /*----------------------------------------------------*/
  for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
      res += *it;

  for (ft::Vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;


  return 0;
}