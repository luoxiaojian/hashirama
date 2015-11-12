all: bfDemo

bfDemo: bfAllocator.cc bfDemo.cc taskset.cc allocation.cc
	g++ bfAllocator.cc bfDemo.cc taskset.cc allocation.cc -o bfDemo