CXX = g++
CXXFLAGS= -Wall -Wextra -pedantic -std=c++14 -o3
LDLIBS= -pthread -lrt -ltbb

all:

clang: CXX = clang++
clang: all
