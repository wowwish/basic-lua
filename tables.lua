-- Tables are THE fundamental data structure in lua that can be used as both arrays and hash maps.
-- A Table in lua is also an Object in the sense of Object-Oriented Programming as it can contain both
-- literals and methods.

-- using a table as an array
a = {34, 22, 12, 9, -34, 55, 89, 1675, 12}

print(a[1])
print(a[3])

-- using a table as a hash map. wrapping the keys with [""] is not strictly neccessary if your keys donot have a space character in them
quiz_scores = {["miles"] = 88.7, ["john"] = 99.4, ["bill"] = 67.7, ["aretha"] = 45.8, ["nina"] = 88.5}
quiz_scores = {miles = 88.7, john = 99.4, bill = 67.7, aretha = 45.8, nina = 88.5}

-- fetch values from the table.
print(quiz_scores["aretha"])

-- shortcut way to access values using key
print(quiz_scores.aretha)

-- add new entries to the table
quiz_scores["oscar"] = 99.4


-- loop through all the key-value pairs in the table. pairs() returns key-value pairs without following their order in the table.
-- Another function ipairs() returns index-value pairs in the same order as in the table.
for k, v in pairs(quiz_scores) do
	print("Inside the key "..k.." we have the value "..v)
end


game_prices = {
  599.99,
  455.23,
  600.00,
  190.00
}

-- Loop all in order over the index-value pairs in the table
for i,v in ipairs(game_prices) do
  print("In the index "..i.." we have the value "..v)
end


-- NOTE: ipairs() will ignore all entries that have non-numeric index in the table. It will only return entries before the first non-numeric key. 
my_values = {
  [1] = "one",
  [2] = "two",
  [3] = "three",
  ["four"] = "four",
  [5] = "five"
}
 
-- Loop over all index-value pairs.
for i,v in ipairs(my_values) do
  print("In the index "..i.." we have the value "..v)
end


-- NOTE: Tables can be nested, one inside another
prince_codes = {
	{ Page = 1, Line = 2, Word = 2, Code = "W"},
	{ Page = 1, Line = 5, Word = 4, Code = "O"},
	{ Page = 1, Line = 8, Word = 6, Code = "E"},
	{ Page = 1, Line = 10, Word = 6, Code = "S"},
	{ Page = 2, Line = 2, Word = 5, Code = "P"},
	{ Page = 2, Line = 3, Word = 8, Code = "B"}
}


-- Tables in lua can also have functions as values (act as a class)
local vector3d = {}
-- metatable for vector3d (objects of vector3d)
local meta = {}

-- A method similar to a constructor for creating a new table instance
function vector3d.new(x, y, z)
	local v = {x = x, y = y, z = z}
	-- set the metatable for the newly created table (object)
	setmetatable(v, meta) -- inject the methods and attributes of the class using pre-built metatable
	return v
end


function vector3d.add(v1, v2)
	return vector3d.new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z)
end

function vector3d.tostring(v)
	return "("..v.x..","..v.y..","..v.z..")"
end

-- setting a metamethod for the table using its metatable
-- The metamethod is set to refer to an user-defined function
-- Notice how methods are injected into the metatable even after the object creation step and it works seamlessly
-- due to the usage of references instead of actual copying of data
meta.__add = vector3d.add
meta.__tostring = vector3d.tostring

local position = vector3d.new(5.0, 5.0, 5.0)
local velocity = vector3d.new(10.0, -3.5, 0.0)

-- Note that the functionality required must be injected into the metatable during metatable instance creation
-- for it to be accessible in the newly created instance (object)
local result = velocity + position
print("Result vector is: "..result)
