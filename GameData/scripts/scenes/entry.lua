me = {
    init = function()
        local size = scene.get_size(me.self)
        local m = scene.get_menu(me.self)
        local play_button = menu.add_text_button(m, "play", {x=10, y=size.y-220}, "mainmenu.new_game_button")
        local options_button = menu.add_text_button(m, "options", {x=10, y=size.y-160}, "mainmenu.options_button")
    end,
    update = function(delta)
    end
}
