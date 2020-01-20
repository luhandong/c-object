CC=gcc
CA=g++
obj=file
rely=file.cpp


all:$(obj)

$(obj):$(rely)
	$(CA) -std=gnu++0x $^ -o $@ 

clean:
	rm file
