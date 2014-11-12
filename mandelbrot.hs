-- MandelBrot implementation in Haskell
-- Initial Code from Rosetta Code
import Data.Complex
import System.Environment
import Control.Parallel.Strategies

--initSDL :: IO Surface
--initSDL = do
--    SDL.init [SDL.InitEverything]
--    SDL.setVideoMode (floor imageWidth) (floor imageHeight) 32 []
--    SDL.setCaption "Mandelbrot" "Mandelbrot"-   screen <- getVideoSurface
--    white <- SDL.mapRGB (SDL.surfaceGetPixelFormat screen) 255 255 255
--    fillRect screen Nothing white >> SDL.flip screen
--    return screen
 
mandelbrot :: Num a => a -> Int -> a
mandelbrot a n = iterate (\z -> z^2 + a) 0 !! n
  
mbrot_seq :: Int -> Int -> Int -> [[Bool]]
mbrot_seq iter w h = [[magnitude (mandelbrot (x :+ y) iter) < 2 
                       | x <- [-2, (-2 + incW) ..   2]]
                       | y <- [ 2,  (2 - incH) ..  -2]]
 where incW = 4.0 / (fromIntegral w)
       incH = 4.0 / (fromIntegral h)



mbrot_par :: Int -> Int -> Int  -> [[Bool]]
mbrot_par iter w h = (mbrot_seq iter w h) `using` parList rdeepseq

main = do
    args <- getArgs
    if (length args < 3) 
        then print "Expected iterations, image width, and image height"    
        else do
            let nIter = read (args !! 0) :: Int
            let nWidth = read (args !! 1) :: Int
            let nHeight = read (args !! 2) :: Int
            print $ mbrot_seq nIter nWidth nHeight 

