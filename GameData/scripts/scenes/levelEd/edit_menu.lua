
local edit_menu = {}

edit_menu.signal = nil

edit_menu.world = nil
edit_menu.actorman = nil

edit_menu.init = function(self, signal)
    scene.init_world(self)
    edit_menu.world = scene.get_world(self)
    edit_menu.actorman = world.get_actorman(edit_menu.world)
end

edit_menu.update = function(self, delta)
    me.world = scene.get_world(self)
    me.actorman = world.get_actorman(me.world)
end

edit_menu.draw = function(self, window)
    scene.draw(self, window)
end

edit_menu.message = function()
    local signal = edit_menu.signal
    edit_menu.signal = nil
    return signal;
end

edit_menu.release = function()

end

return edit_menu
