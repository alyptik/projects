-- Potatos for Bools just because

-- we create a new datatype analagous to Bool
--   Bool    True   | False
data Tater = Potato | NoPotato

-- to use boolean operators we need to make Tater
-- an instance of the Eq typeclass

-- The type of the == (equality) operator is:
-- (==) :: Eq a => a -> a -> Bool

-- So without writing our own new Eq typeclass, we will get bools out
-- but can use Potatos where the a's go in that type

instance Eq Tater where
  Potato == Potato = True
  NoPotato == NoPotato = True
  Potato == NoPotato = False
  NoPotato == Potato = False

-- Now our Tater bool type will work with any function asking for an Eq
