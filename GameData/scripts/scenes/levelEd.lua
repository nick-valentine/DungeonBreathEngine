package.path = package.path .. ";GameData/scripts/scenes/levelEd/?.lua"
local select_menu = require 'select_menu'
local edit_menu = require 'edit_menu'

local c_choose_menu = 0;
local c_edit_menu = 1;

me = {}

me.state = c_choose_menu

me.init = function()
    select_menu.init()

end

me.update = function(delta)
    if me.state == c_choose_menu then
        select_menu.update(me.self, delta)
        local m = select_menu.message()
        if m then
            if m.pop and m.pop == true then
                scene.pop(me.self)
            else
                edit_menu.init(me.self, m)
                me.state = c_edit_menu
            end
        end
    elseif me.state == c_edit_menu then
        edit_menu.update(me.self, delta)
    end
end

me.draw = function(window)
    if me.state == c_choose_menu then
        select_menu.draw(me.self, window)
    elseif me.state == c_edit_menu then
        edit_menu.draw(me.self, window)
    end
end

me.release = function()
    select_menu.release()
    edit_menu.release()
end
