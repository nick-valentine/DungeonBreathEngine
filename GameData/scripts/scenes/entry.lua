me = {
    init = function()
        local size = scene.get_size(me.self)
        local m = scene.get_menu(me.self)
        local play_button = menu.add_text_button(m, "play", {x=10, y=size.y-220}, "mainmenu.new_game_button")
        local options_button = menu.add_text_button(m, "options", {x=10, y=size.y-160}, "mainmenu.options_button")
        local exit_button = menu.add_text_button(m, "exit", {x=10, y=size.y-100}, "mainmenu.exit_button")

        menu.set_current(m, play_button);
        menu_item.pair_items(play_button, options_button, 1);
        menu_item.pair_items(options_button, exit_button, 1);
    end,
    update = function(delta)
    end
}
