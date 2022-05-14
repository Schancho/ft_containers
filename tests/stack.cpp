#include "../containers/stack/stack.hpp"
#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <vector>


#define BLUE "\e[0;34m"
#define red "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"


int main()
{

std::cout << YELLOW << "\t===================================test construct===================================" << RESET << std::endl;

{
	{
		std::cout << "std::stack\n";
		std::deque<int> mydeque (3,100);          // deque with 3 elements
		std::vector<int> myvector (2,200);        // vector with 2 elements

		std::stack<int> first;                    // empty stack
		std::stack<int> second (mydeque);         // stack initialized to copy of deque

		std::stack<int,std::vector<int> > third;  // empty stack using vector
		std::stack<int,std::vector<int> > fourth (myvector);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
		std::cout << "size of fourth: " << fourth.size() << '\n';
	}
	{
		std::cout << "ft::stack\n";
		std::deque<int> mydeque (3,100);          // deque with 3 elements
		ft::vector<int> myvector (2,200);        // vector with 2 elements

		ft::stack<int> first;                    // empty stack
		ft::stack<int, std::deque<int> > second (mydeque);         // stack initialized to copy of deque

		ft::stack<int,ft::vector<int> > third;  // empty stack using vector
		ft::stack<int,ft::vector<int> > fourth (myvector);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
		std::cout << "size of fourth: " << fourth.size() << '\n';
	}
}


std::cout << YELLOW << "\t===================================test empty===================================" << RESET << std::endl;

{
	{
		std::cout << "std::stack\n";
  		std::stack<int> mystack;
  		int sum (0);

  		for (int i=1;i<=10;i++) mystack.push(i);

  		while (!mystack.empty())
  		{
  		   sum += mystack.top();
  		   mystack.pop();
  		}

  		std::cout << "total: " << sum << '\n';
	}

	{
		std::cout << "ft::stack\n";
  		ft::stack<int> mystack;
  		int sum (0);

  		for (int i=1;i<=10;i++) mystack.push(i);

  		while (!mystack.empty())
  		{
     		sum += mystack.top();
     		mystack.pop();
  		}

 		std::cout << "total: " << sum << '\n';
	}

}

std::cout << YELLOW << "\t===================================test top===================================" << RESET << std::endl;


{
	{
		std::cout << "std::stack\n";
  		std::stack<int> mystack;

  		for (int i=0; i<5; ++i) mystack.push(i);

  		std::cout << "Popping out elements...";
  		while (!mystack.empty())
  		{
  		   std::cout << ' ' << mystack.top();
  		   mystack.pop();
  		}
  		std::cout << '\n';
	}

	{
		std::cout << "ft::stack\n";
  		ft::stack<int> mystack;

  		for (int i=0; i<5; ++i) mystack.push(i);

  		std::cout << "Popping out elements...";
  		while (!mystack.empty())
  		{
  		   std::cout << ' ' << mystack.top();
  		   mystack.pop();
  		}
  		std::cout << '\n';
	}
}



std::cout << YELLOW << "\t===================================test push===================================" << RESET << std::endl;


{
	{
		std::cout << "std::stack\n";
		std::stack<int> mystack;

  		for (int i=0; i<5; ++i) mystack.push(i);

  		std::cout << "Popping out elements...";
  		while (!mystack.empty())
  		{
  		   std::cout << ' ' << mystack.top();
  		   mystack.pop();
  		}
  		std::cout << '\n';
	}

	{
		std::cout << "ft::stack\n";
		ft::stack<int> mystack;

  		for (int i=0; i<5; ++i) mystack.push(i);

  		std::cout << "Popping out elements...";
  		while (!mystack.empty())
  		{
  		   std::cout << ' ' << mystack.top();
  		   mystack.pop();
  		}
  		std::cout << '\n';
	}
}
std::cout << YELLOW << "\t===================================test size===================================" << RESET << std::endl;

{
	{
		std::cout << "std::stack\n";
  		std::stack<int> myints;
  		std::cout << "0. size: " << myints.size() << '\n';

  		for (int i=0; i<5; i++) myints.push(i);
  		std::cout << "1. size: " << myints.size() << '\n';

  		myints.pop();
  		std::cout << "2. size: " << myints.size() << '\n';
	}
	{
		std::cout << "ft::stack\n";
  		ft::stack<int> myints;
  		std::cout << "0. size: " << myints.size() << '\n';

  		for (int i=0; i<5; i++) myints.push(i);
  		std::cout << "1. size: " << myints.size() << '\n';

  		myints.pop();
  		std::cout << "2. size: " << myints.size() << '\n';
	}
}

std::cout << YELLOW << "\t===================================test top===================================" << RESET << std::endl;


{
	{
		std::cout << "std::stack\n";
  		std::stack<int> mystack;

  		mystack.push(10);
  		mystack.push(20);

  		mystack.top() -= 5;

  		std::cout << "mystack.top() is now " << mystack.top() << '\n';

	}
	{
		std::cout << "ft::stack\n";
		ft::vector<int> myvector;
  		ft::stack<int> mystack;

  		mystack.push(10);
  		mystack.push(20);

  		mystack.top() -= 5;

  		std::cout << "mystack.top() is now " << mystack.top() << '\n';
	}
}

}