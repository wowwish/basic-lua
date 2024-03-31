local missile = script.Parent

while true do
	wait()
	
	-- update the missile velocity to move in the direction where the model is looking at
	missile.PrimaryPart.Velocity = missile.Part.CFrame.LookVector * 50
end
