package.path = package.path .. ";GameData/scripts/scenes/tileset/?.lua"
local select_menu = require 'select_menu'
local edit_menu = require 'edit_menu'

local c_choose_menu = 0;
local c_edit_menu = 1;

local state = c_choose_menu

local name;
local tex_name;
local base_size;
local anim_speed;

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
                if m.back and m.back == true then
                    scene.pop(me.self)
                    return
                end
                logger.info(m.name)
                logger.info(m.spritesheet)
                logger.info(m.base_size)
                logger.info(m.existing_name)
                logger.info(m.anim_speed)
                name = m.name
                tex_name = m.spritesheet
                base_size = m.base_size
                anim_speed = m.anim_speed
                state = c_edit_menu
                edit_menu.init(name, tex_name, base_size, anim_speed)
            end
        elseif state == c_edit_menu then
            edit_menu.update(delta, me.self)
            local m = edit_menu.message()
            if m == "pop" then
                edit_menu.reset()
                state = c_choose_menu
            end
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
