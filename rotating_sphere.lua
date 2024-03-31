
-- The parent of this script is the sphere object in the game workspace
local sphere = script.Parent

-- Simulate the color and texture of the sphere to be like the sun
-- if the system time is between 9AM and 6PM or to be like the moon
-- otherwise
local current_time = tonumber(os.date("%H"))
if current_time >= 9 and current_time < 18 then
	sphere.Color = Color3.new(1, 1, 0)
	sphere.Material = Enum.Material.Neon
else
	sphere.Color = Color3.new(1, 1, 1)
	sphere.Material = Enum.Material.Foil
end

-- Make the sphere constantly rotate along its y-axis
function rotate_sphere(speed)
	while true do
		-- Every loop within the roblox studio game loop requires
		-- a wait() call. This is not a Lua function, but a specific function
		-- within the roblox studio. 0.03 is the minimum time that the game
		-- waits on a single frame in the game loop
		wait(0.03)
		sphere.Orientation = sphere.Orientation + Vector3.new(0, speed, 0)
	end
end

-- Make sure we call the function
rotate_sphere(2)

