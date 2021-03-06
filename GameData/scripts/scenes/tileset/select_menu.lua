local select_menu = {};
select_menu.signal = nil

local tileset_name = ""
local spritesheet_name = ""
local base_size = 0
local anim_speed = 20
local idx = nil
local dir_items = {}

select_menu.init = function()
    idx = index.get("GameData/tilesets");
    dir_items = index.all(idx)
end

select_menu.update = function(delta)
    imgui.start("new tileset")
    tileset_name = imgui.input_text("tileset name: ", tileset_name)
    spritesheet_name = imgui.input_text("spritesheet name: ", spritesheet_name)
    base_size = imgui.input_int("base size: ", base_size)
    anim_speed = imgui.input_int("anim speed: ", anim_speed)
    if imgui.button("next") == 1.0 then
        select_menu.signal = {}
        select_menu.signal.name = tileset_name
        select_menu.signal.spritesheet = spritesheet_name
        select_menu.signal.base_size = base_size
        select_menu.signal.anim_speed = anim_speed
        index.add(idx, tileset_name);
        index.save(idx)
    end
    if imgui.button("back") == 1.0 then
        select_menu.signal = {}
        select_menu.signal.back = true
    end
    imgui.stop()
    imgui.start("existing tilesets")
    for k, v in pairs(dir_items) do
        if imgui.button(v) == 1.0 then
            select_menu.signal = {}
            select_menu.signal.name = v
        end
    end
    imgui.stop()
end

select_menu.draw = function(window)

end

select_menu.message = function()
     local signal = select_menu.signal
     select_menu.signal = nil
     return signal
end

return select_menu;
