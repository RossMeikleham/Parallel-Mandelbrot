import pygame, sys, getopt
from pygame import *
from numpy import arange
from time import sleep
from vecpy.runtime import *
from vecpy.compiler_constants import *

def mandelbrot(num, iterations):
    z = 0
    for i in range (0, iterations + 1):
        z = z**2 + num
        if abs(z) > 2: 
            return False
    return True


def mbrot_seq(iterations, width, height):
    incW = 4.0 / width
    incH = 4.0 / height
    return [[mandelbrot(complex(x, y), iterations) 
                for x in arange(-2.0, 2.0, incW)]
             for y in arange(2.0, -2.0, -incH)] 

#Mandelbrot function to be compiled as a Kernel
def mandelbrot2(x, iy, iterations, res):
    zr= 0 
    zi = 0
    while iterations > 0 and res == 1:
        old_zr = zr  
        zr = (zr * zr) - (zi * zi) + x
        zi = (2 * zi * old_zr) + iy 
        if abs(math.sqrt((zr * zr) + (zi * zi))) > 4:
            res = 0
        else:
            res = 1
        iterations -= 1
    

# Generate Kernel
vectorize(mandelbrot2, Options(Architecture.generic, DataType.float))
from vecpy_mandelbrot2 import mandelbrot2
    
def mbrot_par(iterations, width, height):
    incW = 4.0 / width
    incH = 4.0 / height
    co_ords = [[(x, y) for x in arange(-2.0, 2.0, incW)]
                for y in arange(2.0, -2.0, -incH)]
    arraysX = get_arrays(height, 'f', width)
    arraysY = get_arrays(height, 'f', width)
    arraysN = get_arrays(height, 'f', width)
    arraysR = get_arrays(height, "f", width)
    for y in range(0, height):
        for x in range(0, width):
            arraysX[y][x] = co_ords[x][y][0]
            arraysY[y][x] = co_ords[x][y][1]
            arraysN[y][x] = iterations
            arraysR[y][x] = 1

    for y in range(0, height):
        mandelbrot2(arraysX[y], arraysY[y], arraysN[y], arraysR[y])
    
    results = [[arraysR[x][y] != 0.0 for x in range(width)] 
                for y in range(height)] 

    return results 

def main():
    width = 500
    height = 500
    iterations = 40
    pygame.init()
    mbrot = mbrot_par(iterations, width, height)

    display = pygame.display.set_mode((width, height),0,32)
    green = (0,255,0)
    black = (0,0,0)

    for y in range(0, height):
        for x in range(0, width):
            if mbrot[y][x]:
              pos = (x, y) 
              pygame.draw.line(display, green, pos, pos) 

    pygame.display.update()
    sleep(5)
    pygame.quit()

main()                
