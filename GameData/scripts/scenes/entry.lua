me = {
    init = function()
        local m = scene.get_menu(me.self)
        print(m)
        local play_button = menu.add_text_button(m, "play", {x=100, y=100}, "mainmenu.play")
    end,
    update = function(delta)
    end
}
