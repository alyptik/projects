#!/usr/bin/awk -f

# A fizzbuzz in pure awk. A! W! K! !!

  #:[ 1 ]:----------------=
   # Fizzbuzz
    #--

    ### Ok dumbass % is the rhs of 0.0 after /
    ### I.e. (10%100 == 10) == (10/100 == 0.10)
    BEGIN {
      for ( i=1; i <= 100; i++ ) {
        if ( i%15 == 0 ) {
        ###   ^ Here you fuck!
          print i" - FizzBuzz"
        } else {
          if ( i%3 == 0 ) {
            print i" - Fizz"
          } else {
            if ( i%5 == 0 ) {
              print i" - Buzz"
                } else {
                  print i" - ["i/100"]"
            }
          }
        }
      }
    }





