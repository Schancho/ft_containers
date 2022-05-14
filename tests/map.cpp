#include <iostream>

#include "../containers/map/map.hpp"

#include <map>
#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>


#define BLUE "\e[0;34m"
#define red "\e[0;31m"
// #define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"



template <typename Iter1>
void print_elemts(Iter1 first1, Iter1 last1)
{
	for (; (first1 != last1) ; ++first1)
		;//std::cout << (*first1).first << ' ';
	//std::cout << std::endl;
}


bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main() {



   ft::map<char,int> mymap;
  ft::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('f');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;

 
}