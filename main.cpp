// inserting into a Vector

#include <iostream>

#include "containers/map/avl.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <random>


int main() {
  std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist (0,1);
int random_number = dist(mt);
  ft::Avl<int, int> Tree;
     time_t t;
   srand((unsigned) time(&t));

  int tab[]= {199,
397,464,
329,
363,
443,
412,
779,
4,
455,
384};
  Tree.insert(ft::make_pair(1, 1));

  for (int i = 0; i <= 10; i++) {
    int num = rand() % 1000;
    // std::cerr <<  << std::endl;
      Tree.insert(ft::make_pair<int , int>(num, 1));
      tab[i] = num;
  }
  Tree.print();

  for (int i = 0; i <= 1; i++) {
    int num = rand() % 1000;
    // std::cerr <<  << std::endl;
      Tree.delete_node(tab[i]);
  }

//   Tree.insert(ft::make_pair<int , int>(1, 1));
//   Tree.insert(ft::make_pair<int , int>(2, 1));
//   Tree.insert(ft::make_pair<int , int>(3, 1));
//   Tree.insert(ft::make_pair<int , int>(4, 1));
//   Tree.insert(ft::make_pair<int , int>(5, 1));
// Tree.insert(ft::make_pair<int , int>(1, 1));
// Tree.insert(ft::make_pair<int , int>(2, 1));
// Tree.insert(ft::make_pair<int , int>(3, 1));
// Tree.insert(ft::make_pair<int , int>(4, 1));
// Tree.insert(ft::make_pair<int , int>(5, 1));
Tree.print();

// Tree.delete_node(4);
// Tree.print();
// Tree.insert(ft::make_pair<int , int>(4, 1));
// Tree.print();
// Tree.delete_node(tab[i]);

   

  //Tree.printTree(root, "", true);
  //root = Tree.remove(root, 13);
  std::cout << "After deleting " << std::endl;
  //Tree.printTree(root, "", true);
}