#!/bin/bash

problem=fun

g++ -std=c++11 -o "${problem}" "grader.cpp" "${problem}.cpp" -O2 -lm
