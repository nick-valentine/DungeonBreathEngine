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

local rect = nil;
local cursor_pos = {x=0, y=0}
local last_keys = {up=false, down=false, left=false, right=false}
local max_id = 0;

function marker(id, start, size)
    local mark_rect = rectangle_shape.get()
    rectangle_shape.set_size(mark_rect, {x=size.x*my_base_size, y=size.y*my_base_size})
    rectangle_shape.set_position(mark_rect, {x=start.x*my_base_size, y=start.y*my_base_size})
    rectangle_shape.set_outline_color(mark_rect, {r=255, g=0, b=255})
    rectangle_shape.set_outline_thickness(mark_rect, 1)
    rectangle_shape.set_fill_color(mark_rect, {r=0, g=0, b=0, a=0})

    local mark_label = label.get(
        {
            x=start.x*my_base_size, 
            y=start.y*my_base_size, 
            width=size.x*my_base_size,
            height=size.y*my_base_size
        },
        tostring(id)
    )
    label.set_size(mark_label, 12);

    if tonumber(id) > max_id then
        max_id = tonumber(id) + 1
    end
    local mark = {}
    mark.id = id 
    mark.label = mark_label
    mark.rect = mark_rect
    mark.pos = start
    mark.size = size
    return mark
end

function draw_marker(marker, window)
    if marker.rect then
        rectangle_shape.draw(marker.rect, window)
        label.draw(marker.label, window)
    end
end

function release_marker(marker)
    rectangle_shape.release(marker.rect)
    label.release(marker.label)
end

local markers = {}

function create_tileset(name, tex_name, base_size, anim_speed)
    local f = io.open("./GameData/tilesets/" .. name .. ".txt", "w")
    f:write(name, "\n")
    f:write("size ", base_size, "\n")
    f:write("tex ", tex_name, "\n")
    f:write("anim_speed ", anim_speed, "\n")
    f:write("---\n")
    f:close()
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

function load_line(line)
    local ints = strings.split(line, " ")
    local id = 0
    local m = {}
    for k, v in pairs(ints) do
        if k == 1 then
            id = v
        else
            m[#m+1] = v
        end
        if #m == 4 then
            markers[#markers+1] = marker(id, {x=m[1],y=m[2]}, {x=m[3], y=m[4]})
            m = {}
        end
    end
end

function load_tileset(name, tex_name, base_size, anim_speed)
    if tex_name then
        create_tileset(name, tex_name, base_size, anim_speed)
    end
    local filename = './GameData/tilesets/' .. name .. '.txt'
    local data = file.read(filename)
    load_headers(data)
    logger.info("name: ", my_name)
    logger.info("base size: ", my_base_size)
    logger.info("tex: ", my_tex)
    logger.info("anim_speed: ", my_anim_speed)
    local activate = false
    for k, v in pairs(data) do
        if v == "---" then
            activate = true
        end
        if activate then
            load_line(v)
        end
    end
end

edit_menu.init = function(name, tex_name, base_size, anim_speed)
    load_tileset(name, tex_name, base_size, anim_speed)
    spriteman = sprite_manager.get(my_tex, my_base_size);
    spr = sprite_manager.make_sprite(spriteman, {x=0, y=0}, {x=512, y=512})

    rect = rectangle_shape.get()
    rectangle_shape.set_size(rect, {x=my_base_size, y=my_base_size})
    rectangle_shape.set_position(rect, cursor_pos)
    rectangle_shape.set_outline_color(rect, {r=0, g=0, b=255})
    rectangle_shape.set_outline_thickness(rect, 1)
    rectangle_shape.set_fill_color(rect, {r=0, g=0, b=0, a=0})
end

edit_menu.update = function(delta, self)

    keys = {
        up=input.is_key_pressed(input.up),
        down=input.is_key_pressed(input.down),
        left=input.is_key_pressed(input.left),
        right=input.is_key_pressed(input.right),
    }
    if (keys.up == 1 and last_keys.up == 0) then
        cursor_pos.y = cursor_pos.y - 1
    elseif (keys.down == 1 and last_keys.down == 0) then
        cursor_pos.y = cursor_pos.y + 1
    end

    if (keys.left == 1 and last_keys.left == 0) then
        cursor_pos.x = cursor_pos.x - 1
    elseif (keys.right == 1 and last_keys.right == 0) then
        cursor_pos.x = cursor_pos.x + 1
    end
    last_keys = keys

    rectangle_shape.set_position(rect, {x=cursor_pos.x*my_base_size, y=cursor_pos.y*my_base_size})

    local camera = scene.get_camera_center(self);
    camera.x = (cursor_pos.x*my_base_size) - camera.x
    camera.y = (cursor_pos.y*my_base_size) - camera.y
    scene.move_camera(self, camera)

    local old_scale_factor = scale_factor;
    imgui.start("tileset edit menu");
    scale_factor = imgui.input_int("scale factor: ", scale_factor)
    my_name = imgui.input_text("name: ", my_name)
    my_base_size = imgui.input_int("base size: ", my_base_size)
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
    for k, v in pairs(markers) do
        draw_marker(v, window)
    end
    if rect then
        rectangle_shape.draw(rect, window)
    end
end

edit_menu.release = function()
    sprite_manager.release(spriteman)
    for k, v in pairs(markers) do
        release_marker(v)
    end
end

edit_menu.message = function()
    local signal = edit_menu.signal
    edit_menu.signal = nil
    return signal
end

return edit_menu
