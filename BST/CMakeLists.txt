cmake_minimum_required(VERSION 3.20)
project(BST)

set(CMAKE_CXX_STANDARD 14)

add_executable(BST main.cpp BST.h testing.h TreeNode.h)
