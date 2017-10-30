CC=g++
target=find_short_reads
CFLAGS += -std=c++11 -fopenmp -O3 -Wall -Wextra -pedantic
LDFLAGS += -fopenmp

$(target): $(target).o
	$(CC) -o $@ $(LDFLAGS) $<

%.o : %.cpp
	$(CC) -o $@ $(CFLAGS) $(includes) -c $<

clean:
	rm $(target) *.o
