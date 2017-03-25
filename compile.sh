#!/bin/bash
# macOS: install using brew install glfw3 --static
clang++ -Wall -std=c++14 -I/usr/local/include -L/usr/local/lib -lglfw3 -framework OpenGL -framework CoreVideo -framework IOKit -framework Cocoa OpenGL-Minimal.cpp
# ubuntu: install using sudo apt-get install libglfw3 libglfw3-dev
# g++ -Wall -std=c++14 -lGL -lGLFW OpenGL-Minimal.cpp
