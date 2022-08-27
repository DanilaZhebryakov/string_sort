
COMPILER=g++

all:
	$(COMPILER) -c main.cpp
	$(COMPILER) -c msort.cpp
	$(COMPILER) -c file_read.cpp
	$(COMPILER) -c String.cpp
	$(COMPILER) .\main.o .\file_read.o .\String.o .\msort.o
