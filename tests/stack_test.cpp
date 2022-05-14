#include "../stack/stack.hpp"
#include <stack>

#define GREEN "\e[1;32m"
#define DEFAULT "\e[0;37m"

int main()
{
    std::cout << GREEN;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "*                            STD TEST                     *" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << DEFAULT;
    {
        std::stack<int> mystack;

        mystack.push(13);
        mystack.push(12);
        mystack.push(2000);

        std::cout << "mystack.top() is now " << mystack.top() << '\n';

        mystack.top() -= 2;

        std::cout << "and now " << mystack.top() << '\n';
    }
    std::cout << GREEN;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "*                            FT  TEST                     *" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << DEFAULT;
    {
        ft::stack<int> mystack;

        mystack.push(13);
        mystack.push(12);
        mystack.push(2000);

        std::cout << "mystack.top() is now " << mystack.top() << '\n';

        mystack.top() -= 2;

        std::cout << "and now " << mystack.top() << '\n';
    }

    return 0;
}