function is_colliding(x1, y1, width1, height1, x2, y2, width2, height2)
	if (((x2 >= x1) and  (x2 <= x1 + width1)) or ((x2 <= x1) and (x2 + width2 > x1))) and 
		(((y2 >= y1) and (y2 < y1 + height1)) or ((y2 <= y1) and (y2 + height2 > y1))) then
		return true
	else
		return false
	end
end

-- Call the function with some values to test
if is_colliding(10, 10, 20, 8, 12, 13, 20, 6) then
  print("Rectangles are colliding.")
else
  print("Rectangles are not colliding.")
end
