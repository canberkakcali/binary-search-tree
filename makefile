test: test.cpp bstree.cpp
	g++ -std=c++11 -o test test.cpp bstree.cpp
debug:
	g++ -ggdb -std=c++11 -o test test.cpp bstree.cpp
