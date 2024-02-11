menu_option = 3

-- Here are some comparison operators
--------------------------------------
-- value1 == value2
-- value1 ~= value2
-- value1 > value2
-- value1 >= value2
-- value1 < value2
-- value1 <= value2


if menu_option == 1 then
	menu_text = "Easy"
elseif menu_option == 2 then
	menu_text = "Medium"
elseif menu_option == 3 then
	menu_text = "Hard"
elseif menu_option == 4 then
	menu_text = "Very Hard"
end

print("Menu Option: " .. menu_text)
