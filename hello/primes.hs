#!/usr/bin/env runhaskell

primes = 2 : [x | x <- [3,5..], y <- primes, rem x y /= 0]
main = print primes
