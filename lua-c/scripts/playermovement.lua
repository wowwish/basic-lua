-- set the SDL window size
local WINDOW_WIDTH = 800
local WINDOW_HEIGHT = 600

-- positions x and y of a game object
local x, y = 1, 1

-- dx and dy represent the number of pixels of displacement of positions
-- x and y per second for the player on the x and y axis respectively
local dx, dy = 50, 30

---------------------------------------
-- Update function
---------------------------------------

function update(delta_time)
	-- delta_time comes from the shared stack between Lua and C. 
	x = x + (dx * delta_time)
	y = y + (dy * delta_time)

	-- Make the player's movement be bounded within the window by
	-- causing the player to move in the reverse direction when the
	-- player hits the edges of the SDL window
	if (x > WINDOW_WIDTH) or (x <= 0) then 
		dx = -dx
	end
	if (y > WINDOW_HEIGHT) or (y <= 0) then
		dy = -dy
	end
	-- Calling native C function with modified values from Lua environment
	-- to update the state of C struct player (a game object in C)
	set_player_pos(x, y)
end

---------------------------------------
-- Render function
---------------------------------------

function render()
end
