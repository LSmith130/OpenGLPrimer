#!/bin/bash

clang++ -Wall -std=c++14 -I/usr/local/include -L/usr/local/lib -lglfw3 -framework OpenGL -framework CoreVideo -framework IOKit -framework Cocoa OpenGL-Minimal.cpp
