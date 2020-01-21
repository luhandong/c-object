CC=gcc
CA=g++

relay=Service.cpp ../Sock.cpp
object=svr

all:$(object)

$(object):$(relay)
	$(CA) -std=gnu++0x $^ -o $@

clean:
	rm svr
