--------------------------------------
-- Define the class (prototype object) attributes
--------------------------------------
-- The Lua programming language does not have a Class per se.
-- It uses prototype objects that are inherited by other objects
-- An object looks for the methods and attributes first within its own definition
-- and then in its prototype definition.

Fighter = {
    name = "",
    health = 0,
    speed = 0
}

--------------------------------------
-- Define the class (prototype object) methods
--------------------------------------

-- We can define the methods of the Fighter class outside the class
-- definition like this. The "self" keyword can be used to access
-- the class attributes and previously defined class methods inside such methods
function Fighter:light_punch()
    print("fighter "..self.name.." performed a light punch")
end

function Fighter:heavy_punch()
    print("fighter "..self.name.." performed a heavy punch")
end

function Fighter:light_kick()
    print("fighter "..self.name.." performed a light kick")
end

function Fighter:heavy_kick()
    print("fighter "..self.name.." performed a heavy kick")
end

function Fighter:special_attack()
    print("fighter "..self.name.." performed a special attack!!!")
end

----------------------------------------
-- Define the class constructor
----------------------------------------
function Fighter:new(t)
    -- If "t" is a falsy value (becomes false when converted to boolean)
    -- then "t" is assigned as empty table, otherwise the original table "t"
    -- is retained
    t = t or {} -- create object if user does not provide one
    -- binding metatable to the object of Fighter
    setmetatable(t, self)
    -- the __index() metamethod is used to set the prototype object that the newly created
    -- object will inherit. In this case, the new Object will inherit the Fighter object itself which
    -- is accessible as the "self" keyword within the method.
    -- Lua searches for methods and attributes from the __index table/prototype when it is not able to find in the
    -- original table/object
    self.__index = self
    -- Keep in mind that A metatable defines metamethods for the instance.
    -- __index is the metamethod that routes field access to another table
    -- (if __index is a table. It could also be a function)
    return t
end

-----------------------------------------
-- Create two fighter objects
-----------------------------------------
blanka = Fighter:new({
    name = "Blanka",
    health = 100,
    speed = 60
})
print("Object "..blanka.name.." was created with prototype object Fighter itself as __index.")

chun_li = Fighter:new({
    name = "Chun Li",
    health = 100,
    speed = 85
})
print("Object "..chun_li.name.." was created with prototype object Fighter itself as __index.")

------------------------------------------
-- Call object methods
------------------------------------------
blanka:light_punch()
blanka:heavy_kick()
blanka:special_attack()

chun_li:light_punch()
chun_li:heavy_kick()
chun_li:special_attack()

------------------------------------------
-- Creating Bank Account Objects
------------------------------------------

BankAccount = {
    account_number = 0,
    holder_name = "",
    balance = 0.0
}

function BankAccount:deposit(amount)
    self.balance = self.balance + amount
end

function BankAccount:withdraw(amount)
    self.balance = self.balance - amount
end

function BankAccount:new(t)
    t = t or {} -- If there is some "t", assign it to "t". If "t" is nil, assign empty table to "t"
    setmetatable(t, self) -- set the metatable for "t" as "BankAccount"
    -- Keep in mind that a metatable defines metamethods for the instance.
    -- __index is the metamethod that routes field access to another table 
    -- (if __index is a table. It could also be a function)
    self.__index = self
    return t
end


johns_account = BankAccount:new({
    account_number = 12345,
    holder_name = "John",
    balance = 0.0
})

johns_account:deposit(400.00)
johns_account:withdraw(50.00)

print("New account object...")
print(johns_account.balance)
