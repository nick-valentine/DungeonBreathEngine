options = nil;
size = nil;
lang_label = nil;
function build_menu()
    menu.clear(options)
    lang_label = menu.add_label_raw(options, {x=60, y=100, width=300, height=50}, config.get_string("language", "eng"))
    local lang_left = menu.add_sprite_button(
        options, 
        "lang_left",
        {x=10, y=100, width=50, height=50},
        "RPG_GUI_v1.png",
        {x=320, y=60,  width=40, height=40},
        {x=320, y=110, width=40, height=40},
        {x=320, y=10,  width=40, height=40}
    )
    local lang_right = menu.add_sprite_button(
        options,
        "lang_right",
        {x=410, y=100, width=50, height=50},
        "RPG_GUI_v1.png",
        {x=360, y=60,  width=40, height=40},
        {x=360, y=110, width=40, height=40},
        {x=360, y=10,  width=40, height=40}
    )
    local key_bindings_button = menu.add_text_button(options, "key_bind", {x=10, y=size.y-160}, "optionsmenu.key_bind_button")
    local exit_button = menu.add_text_button(options, "exit", {x=10, y=size.y-100}, "optionsmenu.back_button")

    menu.set_current(options, key_bindings_button)
    menu_item.pair_items(key_bindings_button, exit_button, 1)
end
me = {
    init = function()
        size = scene.get_size(me.self)
        options = scene.get_menu(me.self)
        build_menu();
    end,
    update = function(delta)
        if menu.has_signal(options) == 0 then
            return
        end

        local pressed = menu.signal_tag(options)
        if pressed == "lang_left" then
            local l = lang.prev()
            config.set("language", l);
            build_menu()
        elseif pressed == "lang_right" then
            local l = lang.next()
            config.set("language", l);
            build_menu()
        elseif pressed == "key_bind" then
            logger.warn("key binding not implemented")
        elseif pressed == "exit" then
            scene.pop(me.self)
        end
    end,
    wakeup = function()
        music.play("Harp.ogg")
    end
}
