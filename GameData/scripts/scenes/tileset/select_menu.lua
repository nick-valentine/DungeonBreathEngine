local select_menu = {};
select_menu.signal = {}

local tileset_name = ""
local spritesheet_name = ""
local base_size = 0

select_menu.init = function()

end

select_menu.update = function(delta)
    imgui.start("new tileset")
    tileset_name = imgui.input_text("tileset name: ", tileset_name)
    spritesheet_name = imgui.input_text("spritesheet name: ", spritesheet_name)
    base_size = imgui.input_int("base size: ", base_size)
    if imgui.button("next") == 1.0 then
        select_menu.signal.name = tileset_name
        select_menu.signal.spritesheet = spritesheet_name
        select_menu.base_size = base_size
    end
    imgui.stop()
end

select_menu.draw = function(window)

end

select_menu.message = function()
    return select_menu.signal
end

return select_menu;
