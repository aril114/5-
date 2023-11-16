cmake_minimum_required(VERSION 3.20)
project(TreeNodeTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TreeNodeTest
        testing.h
        TreeNode.h
        TreeNodeTest.cpp)
