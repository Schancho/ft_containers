COMPILER = c++ -std=c++98
FLAGS = -Wall -Wextra -Werror 

vector:
	$(COMPILER) $(FLAGS) tests/vector.cpp -o vector

map:
	$(COMPILER) $(FLAGS) tests/map.cpp -o map

stack:
	$(COMPILER) $(FLAGS) tests/stack.cpp -o stack

all: vector map stack
	@echo "Done!"

re:	fclean all

fclean:
	@echo "Cleaning..."
	rm -f vector map stack
	@echo "Done!"

