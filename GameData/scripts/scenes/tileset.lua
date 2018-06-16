package.path = package.path .. ";GameData/scripts/scenes/tileset/?.lua"
local select_menu = require 'select_menu'
local checked = 0;
local input_text_field = "";
local input_int_field = 0;
local input_float_field = 0;
local list_input = 0;
me = {
    init = function()
        select_menu.init()
    end,
    update = function(delta)
        select_menu.update(delta)
        local m = select_menu.message()
        if not m == {} then
            logger.info(m.name)
            logger.info(m.spritesheet)
            logger.info(m.base_size)
        end
    end,
    draw = function(window)
        select_menu.draw(window)
    end,
    wakeup = function()

    end,
}
