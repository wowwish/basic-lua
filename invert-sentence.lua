-- Initialize a sentence
text = "The quick fox jumps over the lazy dog."

-- string.gmatch() returns a list of all the sub-strings of an input string that match the given regex pattern
-- The "%S" in the pattern is a character class in lua and corresponds to a set of all non-space characters
words = string.gmatch(text, "%S+")

result = ""

-- Loop all words adding each word to the beginning of the final result string
for word in words do
  result = word.." "..result
end

-- Display the final inverted result sentence
print("Inverted sentence: "..result)
