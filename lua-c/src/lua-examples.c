// Use the function defined in scripts/factorial.lua


#include <stdio.h>
// include headers from Lua
#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"


// Any C function that is going to be executed through
// Lua needs to take the Lua State pointer as its
// only input argument. All arguments have to be taken out
// from the shared stack and the result values should be pushed to
// to stack. The C function executed by Lua should be designed to
// return the number of result values that it pushed into the shared
// stack.
int native_pythagoras(lua_State* L) {
	// This function receives the arguments from the shared
	// Since the stack follows LIFO order, we take the second
	// argument from the top first and then the first argument.
	// We use indices -1 and -2 because the lua_tonumber() function
	// only peaks into the given index of the stack and does not pop
	// the stack.
	lua_Number b = lua_tonumber(L, -1);
	lua_Number a = lua_tonumber(L, -2);
	lua_Number result = (a * a) + (b * b);
	// Instead of returning the result like a normal function, we push
	// the result to the top of the shared stack.
	lua_pushnumber(L, result);
	// The function should instead return the actual number of values
	// that it pushed into the shared stack as result
	return 1; 
}


void lua_example_dofile(void) {
 	// To work with Lua in C, you have to create a Lua state pointer
	// This also initializes a shared stack data structure between 
	// Lua and C through which functions and variables can be shared
	lua_State* L = luaL_newstate();
	
	// This allows acces to all the standard libraries of Lua to the
	// C lua state pointer 'L' that we have created
	luaL_openlibs(L);
	
	// Send file path for the Lua function import from a Lua script
	// Here, we want to parse,interpret and execute the lines of code
	// in our 'factorial.lua' script.
	// NOTE: The lua script is loosely coupled with the compiled C code
	// binary file and hence when any modification is made to the lua
	// script associated with the lua state pointer, no re-compilation
	// of the C source code is required!
	luaL_dofile(L, "./scripts/factorial.lua");

	// Once the Lua code is utilized and executed, the Lua state
	// has to be cleared
	lua_close(L);
		
}

// NOTE: it is bad practice to create serveral lua states, but we do
// so in every example function here just for improving learning

// This example function is to get a variable declared in Lua code
// into the context of this C program
void lua_example_getvar(void) {
	// Create the Lua state pointer pointing to the shared stack
	lua_State* L = luaL_newstate();
	// Execute a string of Lua code using the luaL_dostring()
	// function with the Lua state pointer
	luaL_dostring(L, "some_var = 486");
	// After executing Lua code that assigns a value to a global
	// variable, we can then get back the declared variable into C
	// using the lua_getglobal() function
	lua_getglobal(L, "some_var");
	// The communication between Lua and C is done using a stack.
	// Here, we are extracting the last index of the stack and
	// converting it to a number and assigning it to a C variable
	// 'some_var_in_c'. Lua grows this stack and C pops or peaks
	// from this stack. Remember that a stack grows vertically
	// from bottom to top Right now, we have only one variable in the
	// stack, and the -1 index removes the topmost value in the stack
	// which is that value we just added into the stack using
	// lua_getglobal()
	lua_Number some_var_in_c = lua_tonumber(L, -1);
	// NOTE: explicit type casting (casting to integer in this case) is
	// required for any variable taken from the shared stack L
	printf("The value of some_var_in_c inside C is: %d\n", (int)some_var_in_c);
	lua_close(L);
}

void lua_example_stack(void) {
	// Creating the Lua state pointer
	lua_State* L = luaL_newstate();
	// push numbers into the shared stack between Lua and C
	lua_pushnumber(L, 286); // stack[1] or stack[-3]
	lua_pushnumber(L, 386); // stack[2] or stack[-2]
	lua_pushnumber(L, 486); // stack[3] or stack[-1]
	// declare a lua numeric value holder in C
	lua_Number element;
	// peaking the topmost value from the shared stack
	element = lua_tonumber(L, -1);
	printf("The last added element in index 2 of the stack is %d\n", (int)element);
	
	// remove the number 386 at position 2 of the stack
	lua_remove(L, 2);
	element = lua_tonumber(L, 2); // update the element variable
	printf("Position 2 of the stack is now: %d", (int)element);

	// Closing the Lua state
	lua_close(L);
}

void example_call_lua_function(void) {
	lua_State* L = luaL_newstate();
	// loosely couple Lua script file in given path to the
	// current stack shared between Lua and C
	// If the function call errors out, Then Lua will place
	// an error message into the shared Stack which can be
	// forwarded as error from C
	if (luaL_dofile(L, "./scripts/pythagoras.lua") != LUA_OK) {
		// peaking at the shared Stack to refer the error
		// message given by Lua and then forwarding that 
		// error through C using luaL_error()
		luaL_error(L, "Error: %s\n", lua_tostring(L, -1));		
	}
	// get the function 'pythagoras' declared within the
	// script file that was attached to the Lua state pointer
	// and push it to the top of the shared stack.
	// functions also behave like variables in Lua and this
	// allows us to share them with this C program
	lua_getglobal(L, "pythagoras");
	// There are several C functions to test the Lua variables
	// obtained from the shared Stack. These include:
	// 	* lua_isnumber()
	// 	* lua_isstring()
	// 	* lua_isfunction()
	// 	* lua_istable()
	// 	* lua_isnil()
	// If the topmost value in the shared stack is a Lua function,
	// we add the input arguments for that function on top of
	// the shared stack 
	if (lua_isfunction(L, -1)) {
		// push the first argument for the Lua function that
		// is going to be called into the shared Stack
		lua_pushnumber(L, 3);
		// push the second argument for the Lua function that
                // is going to be called into the shared Stack
                lua_pushnumber(L, 4);
		const int NUM_ARGS = 2;
                const int NUM_RETURNS = 1;
		// Make a protected call of the Lua function that
		// we just got inside C. Here NUM_ARGS is the number
		// of input arguments to the called Lua function and
		// NUM_RETURNS is the number of returns by the called
		// Lua function. The 0 here specifies to return 0 if
		// the function call errors out instead of handling the
		// error with an error message. NUM_ARGS is used by Lua
		// to pick the function arguments from the shared Stack
		// for its call.
		// NOTE: C automatically takes the NUM_ARGS + 1 index
		// value in the shared stack to be the actual function
		// of Lua to be called and the values on top of index
		// NUM_ARGS + 1 as the input arguments for the function
		// Error handling for the function call can also be done
		// like this
		if (lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0) != LUA_OK) {
			// Here LUA_OK is a built-in constant from
			// <lua.h> that is equal to 0
			// TODO ... error handling
		} else {
			// peak into the shared Stack and get the topmost element
			// which will be the result from Lua function call.
			// NUM_RETURNS actually tells Lua about how many returns
			// from the function to push into the stack.
			lua_Number pythagoras_result = lua_tonumber(L, -1);
			printf("The Pythagoras(3,4) is %f\n", (float)pythagoras_result);
		}	
	// closing the Lua state
	lua_close(L);
	}
}

// Sometimes, it is benificial to call C functions from within
// Lua. C is better in rendering audio and images compared
// to Lua for example
void example_call_c_function(void) {
	// Create a new Lua state pointer to the shared
	// stack between Lua and C
	lua_State* L = luaL_newstate();
	// Push a C function into the shared Stack between
	// Lua and C
	lua_pushcfunction(L, native_pythagoras);
	// Exposing a global scope item from this C program
	// for Lua to access - in this case, the pointer to function
	// native_pythagoras() is pushed into the shared stack
	lua_setglobal(L, "native_pythagoras");
	// Import the Lua script that uses the native C function
	luaL_dofile(L, "./scripts/pythagoras-native.lua");
	// Get the wrapper function from Lua that calls the native
	// C function within itself and push it on top of the shared
	// stack 
	lua_getglobal(L, "pythagoras");
	// Check if the topmost value in the shared stack is a Lua
	// function. If it is, then add the input arguments for the
	// function on top of the function itself in the shared stack
	// and make a protected call of the Lua function within C.
	// NUM_ARGS is used to locate the input arguments to the Lua
	// function and also the Lua function to call itself within
	// the shared stack. NUM_RETURNS is used to populate the stack
	// with the return values of the Lua function call.
	if (lua_isfunction(L, -1)) {
		// adding the first input argument for the 'pythagoras'
		// function call which inturn calls the C function
		// native_pythagoras()
		lua_pushnumber(L, 3);
		// adding the second input argument for the 'pythagoras'
		// funtion call which inturn calls the C function
		// native_pythagoras()
		lua_pushnumber(L, 4);

		const int NUM_ARGS = 2;
		const int NUM_RETURNS = 1;
		// lua_pcall() returns 0 if the Lua function errors
		// out instead of return an error handling message
		// index NUM_ARGS + 1 in the shared stack pointed to
		// by L has the native_pythagoras() function from this
		// C program
		lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0);
		// Peak into the shared stack and pick out the topmost value
		// which in this case is the result from our C function call
		// or the native_pythagoras() call
		lua_Number pythagoras_result = lua_tonumber(L, -1);
		// explicitly type cast the result to float and print it
		printf("native_pythagoras(3, 4) = %f\n", (float)pythagoras_result);
	}
	// closing the Lua state
	lua_close(L);
}

// Define a C Struct called rectangle2d as a new user-defined data type
// with another name 'rectangle', using the typedef keyword
typedef struct rectangle2d {
	int x;
	int y;
	int width;
	int height;
} rectangle;

// A native C function that will be called from within Lua
// environment that also creates a variable of an user-defined
// data type
int create_rectangle(lua_State* L) {
       	// Create a new pointer of the user-defined data type 'rectangle'
       	// of this C program within the Lua environment. This pointer
	// is then pushed into the shared stack and it takes up memory
	// space in the stack, equal to the size of the struct.
     	rectangle* rect = (rectangle*)lua_newuserdata(L, sizeof(rectangle));
	// initialize all the fields of the struct variable to 0 
	rect->x = 0;
	rect->y = 0;
	rect->width = 0;
	rect->height = 0;
	// As usual, return the number of result values that this native C
	// function will push into the shared stack to inform the Lua
	// environment instead of returning the actual values themselves
	// which will actually be pushed into the shared stack.
	return 1;
}	

// Native C function to modify the fields of the 'rectangle' datatype
// defined by user. Again, this native C function will execute from the
// Lua environment and hence will not receive the input arguments directly.
// It only takes the shared stack as input and uses the arguments from the
// shared stack. It will also push the result balues back into the stack.
// This function will only return the number of result values instead of
// the actual values.
int change_rectangle_size(lua_State* L) {
	// Remember that a stack follows LIFO order. So when using
	// input arguments from the stack, the order of placing the
	// arguments should be reversed and the last placed argument
	// will be at the top and will be referenced first.
	// Here, the userdata is referenced first so that it can
	// directly be modified with the other two arguments
	rectangle* rect = (rectangle*)lua_touserdata(L, -3);
	// Modify the values of the 'rectangle' struct variable
	// fields by type casting the appropriate arguments from the
	// shared stack
	rect->width = (int)lua_tonumber(L, -2);
	rect->height = (int)lua_tonumber(L, -1);
	// Since the function does not create any new value and only
	// modified the rectangle userdata already present in the stack
	// using a reference pointer, this function does not return any
	// result values into the stack and hence we return 0
	return 0;
}

// function to pass and receive userdata types like structs between
// C and Lua
void lua_example_userdata(void) {
	// Create a pointer to a new shared stack between Lua and C
	lua_State* L = luaL_newstate();
	// expose the native C function from this C program that is to
	// be called from within Lua into the shared stack by pushing a
	// pointer to the function at the top of the shared stack
	lua_pushcfunction(L, create_rectangle);
	// add the C function create_rectangle() to the global scope
	// in Lua
	lua_setglobal(L, "create_rectangle");

	// push the second native C function into Lua
	lua_pushcfunction(L, change_rectangle_size);
	// get the second native C function into the global scope of Lua
	lua_setglobal(L, "change_rectangle_size");

	// Import the Lua script which will call our C function. 
	// Remember that this also automatically executes all
	// statements within the lua script and any declarations of
	// variables, functions etc in the Lua script will be added
	// into the shared stack. In this case, we have only declared
	// one variable 'square' in the Lua script which is created
	// by utilizing the native C function create_rectangle() 
	luaL_dofile(L, "./scripts/rectangle.lua");
	// Get the variable created by the Lua script through its
	// execution in luaL_dofile() into the top of the shared
	// stack
	lua_getglobal(L, "square");
	// Check if the top of the shared stack contains an user-defined
	// data type (a variable declared using struct)
	if (lua_isuserdata(L, -1)) {
		// Use the lua_touserdata() to peak at the userdata
		// variable from the top of the stack and then do implicit
		// conversion of the data to the 'rectangle' user defined
		// data type
		rectangle* r = (rectangle*)lua_touserdata(L, -1);
		printf("We got back a rectangle from Lua, width: %d, height: %d.\n", r->width, r->height);
	} else {
		printf("We did not get a rectangle userdata from Lua.");
	}
	// close the Lua state pointer and free up the shared stack
	lua_close(L);
}

void lua_example_table(void) {
	// create the Lua state pointer for the shared stack
	lua_State* L = luaL_newstate();
	// Load the Lua script into the C environment using
	// the shared stack to fill in the declarations in the Lua script
	// LUA_OK is an in-built constant in lua.h that is set to 0 which
	// is the retruned value of success for luaL_dofile(). So, we use
	// an if condition to check the successful import of the Lua script
	// into the shared stack and the C environment and if it has errored
	// out, we return an error message which is taken from the top of
	// the shared stack. This error message is pushed to the top of the
	// shared stack by the luaL_dofile() call if loading the Lua script
	// fails.
	if (luaL_dofile(L, "./scripts/configtable.lua") == LUA_OK) {
		// Get variable from the global scope of the Lua script
		// using the declared name of the variable in Lua and put
		// the variale at the top of the shared stack
		lua_getglobal(L, "config_table");
		// If the variable at the top of the shared stack is a Lua
		// table, then get the value of the key 'window_width'
		if (lua_istable(L, -1)) {
			// lua_getfield() is used to obtain the value of a
			// key from the Lua table at the top of the shared
			// stack and the obtained value is pushed back into
			// the top of the same shared stack.
			// lua_setfield() can be used in a similar way to
			// modify a Lua table's field value in the shared
			// stack using its index from the top
			lua_getfield(L, -1, "window_width");
			// convert the value at the top of the shared stack
			// to a string and print it appropriately
			printf("The window width defined in the lua table is %s\n", lua_tostring(L, -1));
		} 
	} else {
			luaL_error(L, "Error: %s\n", lua_tostring(L, -1));
	}
	
	// close the lua state and clear the stack memory
	lua_close(L);
}

// The main function
// int main(int argc, char* argv[]) {
	// lua_example_dofile();
	
	// create a variable inside lua and get its value into C
	// lua_example_getvar();
	
	// lua_example_stack();
	
	// example_call_lua_function();
	
	// Execute a native C function from inside Lua
	// example_call_c_function();
	
	// Send and recieve structs and other C userdata types 
	// between Lua and C
	// lua_example_userdata();
	
	// lua_example_table();
	// return 0;
// }
