// Access the SDL2 abstractions by loading its preprocessor directive
#include <SDL2/SDL.h>
#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"

// Define constants for success and failure of a function. In C,
// it is standard practice to return 0 for successful execution
// of a function and return 1 when a function errors out
#define SUCCESS 0
#define FAIL 1

// A pointer current referencing NULL that will be used to reference
// a new SDL Window
SDL_Window* window = NULL;
// A pointer currently referencing NULL, that will be used to reference
// a new SDL renderer which uses the graphics driver in the system
// to render graphics within the SDL window.
SDL_Renderer* renderer = NULL;
// Initialize a Lua State pointer currently referencing NULL
lua_State* L = NULL;


// Define the SDL window width and height as constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Define the frames per second for the game
#define FPS 30
// Define the time in milliseconds for which each frame
// will be rendered
#define FRAME_TIME_LENGTH (1000 / FPS) 

// Variable to keep track of whether the game loop is running
int is_running = FAIL;
// Variable to keep track of the time in milliseconds since the
// last time the game state was updated in the game loop
int last_frame_time;

// declare a struct representing a Player in the game
struct player {
	float x; // position x
	float y; // position y
	float width;
	float height;
} player;

// function to create a window
int initialize_window(void) {
	// throw error if the SDL initiation fails, ie, if SDL_Init()
	// does not return the success signal 0. Here, insread of
	// initializing individual components of the SDL such as the
	// graphics driver or the keyoboard hardware driver, we initialize
	// every abstraction layer in SDL.
	// printf() places output on the standard output stream 'stdout'.
	// fprintf() places output on the named output stream which can be
	// 'stderror' or 'stdout' or a file for example.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return FAIL;
	}
	// SDL_CreateWindow() takes the window title, The x position of the
	// upper left corner of the window and the y position of the upper
	// left corner of the window, window width, window height and
	// several boolean flags that configure the window such as 
	// borderless as input arguments. Here, we use in-built constants
	// from the SDL2 library. The function then creates a pointer to
	// a newly created window using the provided arguments.
	window = SDL_CreateWindow(
			"SDL WINDOW",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_BORDERLESS);
	// If the window was not initialized, then handle the error
	if (!window) {
		fprintf(stderr, "Error creating SDL window.\n");
		return FAIL;
	}
	// Create a pointer to a new Rederer. The SDL_CreateRenderer()
	// function takes pointer to the window for which the renderer
	// is being created, the index of the rendering driver to
	// initialize, or -1 to initialize the first one supporting the
	// requested flags, and any additional flags for the renderer
	// (here, we use no additional flags and hence pass 0)
	renderer = SDL_CreateRenderer(window, -1, 0);
	// If renderer initialization failed, handle the error
	if (!renderer) {
		fprintf(stderr, "Error");
	}
	// If both the window and the renderer have been initialized
	// successfully, return 0
	return SUCCESS;
}

// A one-time initialization function for the game loop which places
// the players in their starting position
void setup(void) {
	player.x = 20;
	player.y = 20;
	player.width = 10;
	player.height = 10;
}

// Function to take care of the first step in the game loop
void process_input() {
	// Initialize an event
	SDL_Event event;
	// Using  
	SDL_PollEvent(&event);
	switch (event.type) {
		// SDL_QUIT represents the event triggered when
		// the user presses the X quit button on the SDL window
		case SDL_QUIT:
			// Change the is_running variable in the outer scope
			// from SUCCESS to a termination value, such as -1
			is_running = -1;
			// Break the outer while loop which executes this function
			break;
		// SDL_KEYDOWN represents the even triggered when the user
		// presses any key on the Keyboard with the SDL window active
		case SDL_KEYDOWN:
			// check if the user has pressed the escape key
			// by checking the symbol of the key press event
			// that was triggered and see if the symbol is
			// SDLK_ESCAPE (SDL has many such key symbol 
			// constants available for checking key presses)
			if (event.key.keysym.sym == SDLK_ESCAPE)	
				// Terminate the window and exit the
				// program similar to the action taken when
				// the user closes the SDL window
				is_running = -1;
			break;
	}
}

// Function to update the game state in every iteration of the game loop
// to animate the game objects, modify game scores etc
// Additionally, to lock the game at the defined frames per second rate,
// the function keeps track of the time difference between the last call
// and current call of itself and only executes the game state modification
// logic for the next frame when the time difference is more than the
// FRAME_TIME_LENGTH constant
void update(void) {
	// The time in milliseconds since the last update() call in the
	// game loop is stored here to help with FPS locking of the game
	// for smooth game animations for better visual perception of the game
	// Here we use SDL_GetTicks() which is an in-built function in the SDL
	// library that gives back the number of milliseconds that have passed
	// since the last SDL_Init() function call which in our case happens
	// in the initialize_window() function
	// SDL_TICKS_PASSED() is another in-built function in SDL that returns true
	// or false depending on if the first timepoint provided to it has passed the
	// second timepoint provided in the call. So in our case, we check if 
	// the time since SDL initialization has exceeded
	// (last_frame_time + FRAME_TIME_LENGTH). Notice that the while loop here
	// is closed without any body. This locks the function in the while loop execution
	// until the while loop condition is not satisfied in which case, the player positions
	// and the new frame is created with the updation time recorded in last_frame_time
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TIME_LENGTH));
	// Updating the game object states using constants at every iteration
	// makes the distance travelled by a game object across the screen difficult
	// to track and the speed of movement of objects in the screen also becomes difficult
	// to determine for a given time frame of seconds or milliseconds.
	// For a smooth visualization of the game in the window, and proper tracking of objects,
	// we can instead use a factor which can be used to scale the modification value of an
	// object's state in the game. Here, the factor is delta_time which is the time since
	// the last frame updation in seconds (milliseconds is divided by float 1000 to convert to seconds)
	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
	last_frame_time = SDL_GetTicks();
	
	// Call the update() function of lua intside this native C function by getting the function
	// delcared in Lua to the top of the shared stack
	lua_getglobal(L, "update");
	// If the element at the top of the shared stack is indeed a function, perform a protected
	// call of that function - in our case it is the Lua's update() function from the playermovement.lua
	// script which takes only delta_time as input argument and no output result will be inserted into the 
	// shared stack.
	// The function only changes the value of the 'x' and 'y' variables declared in the Lua environment
	if (lua_isfunction(L, -1)) {
		lua_pushnumber(L, delta_time);
		const int NUM_ARGS = 1;
		const int NUM_RETURNS = 0;	
		lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0);
	}
}

// function to render the objects of the game in their current frame state
// in the associated window of the renderer
void render(void) {
	// Internally, SDL uses two buffers for rendering graphics
	// select the colour to use for rendering graphics. One buffer
	// will be populated with appropriate pixel values when the other
	// buffer is rendered and then when the population of the buffer
	// in the back is done it is swapped with the front buffer and displayed.
	// The buffers are sequentially cleared and swapped like this to reduce
	// flickering, pixellation etc and display the objects very fast without
	// any distortions
	
	// SDL_SetRenderDrawColor() takes the pointer to the renderer, RGB values
	// and opacity (alpha value) for the color. Here we are rendering red color
	// without any transparency as the background of the SDL window.
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// Clear the currently displayed renderer buffer
	SDL_RenderClear(renderer);
	
	// Draw the player at position player.x and player.y by first creating
	// an variable of the SDL_Rect struct and then passing its reference to
	// SDL_RenderFillRect() along with the pointer to the renderer. We use
	// the player struct variable here to create another very similar SDL_rect
	// struct variable but we could also have passed the x,y,width,height values
	// directly, or made a function to create such a variable.
	// Also, we change the color of player_rect to yellow before rendering to
	// differentiate it from the background color.
	// Change color before creating and drawing the object in the SDL window
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_Rect player_rect = {
		// explicitly casting float to int here 
		(int)player.x,
		(int)player.y,
		(int)player.width,
		(int)player.height};
	SDL_RenderFillRect(renderer, &player_rect);	

	// Here, the populated renderer is brought to the front and displayed in the
	// window
	SDL_RenderPresent(renderer);

}

void destroy_window(void) {
	// Using the pointer to the renderer struct, this function
	// destroys and clears the memory used by the renderer
	SDL_DestroyRenderer(renderer);
	// This function destroys the window struct and clears
	// the memory used by the window, using its pointer
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Native C function used by the update() function in playermovement.lua
// As always, native C functions which are executed within Lua environment
// only use the shared stack to find its input arguments and to push its
// result values into
int set_player_pos(lua_State* L) {
	// get the first added parameter from the top of the shared stack
	lua_Number x = lua_tonumber(L, -2);
	// get the last added parameter from the top of the shared stack
	lua_Number y = lua_tonumber(L, -1);
	// Update the player struct variable's fields with the new values
	player.x = (int)x;
	player.y = (int)y;
	
	return 0;
}

// The main function to start the game
int main(int argc, char* argv[]) {
	// Create the Lua State Pointer
	L = luaL_newstate();

	// To have access to the C implementation of standard Lua libraries with useful functionalities,
	// the C host program should call the luaL_openlibs function, which opens all standard libraries
	luaL_openlibs(L);
	// Link and load the functions, variables etc from the Lua script 
	if (luaL_dofile(L, "./scripts/playermovement.lua") != LUA_OK) {
		luaL_error(L, "Error reading playermovement.lua: ", lua_tostring(L, -1));
		// EXIT_FAILURE is a built-in C constant from stdlib.h that is equal to 1
		// In this program, the luaxlib.h file will uses stdlib.h internally
		// and hence this constant is available for use
		return EXIT_FAILURE;
	}

	// Push the native C function used by the update() call from the playermovement.lua
	// script into the shared stack
	lua_pushcfunction(L, set_player_pos);
	// Make the native C function set_player_pos currently in the shared stack available
	// in the global scope of the Lua environment
	lua_setglobal(L, "set_player_pos");

	// Capture the output of initialization of window and renderer, to keep the game loop
	// aware of whether the window and renderer are still up and running
        is_running = initialize_window();

	// A single time call of this setup() function is used to initialize
	// position of every object in the game, starting scores etc before starting
	// the game loop
	setup();

	// Start the game loop as an infinite loop. The game loop has
	// three steps that it performs in every iteration and it iterates
	// forever. The first stem is to get input from the user if any.
	// Then the game is updated according the the user's input.
	// Finally, the modified game state is rendered in the window.
	// The speed of the game (while) loop iteration and thereby the speed of the game
	// itself will be dependent on how fast your CPU executes instructions
	// (CPU clock time)
	while (is_running == SUCCESS) {
		process_input();
		update();
		render();
	}
	// After the game loop terminates, destroy and cleanup
	// the resources for a smooth exit from the program
	destroy_window();
	return 0;
}
