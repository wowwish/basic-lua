-- Get the object containing this script
local wall = script.Parent

-- keep the part anchored
wall.Anchored = true

-- connect a touch event for the wall
wall.Touched:Connect(function()
	-- change color of object when touched
	wall.Color = Color3.new(1, 0, 0)	
	-- change position of object when touched
	-- move the wall in the x-direction when touched
	wall.Position = Vector3.new(
		wall.Position.X + 1,
		wall.Position.Y,
		wall.Position.Z
	)
end)
