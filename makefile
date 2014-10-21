all :: 
	g++ -o mandelbrot -std=c++11 -Wall -fopenmp -fcilkplus -O2 mandelbrot.cpp -ltbb -lSDL2 
