Parallel-Mandelbrot
===================

![MandelBrot](/images/mandel.png?raw=true)

Intell TBB, Cilk++, and OpenMP implementations of the Mandelbrot Series

Instructions
============

Required Libraries/Programs
===========================
- Intel TBB
- Cilk++
- OpenMP
- SDL2
- gcc

Building
========
simply run the "make" command to build

Running
=======
usage `./mandelbrot type iterations width height`
- **type** is either "tbb", "cilk", or "openmp", this specifies which implementation to run
- **iterations** are the number of iterations to run the algorithm for before drawing the result
- **width** is the number of horizontal pixels
- **height** is the number of vertical pixels

