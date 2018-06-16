package.path = package.path .. ";GameData/scripts/?.lua"
local file = require 'file'
local strings = require 'strings'
local edit_menu = {};
edit_menu.signal = nil

local spriteman = nil
local spr = nil

local my_name = ""
local my_base_size = 16
local my_tex = ""
local my_anim_speed = 30

local scale_factor = 1
local current_pos = {x=0, y=0}

function create_tileset(name, tex_name, base_size)
end

function load_headers(data)
    for k, v in pairs(data) do
        if v == "---" then
            return
        end
        if k == 1 then
            my_name = v
        end
        local pair = strings.split(v, ' ')
        if pair[1] == "size" then
            my_base_size = tonumber(pair[2])
        elseif pair[1] == "tex" then
            my_tex = pair[2]
        elseif pair[1] == "anim_speed" then
            my_anim_speed = tonumber(pair[2])
        end
    end
end

function load_tileset(name, tex_name, base_size)
    if tex_name then
        create_tileset(name, tex_name, base_size)
    end
    local filename = './GameData/tilesets/' .. name .. '.txt'
    local data = file.read(filename)
    load_headers(data)
    logger.info("name: ", my_name)
    logger.info("base size: ", my_base_size)
    logger.info("tex: ", my_tex)
    logger.info("anim_speed: ", my_anim_speed)
end

edit_menu.init = function(name, tex_name, base_size)
    load_tileset(name, tex_name, base_size)
    spriteman = sprite_manager.get(my_tex, my_base_size);
    spr = sprite_manager.make_sprite(spriteman, {x=1, y=1}, {x=512, y=512})
end

edit_menu.update = function(delta, self)
    local camera = scene.get_camera_center(self);
    camera.x = current_pos.x - camera.x
    camera.y = current_pos.y - camera.y
    scene.move_camera(self, camera)
    logger.info("camera", camera.x, camera.y)
    logger.info("curr", current_pos.x, current_pos.y)

    if (input.is_key_pressed(input.up) == 1.0) then
        current_pos.y = current_pos.y - 5
    elseif (input.is_key_pressed(input.down) == 1.0) then
        current_pos.y = current_pos.y + 5
    end

    if (input.is_key_pressed(input.left) == 1.0) then
        current_pos.x = current_pos.x - 5
    elseif (input.is_key_pressed(input.right) == 1.0) then
        current_pos.x = current_pos.x + 5
    end

    local old_scale_factor = scale_factor;
    imgui.start("tileset edit menu");
    scale_factor = imgui.input_int("scale factor: ", scale_factor)
    imgui.stop()

    if not (old_scale_factor == scale_factor) then
        if old_scale_factor > scale_factor then
            scene.zoom_camera(self, 1+1/4);
        else
            scene.zoom_camera(self, 1-1/4);
        end
    end
end

edit_menu.draw = function(window)
    if spr then
        sprite.draw(spr, window)
    end
end

edit_menu.release = function()
    sprite_manager.release(spriteman)
end

edit_menu.message = function()
    local signal = edit_menu.signal
    edit_menu.signal = nil
    return signal
end

return edit_menu
