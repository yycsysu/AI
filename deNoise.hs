import System.IO
import Data.List
main = do
  noiseString <- readFile "noise.txt"
  let numList = stringToInt noiseString
      newNumList = deNoise ([], numList) numList
      newNumList2 = deNoise ([], newNumList) newNumList
      newNoiseString = intToString newNumList2
  writeFile "noiseFreed.txt" newNoiseString
   
deNoise :: ([Int], [Int]) -> [Int] -> [Int]
deNoise (xs, []) ys = xs
deNoise (xs1, x:xs2) ys = deNoise (selectLowerEnergy (xs1, [x], xs2) ys) ys

selectLowerEnergy :: ([Int], [Int], [Int]) -> [Int] -> ([Int], [Int])
selectLowerEnergy (xs1, _, xs2) ys
  | e1 < e2 = (xs1++[1], xs2)
  | otherwise = (xs1++[-1], xs2)
  where e1 = evaluateEnergy s1 ys (1, 1, 2)
        e2 = evaluateEnergy s2 ys (1, 1, 2)
        s1 = xs1 ++ [1] ++ xs2
        s2 = xs1 ++ [-1] ++ xs2

evaluateEnergy :: [Int] -> [Int] -> (Int, Int, Int) -> Int
evaluateEnergy xs ys (h, beta, eta) = h * e1 - beta * e2 - eta * e3
  where e1 = sum xs
        matrix = toMatrix 64 xs
        e2 = (sumOfMatrixCol matrix) + (sumOfMatrixCol $ transpose matrix)
        e3 = sum $ zipWith (*) xs ys

toMatrix :: Int -> [Int] -> [[Int]]
toMatrix _ [] = []
toMatrix dim xs = y:(toMatrix dim ys)
         where (y,ys) = splitAt dim xs

sumOfMatrixCol :: [[Int]] -> Int
sumOfMatrixCol (xs:[]) = 0
sumOfMatrixCol (xs:ys:xss) = sumOfMatrixCol (ys:xss) + (sum $ zipWith (*) xs ys)


stringToInt :: String -> [Int]
stringToInt = map checkString
               where checkString '0' = -1
                     checkString '1' = 1
                     checkString _ = 0

intToString :: [Int] -> String
intToString = map checkInt
               where checkInt 1 = '1'
                     checkInt (-1) = '0'
                     checkInt _ = '2'
