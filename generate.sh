#!/bin/sh

g++ -std=c++14 src/main.cpp -I./src/include/ -o raytracer

./raytracer > output.ppm