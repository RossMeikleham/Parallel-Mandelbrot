-- MandelBrot implementation in Haskell
import Data.Complex
import System.Environment
import Control.Parallel.Strategies
import Criterion.Measurement
--import Graphics.UI.SDL 


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


draw_image :: Int -> Int -> [[Bool]] -> IO()
draw_image x y xs = print "to be implemented"

main = do
    initializeTime
    start_time <- getTime
    args <- getArgs
    if (length args < 4) 
        then print "Expected \"par/seq\"iterations, image width, and image height"    
        else do
            let nIter = read (args !! 1) :: Int
            let nWidth = read (args !! 2) :: Int
            let nHeight = read (args !! 3) :: Int
            case (args !! 0) of 
                "seq" -> print $ mbrot_seq nIter nWidth nHeight 
                "par" -> print $ mbrot_par nIter nWidth nHeight 
                otherwise -> print "expected first argument to be `par` or `seq`"
            end_time <- getTime
            print $ "Time elapsed : " ++ show (floor $ 10000 * (end_time - start_time)) ++ "ms"
               

