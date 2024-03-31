-- Creating 10 new objects in the game workspace
for i = 1, 10 do
	local new_block = Instance.new("Part", workspace)
	new_block.CanCollide = false
	if i == 10 then
		new_block.Color = Color3.new(0, 1, 0)
	else
		new_block.Color = Color3.new((1 / i), 0, 0)
	end
	new_block.Position = Vector3.new(i * 5, 0, 0)
	new_block.Name = "New_Part"..i
end


-- In the workspace, the character and player are different entities that
-- are connected with each other. The character is the avatar used by the player
-- to interact with the world of the game workspace. The avatar has different
-- body parts such as arm, leg, head etc but the player is an abstract object
-- which can hold player specific metadata such as name, and a reference to
-- a character in the workspace

-- A humanoid is an element placed inside the character of the player that provides
-- traits to the character such as walk speed, health bar. This humanoid instance
-- is used mainly to animate the character.

-- The spawn location of character can be modified by placing a spawn object at
-- the desired location on the game workspace display (take from Model > Gameplay)

-- This is how we can get the player of our game
game.Players.PlayerAdded:Connect(function (player)
	print("Player "..player.Name.."has just joined the game.")
	
	-- The game workspace also has a leaderboard with stats on how much
	-- money a player has, player ranks, other player related meta information
	-- for the game etc
	-- As soon as a new player is created in the game, the access to the player's
	-- leaderboard entry becomes available
	-- Here, we create a folder to store stats of the player, hence the parent
	-- of the created folder will be the player
	local leaderstats = Instance.new("Folder", player)
	leaderstats.Name = "leaderstats"
	-- IntValue is the Roblox Studio version of adding a Numeric Value to
	-- the leaderboard in the game workspace
	local player_money = Instance.new("IntValue", leaderstats)
	player_money.Name = 'Money'
	player_money.Value = 1000

	local player_xp = Instance.new("IntValue", leaderstats)
	player_xp.Name = 'XP'
	player_xp.Value = 5
	
	
	-- Now that we have the Player, we can get the Character of the Player
	player.CharacterAdded:Connect(function (character)
		print("Character "..character.Name.."has joined the game.")

		-- We can also use the Character associated with a player to get the player
		-- leaderboard stats
		local player_name = game.Players:FindFirstChild(character.Name)
		local player_stats = player:WaitForChild("leaderstats")
		local money = player_stats:FindFirstChild("Money")
		local xp = player_stats:FindFirstChild("XP")
		
		-- update player money and xp after getting access to it using the character
		-- connected to the player
		money.Value = money.Value + 5
		xp.Value = xp.Value + 1
	end)
end)



-- ROBLOX STUDIO SHORTCUTS:

-- Focus on Object - Select object either from the game workspace display or the explorer and press F
-- Delete Object(s) - Select object and press Del
-- Duplicate Object(s) - Select object and press Ctrl + D
-- Select multiple Objects by holding Shift while selection objects
-- Use Ctrl + G to group multiple selected objects into a single group
-- Free Assets are available in the Toolbox
-- The terrain editor can be used to add terrain effects using brushes in the game workspace
-- Similarly, the lighting object in the explorer can be used to modify the game world lighting
