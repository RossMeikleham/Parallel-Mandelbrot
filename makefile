all :: 
	g++ -o mandelbrot -std=c++11 -Wall -fopenmp -O2 mandelbrot.cpp -ltbb -lSDL2 
