SRCS = main.cpp BoundedBuffer.cpp ProducerConsumer.cpp 
OBJS = main.o  BoundedBuffer.o ProducerConsumer.o
INCLUDE = BoundedBuffer.h ProducerConsumer.h 
CXX=g++
DEBUGFLAGS = -g  
PTHREADFLAG = -pthread

#LIBS=-lm
#OPTFLAGS= -O

CXXFLAGS =  $(DEBUGFLAGS) $(PTHREADFLAG)

all: depend prodcon  

prodcon : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS)  -o $@  $(LIBS)


clean:
	rm *.o prodcon

depend: Makefile
	makedepend -- -Y $(CXXFLAGS) -- $(SRCS)
# DO NOT DELETE

main.o: ProducerConsumer.h BoundedBuffer.h
BoundedBuffer.o: BoundedBuffer.h
ProducerConsumer.o: ProducerConsumer.h BoundedBuffer.h
