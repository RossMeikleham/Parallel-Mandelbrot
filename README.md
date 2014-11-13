Parallel-Mandelbrot
===================

![MandelBrot](/images/mandel.png?raw=true)

Intel TBB, Cilk Plus, and OpenMP implementations of the Mandelbrot Series in C++.
As well as Strategy Parallel implementation of the Mandelbrot Series in Haskell.
Also VecPy implementation using Python.

Instructions
============

Required Libraries/Programs
===========================
##C++
- gcc
- Intel TBB
- Cilk Plus
- OpenMP (Should be included with gcc)
- SDL2

##Haskell
- GHC
- Cabal

##Python
- Python 3.4
- Pygame
- Numpy
- VecPy

Building
========
simply run the "make" command to build the C++ version. Run `cabal install` to install the Haskell version. 

Running
=======
##C++
usage `./mandelbrot type iterations width height`
- **type** is either "tbb", "cilk", "openmp", or "none" this specifies which implementation to run
- **iterations** are the number of iterations to run the algorithm for before drawing the result
- **width** is the number of horizontal pixels
- **height** is the number of vertical pixels

##Haskell
usage `Mandelbrot par/seq width height iterations`

##Python
usage `python3 mandelbrot.py`
