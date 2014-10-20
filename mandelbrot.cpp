#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/parallel_for_each.h"
#include "tbb/task_scheduler_init.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <SDL2/SDL.h>

using namespace std;


class Point
{
 public:
    double x_pos;
    double y_pos;
    double zx;
    double zy;

    Point(double x, double y) {
        x_pos = x;
        zx = x;
        y_pos = y;
        zy = y;
    }

    // zn+1 = zn^2 + c
    // Dealing with complex nos
    void next() {
        double old_zx = zx;
        zx = (zx * zx) - (zy * zy) + x_pos;
        zy = (2 * old_zx * zy) + y_pos;
    }
 
    double abs() {
        return sqrt ((zx * zx) + (zy * zy));    
    }      
    //Absolute value squared
    double absSq() {
        return (zx * zx) + (zy * zy);
    }
};


typedef vector< vector<Point> > Point2DVec;


/* Draw the mandelbrot graph from the given matrix of values 
   returns 0 if successful, 1 otherwise */
int draw_mandelbrot(Point2DVec &v2, int width, int height, int n) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
	    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	    return 1;
    }   
    
    SDL_Window *win = SDL_CreateWindow("Mandelbrot", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED);
     
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
           Point p = v2[i][j];
           double colorIntensity = 255 * ((n - log(log(p.abs() / log(4.0)))) / n);
           SDL_SetRenderDrawColor(renderer, 0, colorIntensity, 0, 0);
           SDL_Rect r;
           r.x = j;
           r.y = i;
           r.w = 1;
           r.h = 1;
           SDL_RenderFillRect(renderer, &r);
        }    
    }
    
    // Draw mandelbrot to screen
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

// Intel TBB version
void iter_mandelbrot_tbb(Point2DVec &v2) {
    tbb::parallel_for_each(v2.begin(), v2.end(), 
        [&](vector<Point> &v) {
            tbb::parallel_for_each(v.begin(), v.end(), 
                [&](Point &p){if (p.absSq() < 20.0) p.next();});
        });
}

void init_mt(const char* type) {
    if (!strcmp(type, "tbb")) {tbb::task_scheduler_init init;}
    else {throw invalid_argument("Supplied type is not valid");}    
}


Point2DVec createInitialMBrot(int width, int height) {
    Point2DVec mandel(height, vector<Point> (width, Point(0,0)));

    double incW = 4.0 / (width - 1);
    double incH = 4.0 / (height - 1);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
           double y =  2 - (i * incH);
           double x = -2 + (j * incW);
           mandel[i][j].y_pos = y;
           mandel[i][j].zy = y;
           mandel[i][j].x_pos = x;
           mandel[i][j].zx = x;
        }
    }
    return mandel;
}

int main(int argc, char *argv[]) {
    
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " type iterations width height" << std::endl;
        return 1;
    }

    const char* type = argv[1];
    int iterations = stoi(argv[2]);
    int width = stoi(argv[3]);
    int height = stoi(argv[4]);
    

init_mt(type);
Point2DVec mBrot =  createInitialMBrot(width, height);

for (int i = 0; i < iterations; i++) {
    iter_mandelbrot_tbb(mBrot);
}

return draw_mandelbrot(mBrot, width, height, iterations);
}
