package.path = package.path .. ";GameData/scripts/?.lua"
local shapes = require 'shapes'
local music_list = require 'music_list'
local ui = require 'ui'

local options = nil;
local size = nil;

local vol_amount_label = nil;
local current_volume = nil;

function set_volume()
    local raw_label = menu_item.raw(vol_amount_label)
    label.set_string(raw_label, string.format("%.1f", current_volume))
    config.set("volume", current_volume)
    music.set_volume(current_volume)
end

function build_menu()
    menu.clear(options)

    local lang_label = menu.add_label_raw(options, {x=60, y=100, width=300, height=50}, config.get_string("language", "eng"))
    local lang_left = ui.left(options, "lang_left", shapes.rectangle(10, 100, 50, 50))
    local lang_right = ui.right(options, "lang_right", shapes.rectangle(410, 100, 50, 50))

    local vol_label = menu.add_label(options, shapes.rectangle(10, 150, 200, 50), "optionsmenu.volume_label")
    vol_amount_label = menu.add_label_raw(options, {x=260, y=150, width=300, height=50}, current_volume)

    local vol_left = ui.left(options, "vol_left", shapes.rectangle(200, 150, 50, 50))
    local vol_right = ui.right(options, "vol_right", shapes.rectangle(350, 150, 50, 50))

    local key_bindings_button = ui.textbutton(options, "key_bind", {x=10, y=size.y-160}, "optionsmenu.key_bind_button").button
    local exit_button = ui.textbutton(options, "exit", {x=10, y=size.y-100}, "optionsmenu.back_button").button

    menu.set_current(options, lang_left)
    menu_item.pair_items(lang_left, lang_right, menu_item.right)
    menu_item.pair_items(lang_left, vol_left, menu_item.down)
    menu_item.pair_items(lang_right, vol_right, menu_item.down)
    menu_item.pair_items(vol_left, vol_right, menu_item.right)
    menu_item.pair_items(vol_left, key_bindings_button, menu_item.down)
    menu_item.set_down(vol_right, key_bindings_button)
    menu_item.pair_items(key_bindings_button, exit_button, menu_item.down)
end

me = {
    init = function()
        current_volume = config.get_int("volume", 100)
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
        elseif pressed == "vol_left" then
            current_volume = current_volume - 5
            if current_volume < 0 then
                current_volume = 0
            end
            set_volume()
        elseif pressed == "vol_right" then
            current_volume = current_volume + 5
            if current_volume > 100 then
                current_volume = 100
            end
            set_volume()
        elseif pressed == "key_bind" then
            logger.warn("key binding not implemented")
        elseif pressed == "exit" then
            config.save()
            scene.pop(me.self)
        end
    end,
    wakeup = function()
        music.play(music_list.menu)
    end
}
