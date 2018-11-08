CXXFLAGS += --std=c++17
GTKFLAGS += `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

main: main.o mainwin.o store.o product.o java.o donut.o customer.o
	${CXX} ${CXXFLAGS} -o main main.o mainwin.o store.o product.o java.o donut.o customer.o ${GTKFLAGS}

main.o: main.cpp *.h
	${CXX} ${CXXFLAGS} -c main.cpp ${GTKFLAGS}
mainwin.o: main.cpp *.h
	${CXX} ${CXXFLAGS} -c mainwin.cpp ${GTKFLAGS}
store.o: store.cpp *.h
	${CXX} ${CXXFLAGS} -c store.cpp
product.o: product.cpp *.h
	${CXX} ${CXXFLAGS} -c product.cpp
java.o: java.cpp *.cpp
	${CXX} ${CXXFLAGS} -c java.cpp 
donut.o: donut.cpp *.h
	${CXX} ${CXXFLAGS} -c donut.cpp
customer.o: customer.cpp *.h
	${CXX} ${CXXFLAGS} -c customer.cpp

clean:
	rm -rf *.o main