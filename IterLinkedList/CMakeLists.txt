cmake_minimum_required(VERSION 3.20)
project(IterLinkedList)

set(CMAKE_CXX_STANDARD 14)

add_executable(IterLinkedList main.cpp Iterator.h Node.h LinkedList.h LLIter.h)
