-- local variables will only exist within the block in the file that they are declared
-- io is a standard library in lua
-- local file = io.open("sea-level.csv", "r")

-- command line arguments are accessed using arg[]
print(arg[0]) -- lua script name
local file = io.open(arg[1], "r")

-- in Lua object methods are accessed using the ':' operator
-- text contains the file content as a string
local text = file:read("all")

-- close file object
file:close()

print(text)
