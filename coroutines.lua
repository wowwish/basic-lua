-- Lua coroutines allow us to execute multiple tasks at once by utilizing
-- concurrency and threading. Lua passes the execution control to each
-- coroutine in a controlled manner and waits until the coroutines finish.
-- A coroutine can be paused and re-entered at a later time repetitively
-- to help with multi-tasking. Each task runs in a thread which is independent
-- of other threads (multi-threading). Only one coroutine runs at a time in Lua.

-- NOTE: Coroutines in Lua only support pseudo-parallelism (context-switching).
-- Lua use collaborative multi-threading where threads dependent on other threads
-- for their execution wait for the completion of the other threads insread of
-- pre-emptive multi-threading where all threads only run for a fixed amount
-- of time and pass the control to the next thread when their time is up. Also,
-- the coroutines are not actual OS processes, but they are pieces of Lua code that
-- simulate concurrency using OS threads. Hence, coroutines lack support for some
-- of the locking mechanisms available from the OS.

-- A parent coroutine can pass the control to its child coroutine using the
-- coroutine.yield() method in lua. The flow of control comes back to the
-- parent coroutine when the child coroutine fully executes and the parent
-- can continue on with its remaining tasks using coroutine.resume()
-- We can create a coroutine using the coroutine.create(f) function. We pass a Lua
-- function as an entry point for the thread. The object returned by Lua is a thread.

-- A coroutine can be in one of three different states: suspended, running, and dead.
-- When we create a coroutine, it starts in the suspended state. That means that a
-- coroutine does not run its body automatically when we create it. We can check the
-- state of a coroutine with the coroutine.status() method.


function f()
	print("f, A")
	coroutine.yield() -- yielding control flow to the outside scope of the coroutine
	-- using this function.
	print("f, B")
end

---------------------------------------------------------
-- Creates a coroutine with function f as the entry
---------------------------------------------------------

c = coroutine.create(f)
print(type(c)) -- prints "thread"

print(coroutine.status(c)) -- prints "suspended"

-- The state suspended means that the thread is alive, but it is not doing anything.
-- To start the thread we use the coroutine.resume(c) function. Lua will enter the thread
-- and leave when the thread yields.


coroutine.resume(c) -- prints "f, A" and then yields control

print(coroutine.status(c)) -- prints "suspended" again as it has yielded control but still
-- has leftover work to do

-- with a normal function, we would not be able to carry on from where we left off but
-- calling coroutine.yield() inside the function declaration adds a sort of breakpoint
-- for us to resume later on using coroutine.resume()
coroutine.resume(c) -- prints "f, B"

-- Since the function had only one yielding point, it would have completed by this stage
-- and would have moved to the "dead" state
print(coroutine.status(c)) -- prints "dead"



