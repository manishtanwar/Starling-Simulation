#MakeFile
CXX = g++ -std=c++11
LFLAGS        = -m64
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES) -Wno-sign-compare -Wno-unused-result -Wno-unused-variable -Wno-parameter -L /lib64 	
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I.
LIBS          = -lglut -lGL -lGLU -lm

main: main.o boid.o properties.o
	$(CXX) $(LFLAGS) -o main main.o properties.o boid.o $(LIBS)

main.o: src/main.cpp include/boid.h include/properties.h
	$(CXX) $(CXXFLAGS) $(INCPATH) -c src/main.cpp

boid.o: src/boid.cpp include/boid.h
	$(CXX) $(CXXFLAGS) $(INCPATH) -c src/boid.cpp

properties.o: src/properties.cpp include/properties.h include/boid.h
	$(CXX) $(CXXFLAGS) $(INCPATH) -c src/properties.cpp

.PHONY: clean
clean: 
	$(RM) main *.o *~
