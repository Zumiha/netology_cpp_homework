cmake_minimum_required(VERSION 3.20.0)
project(LinkedListLib VERSION 1.0)

set(SOURCE_LIB LinkedList.cpp)
set(SOURCE_HD LinkedList.h ListNode.h)
add_library(LLLIB SHARED ${SOURCE_LIB} ${SOURCE_HD})