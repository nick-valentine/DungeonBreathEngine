main = nil;
me = {
    init = function()
        local size = scene.get_size(me.self)
        main = scene.get_menu(me.self)
        local play_button = menu.add_text_button(main, "play", {x=10, y=size.y-220}, "mainmenu.new_game_button")
        local options_button = menu.add_text_button(main, "options", {x=10, y=size.y-160}, "mainmenu.options_button")
        local exit_button = menu.add_text_button(main, "exit", {x=10, y=size.y-100}, "mainmenu.exit_button")

        menu.set_current(main, play_button)
        menu_item.pair_items(play_button, options_button, 1)
        menu_item.pair_items(options_button, exit_button, 1)
    end,
    update = function(delta)
        if menu.has_signal(main) == 0 then
            return
        end

        local pressed = menu.signal_tag(main)
        if pressed == "play" then
            logger.info("play pressed")
        elseif pressed == "options" then
            logger.info("options pressed")
            scene.push(me.self, "options.lua")
        elseif pressed == "exit" then
            scene.pop(me.self)
        end
    end,
    wakeup = function()
        music.play("Harp.ogg")
    end
}
