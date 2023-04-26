-- DESCENDING ORDER OF OPERATOR PRECEDENCE:
-- () PARENTHESES

-- ^ EXPONENTS

-- * MULTIPLICATION

-- / DIVISION

-- + ADDITION

-- - SUBTRACTION


-- LUA DOES NOT HAVE INCREMENT (++) OR DECREMENT (--) OPERATORS OR SHORTCUT ARITHMETIC OPERATORS (+= -= /= *=)
------------------------------------------
-- Exercise:
------------------------------------------
-- Write a Lua program that receives
-- the value of the name and salary
-- of an employee.
-- The program should calculate and
-- display the new salary increased
-- by 15%.
------------------------------------------

name = "Miles Davis"
salary = 500000.00

------------------------------------------
-- TODO: Calculate the new_salary
------------------------------------------
new_salary = salary + salary * (15 / 100)

print("The new salary is " .. new_salary)
