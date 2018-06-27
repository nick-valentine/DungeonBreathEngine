me = {}

me.label = nil

me.init = function()
	me.size = scene.get_size(me.self)
	me.label = label.get({x=(me.size.x / 2) - 100, y=me.size.y-100, width=100, height=50}, "Press start to play")
end

me.update = function(delta)
	local dsn = input.get_input()
	logger.info("input: ", dsn)
	if not (dsn == "") then
		scene.push(me.self, "mainMenu")
	end
	if input.is_key_pressed(input.escape) == 1 then
		scene.pop(me.self)
	end
end

me.wakeup = function()

end

me.draw = function(window)
	label.draw(me.label, window)
end

me.release = function()
	label.release(me.label)
end
