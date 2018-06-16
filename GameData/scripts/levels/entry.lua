
me = {
    test = function()
        world.change_level(me.self, "two", {x=50, y=100})
    end,
    draw = function(window)
        world.draw(me.self, window)
    end,
}
