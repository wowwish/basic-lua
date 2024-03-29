function pythagoras(a, b)
	-- calling the native C function from within Lua
	result_squared = native_pythagoras(a, b);
	return result_squared;
end
