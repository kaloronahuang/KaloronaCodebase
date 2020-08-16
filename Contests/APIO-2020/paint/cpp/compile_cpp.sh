#!/bin/bash

problem=paint

g++ -std=c++11 -o "${problem}" "grader.cpp" "${problem}.cpp" -g3 -lm
