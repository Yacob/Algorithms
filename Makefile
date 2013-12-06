PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

CXX = LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) g++

# compile cover by default
cover: cover.cpp brute.h util.h pruning.h cluster.h
	$(CXX) -O3 -std=c++11 cover.cpp -o cover
clean:
	rm cover
