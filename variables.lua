-- Lua is case-sensitive with respect to variable naming.
-- Hence, Employee_name and employee_name will be treated as two different variables
-- Lua is DYNAMICALLY TYPED.
-- There are seven types of variables in lua:
-- 1. nil
-- 2. number
-- 3. string
-- 4. function
-- 5. CFunction
-- 6. userdata
-- 7. table


print("Examples of variables:")

level = 1
score = 0
num_lives = 5

player1_name = "Leeroy Jenkins"
player2_name = "Gustavo Pezzi"

print(type(nil))
print(type(score))
print(type(player1_name))


-- arithmetic operators are supported in lua
salary = 25 / 2 -- implicit floating point conversion
int_salary = 25 // 2 -- forced integer division equivalent to math.floor(25 / 2)
print("The value of salary is "..salary) --The ".." operator is used for variable interpolation with strings
print("The value of name is ".. player1_name) --The ".." operator is used for variable interpolation with strings
print("25 // 2 is " .. int_salary) --The ".." operator is used for variable interpolation with strings



-- uninitialized variables will have nil value and they cannot be interpolated with strings
print(uninitialized_var)
