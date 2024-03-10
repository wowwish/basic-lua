-- In Lua, functions can handle an unknown number of input arguments
-- using the "..." operator.

function do_something(...)
	a, b, c = ...
	-- do something
end


function find_max(...)
	local n = 0
	-- using a table as an array to assign multiple input 
	-- keyword arguments of the function
	local arguments = {...}
	local max = arguments[1]
	for i,num in ipairs(arguments) do
		if num > max then
			max = num
		end
		n = n + 1
	end
	return n, max
end

----------------------------------------------------------
-- Ask for the max value of a list of integers
----------------------------------------------------------

local n, max = find_max(4, 2, -3, 8, 6, 3, 7, 2)

print("The maximum out of "..n.." values was "..max)
