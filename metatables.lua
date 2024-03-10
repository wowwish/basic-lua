-- metatables in lua provide operator overloading for tables
-- they are in-built meta methods in metatables, similar to dunder methods of python, that can be used to describe the behaviour of tables

-- METAMETHODS:
-- __index() is a metatamethod that facilitates inheritance from other tables. Functions can also
-- be used instead of tables to return values for fields not present in the original table.
-- __newindex(): is a metamethod used to update keys or values present in the table. When you 
-- assign a value to an absent index in a table, the interpreter looks for a __newindex metamethod.
-- If there is one, the interpreter calls it instead of making the assignment. Like __index, if the
-- metamethod is a table, the interpreter does the assignment in that table, instead of in the
-- original one. 
-- __add() is an arithmetic metamethod for how two objects behave with the "+" operator
-- __sub() is an arithmetic metamethod for how two objects behave with the "-" operator
-- __mul() is an arithmetic metamethod for how two objects behave with the "*" operator
-- __eq() is a relational metamethod for checking equality of objects
-- __lt() is a relational metamethod for the "<" operator
-- __le() is a relational metamethod for the "<=" operator
-- __concat() is an arithmetic metamethod for how two objects behave with the ".." operator
-- __call() is a metamethod that lets a table to be used as a function (also called as functor or functable) 
-- __tostring() is a metamethod for representing objects as strings in display
