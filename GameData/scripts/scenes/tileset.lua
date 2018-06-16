package.path = package.path .. ";GameData/scripts/scenes/tileset/?.lua"
local select_menu = require 'select_menu'
local edit_menu = require 'edit_menu'

local c_choose_menu = 0;
local c_edit_menu = 1;

local state = c_choose_menu

local name;
local tex_name;
local base_size;

me = {
    init = function()
        if state == c_choose_menu then
            select_menu.init()
        end
    end,
    update = function(delta)
        if state == c_choose_menu then
            select_menu.update(delta)
            local m = select_menu.message()
            if m then
                logger.info(m.name)
                logger.info(m.spritesheet)
                logger.info(m.base_size)
                logger.info(m.existing_name)
                name = m.name
                tex_name = m.spritesheet
                base_size = m.base_size
                state = c_edit_menu
                edit_menu.init(name, tex_name, base_size)
            end
        elseif state == c_edit_menu then
            edit_menu.update(delta, me.self)
        end
    end,
    draw = function(window)
        scene.draw(me.self, window)
        if state == c_choose_menu then
            select_menu.draw(window)
        elseif state == c_edit_menu then
            edit_menu.draw(window)
        end
    end,
    wakeup = function()

    end,
    release = function()
        edit_menu.release()
    end,
}
