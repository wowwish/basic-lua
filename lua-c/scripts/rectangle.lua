
-- Create a C struct representing a rectangle using the native
-- C function create_rectangle(). Here, Lua executes function
-- defined in the C program that links this Lua script
square = create_rectangle();
-- alter the values of the Struct created in C by calling another
-- native C function from the Lua environment
change_rectangle_size(square, 100, 100);
