-- INPUT OPTIONS:
-----------------

--txt = io.read("a") 		--> this reads all input from the stdin (ie. keyboard or whatever), including linebreaks. Can also be read.io("all")
--txt = io.read("*a") 		--> same as above, also reads all input from stdin
--txt = io.read("*n") 		--> this reads a number. spaces and linebreaks are interpreted as delimiters for two inputs
--txt = io.read("*l") 		--> read an entire line from stdin (this is the default when io.read() has no params). "\n" is interpreted as delimiter 
--for next line
--txt = io.read(4) 		--> this reads 4 characters from stdin. Remember that spaces, linebreaks are also characters.
--a, b = io.read(4, 6) 		--> reads 4 and 6 characters and assign them to a and b.
--a, b = io.read("*n", "*n") 	--> reads two numbers and assigns them to a and b. space or newline can be used to delimit the two numbers in input.


--print("txt: "..txt)
--print("(a: "..a..", b: "..b..")")



-- A better way to read numbers from user input
local num = tonumber(io.read())
print("Entered number: "..num)
