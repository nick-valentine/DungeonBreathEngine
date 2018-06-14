package.path = package.path .. ";GameData/scripts/?.lua"
local shapes = require 'shapes'
local ui = require 'ui'

local options = nil;
local size = nil;

function build_menu()
    menu.clear(options)

    local lang_label = menu.add_label_raw(options, {x=60, y=100, width=300, height=50}, config.get_string("language", "eng"))
    local lang_left = ui.left(options, "lang_left", shapes.rectangle(10, 100, 50, 50))
    local lang_right = ui.right(options, "lang_right", shapes.rectangle(410, 100, 50, 50))

    local vol_label = menu.add_label_raw(options, {x=60, y=150, width=300, height=50}, config.get_int("volume", 100))

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
