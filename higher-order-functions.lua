-- Functions are First Class values in Lua. This means that they can be 
-- treated like variables. You can return another function from a function
-- body, access the local variables of an inner function from the outer
-- function (closures) etc.

-- Higher-Order Functions simply take a function as argument or return
-- a function as result
-- When a function is written enclosed in another function, it has full
-- access to local variables from the enclosing function; this feature
-- is called "lexical scoping". Lexical scoping, plus first-class functions
-- make up a "Closure". Lua supports closures.
--

students = {
	{name = "Miles Davis", instrument = "trumpet"},
	{name = "John Coltrame", instrument = "saxophone"},
	{name = "Bill Evans", instrument = "piano"},
	{name = "Wynton Kelly", instrument = "piano"}
}

-- Here the table.sort() method is a Higher-Order Function as it takes an
-- (anonymous) function as argument which it used to apply the sorting on
-- the table items
s = table.sort(students, function (a,b)
	return a.name > b.name
end)

-- An implementation of the Closure Concept. Local variable defined in
-- funcA is also available inside the function funcB which itself is
-- defined within funcA
function func A(a)
	local c = 10
	function funcB(b)
		return a + b + c
	end
	return funcB
end
