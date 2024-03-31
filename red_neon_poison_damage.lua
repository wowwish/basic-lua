-- Check the collision with the Poison
local poison = script.Parent

function on_poison_touch(other_part)
	-- If the Parent of the part that touched the poison object is
	-- a humanoid, store the reference to that object in a variable
	-- else store nil in the variable
	local humanoid = other_part.Parent:FindFirstChild("Humanoid")
	--print(other_part.Name.."touched the Poison!!!")
	if humanoid ~= nil then
		--print("we found a humanoid!")
		-- Destroy the poison if it is touched by a human
		--poison:Destroy()
		-- Make the humanoid take damage when touching poison
		humanoid:TakeDamage(10)
	end
end

-- Add a triggered effect on collision on this object
poison.Touched:Connect(on_poison_touch)
