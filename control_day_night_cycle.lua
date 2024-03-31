---------------------------------------------------------------------------------------------------------------------------------
-- Script to control the Day/Night light cycle with varying speed
---------------------------------------------------------------------------------------------------------------------------------

local TIME_SPEED = 60 -- set 1 min script time = 1 hour in game
local START_TIME = 9 -- start game's time at 9AM on the first day

-- Initialize minutes_after_midnight to the first day of the game 9AM
local minutes_after_midnight = START_TIME * 60
local wait_time = 60 / TIME_SPEED

while true do
	-- specify how many seconds to wait in the current game frame
	-- for a TIME_SPEED of 60, the game loop would wait one second
	-- on every frame before updating the game clock
	wait(wait_time)
	-- Increment minutes after midnight at every second of script time
	minutes_after_midnight = minutes_after_midnight + 1
	-- set the Day/Night cycle appropriately according to the number of minutes
	-- after midnight
	game.Lighting:SetMinutesAfterMidnight(minutes_after_midnight)
	--minutes_after_midnight contunues to increment forever and the game
	-- handles iterative day/night cycles appropriately. So even when
	-- minutes_after_midnight get incrmented by 60 * 24 minutes once the game
	-- has started (1 sec is 1 min in game), the game day/night cycle will repeat and continue.
end
