build:
	# Use the gcc compiler with C99 standard for code and show all warnings
	# We compile both the lua source code that ships with an installation of
	# Lua, as well as our custom C source code. We then specify both the source
	# files to be compiled into the same binary file called "main". Also, since
	# our custom C source code will have a main() function and the "lua.c" source
	# file from Lua will also has a main() method for initiating the Lua REPL, 
	# we must remove the REPL files "lua.c" (and also "luac.c" compiler program
	# for Lua for good measure) from the Lua source directory. 
	# We add the pre-processor Definition LUA_USE_POSIX to tell gcc to use posix
	# based functions for creating temporary directories during the build process
	# Also, since the compilation of code relies on the <math.h> directive of C,
	# we add the "-lm" linker flag. The "m" stands for "libm", the library that
	# contains <math.h>
	gcc -std=c99 -Wall -D LUA_USE_POSIX ./lib/lua/src/*.c ./src/*.c -lm -o main


clean:
	# remove the compiled binary
	rm ./main

run:	
	# Run the compiled binary
	./main
