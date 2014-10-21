Parallel-Mandelbrot
===================

![MandelBrot](/images/mandel.png?raw=true)

Intel TBB, Cilk++, and OpenMP implementations of the Mandelbrot Series

Instructions
============

Required Libraries/Programs
===========================
- gcc
- Intel TBB
- Cilk Plus
- OpenMP (Should be included with gcc)
- SDL2

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

