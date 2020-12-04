SRCS = main.cpp console.cpp page.cpp perform.cpp user.cpp
HEADER = console.hpp page.hpp perform.hpp user.hpp
OBJF = $(SRCS:.c=.o)

main.out :
	g++ *.cpp -o main.out -std=c++11 -lpthread
	rm -f *.o

clean :
	rm -f *.out *.o
