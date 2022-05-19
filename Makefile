COMPILER = c++ -std=c++98 #-g #-fsanitize=address 
FLAGS = -Wall -Wextra -Werror 

vector:
	$(COMPILER) $(FLAGS) tests/vector.cpp -o vector

map:
	$(COMPILER) $(FLAGS) tests/map.cpp -o map

stack:
	$(COMPILER) $(FLAGS) tests/stack.cpp -o stack

equals:
	$(COMPILER) $(FLAGS) tests/equal_test.cpp -o equals

lexicographical:
	$(COMPILER) $(FLAGS) tests/lexicographical_compare_test.cpp -o lexicographical

make_pair:
	$(COMPILER) $(FLAGS) tests/make_pair_test.cpp -o make_pair

stack_test:
	$(COMPILER) $(FLAGS) tests/stack_test.cpp -o stack_test
all: vector map stack equals lexicographical make_pair stack_test
	@echo "Done!"

re:	fclean all

fclean:
	@echo "Cleaning..."
	rm -f vector map stack
	@echo "Done!"

