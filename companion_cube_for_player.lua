print("Hello world!")
local follower_part = script.Parent
-- ADDING A PORTAL COMPANION CUBE THAT FOLLOWS THE PLAYER :)


-- Add BodyPosition and BodyGyro properties to the follower part
-- BodyPosition applies a force on the follower_part and BodyGyro applies
-- a torque (rotational force) on the follower_part to allow it to move
-- through certain difficult terrain and follow the master
local follower_position = Instance.new("BodyPosition", follower_part)
local follower_bodygyro = Instance.new("BodyGyro", follower_part)
follower_bodygyro.MaxTorque = Vector3.new(900000, 900000, 900000)

-- Define the name of who the part should follow
-- Instead of hardcoding the master name here in script,
-- the master name can be added as a StringValue to the
-- follower object and accessed
local master_name = follower_part.master.Value

-- Define the position of where the follower part should stay in relation to its master
local follow_position = Vector3.new(0, 5, 0)

-- While loop to update the Position and Orientation of the follower part
while true do
	local master = workspace:WaitForChild(master_name)
	local player = game.Players:FindFirstChild(master.Name)
	-- get the position of the entire Humanoid, not the character avatar or a part
	-- of the character avatar
	local master_position = master.HumanoidRootPart.Position
	-- specify where the follower should stop in relation to the position of the master
	local stop_at = ((master_position - follower_part.Position).magnitude - 1) * 500
	follower_position.P = stop_at
	follower_position.Position = master_position + follow_position
	-- The direction of CFrame of the master will also be the direction of CFrame
	-- of the follower. Therefore, the follower moves in the same direction as its master
	follower_bodygyro.CFrame = master.HumanoidRootPart.CFrame
	wait(0.1)
end

