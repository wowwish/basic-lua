-- use a different seed everytime we start
math.randomseed(os.time())

-- local variables declared outside any blocks within the file cannot be used in other files after importing
-- The main hero of the game will be at the centre of the window
local player_x, player_y = 400, 300

-- start while loop with 0 and end with 499 or start with 1 and end with 500
local num_enemies = 0

-- while loop
while num_enemies < 500 do
	-- Get random enemy position for a 800x800 resolution
	enemy_x = math.random(0, 800) -- random x value
	-- local enemy_x = math.random(0, 800)
	enemy_y = math.random(0, 600) -- random y value

	-- add a buffer to the position if it coincides with the hero's position at the centre of the window
	if (enemy_x == player_x and enemy_y == player_y) then
		-- TODO: Error, enemy cannot be in the same position as hero
		print("Enemy and player position clashed!")
	else
		-- Display the two random values
		print("Enemy "..num_enemies.." pos: ("..enemy_x..","..enemy_y..")")
	end
	-- remember that lua does not have increment/decrement operators
	num_enemies = num_enemies + 1
end

-- variables declared inside the loop are global variables in lua and can be accessed outside the loop
-- you have to prefix variables with the local keyword to declare their scope to be within the loop block
print("Enemy X: "..enemy_x)

print("Thank you, goodbye!")
