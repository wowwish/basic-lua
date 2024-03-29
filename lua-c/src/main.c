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

// Define the SDL window width and height as constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int is_running = FAIL;

// function to create a window
int initialize_window(void) {
	// throw error if the SDL initiation fails, ie, if SDL_init()
	// does not return the success signal 0. Here, insread of
	// initializing individual components of the SDL such as the
	// graphics driver or the keyoboard hardware driver, we initialize
	// every abstraction layer in SDL.
	// printf() places output on the standard output stream 'stdout'.
	// fprintf() places output on the named output stream which can be
	// 'stderror' or 'stdout' or a file for example.
	if (SDL_init(SDL_INIT_EVERYTHING) != 0) {
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

void update(void) {

}

void render(void) {

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

// The main function to start the game
int main(int argc, char* argv[]) {
	// Capture the output of initialization of window and renderer
	is_running = initialize_window();
	// Start the game loop as an infinite loop. The game loop has
	// three steps that it performs in every iteration and it iterates
	// forever. The first stem is to get input from the user if any.
	// Then the game is updated according the the user's input.
	// Finally, the modified game state is rendered in the window
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
