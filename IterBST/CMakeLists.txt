cmake_minimum_required(VERSION 3.20)
project(IterBST)

set(CMAKE_CXX_STANDARD 14)

add_executable(IterBST main.cpp IterBST.h Iterator.h TreeNode.h BST.h testing.h)
