local my_base_size = 64

local edit_menu = {}

edit_menu.signal = nil

edit_menu.world = nil
edit_menu.actorman = nil
edit_menu.scale_factor = 1.0

edit_menu.layers = {}

local cursor = {}
cursor.rect = nil;
cursor.pos = {x=0, y=0}

local last_keys = {up=false, down=false, left=false, right=false}

edit_menu.write_level_header = function(signal)
    logger.info("writing header")
    local f = io.open("./GameData/levels/" .. signal.name .. ".txt", "w")
    f:write(signal.name, "\n")
    f:write(signal.tileset, "\n")
    f:write(signal.size_x, " ", signal.size_y, "\n")
    f:write(signal.script, "\n")
    f:write("---\n")
    f:write("none\n") -- none is sentinel for skip for actors
    f:write("---\n")
    f:write("0 0 0\n") -- collision type 0 will never trigger
    f:write("---\n")
    f:close()
end

edit_menu.write_default_layer = function(signal)
    local f = io.open("./GameData/levels/" .. signal.name .. ".txt", "a")
    for i=0, signal.size_y do
        for j=0, signal.size_x do
            f:write("0 ")
        end
        f:write("\n")
    end
    f:write("---\n")
end

edit_menu.init = function(self, signal)

    for i = 0, 10 do
        edit_menu.layers[#edit_menu.layers + 1] = {draw= true}
    end

    scene.init_world(self)
    edit_menu.world = scene.get_world(self)
    edit_menu.actorman = world.get_actorman(edit_menu.world)
    world.set_edit_mode(edit_menu.world, 1.0)
    if signal.tileset then
        logger.info("creating file")
        edit_menu.write_level_header(signal)
        -- collision
        edit_menu.write_default_layer(signal)
        -- layer 1
        edit_menu.write_default_layer(signal)
    end
    world.change_level(edit_menu.world, signal.name, {x=-1, y=-1})
    world.set_edit_mode(edit_menu.world, 1.0)

    cursor.rect = rectangle_shape.get()
    rectangle_shape.set_size(cursor.rect, {x=my_base_size, y=my_base_size})
    rectangle_shape.set_position(cursor.rect, cursor.pos)
    rectangle_shape.set_outline_color(cursor.rect, {r=0, g=0, b=255})
    rectangle_shape.set_outline_thickness(cursor.rect, 1)
    rectangle_shape.set_fill_color(cursor.rect, {r=0, g=0, b=0, a=0})
end

edit_menu.update_cursor = function(self, delta)
    keys = {
        up=input.is_key_pressed(input.up),
        down=input.is_key_pressed(input.down),
        left=input.is_key_pressed(input.left),
        right=input.is_key_pressed(input.right),
    }

    if (keys.up == 1 and last_keys.up == 0) then
        cursor.pos.y = cursor.pos.y - 1
    elseif (keys.down == 1 and last_keys.down == 0) then
        cursor.pos.y = cursor.pos.y + 1
    end

    if (keys.left == 1 and last_keys.left == 0) then
        cursor.pos.x = cursor.pos.x - 1
    elseif (keys.right == 1 and last_keys.right == 0) then
        cursor.pos.x = cursor.pos.x + 1
    end

    rectangle_shape.set_position(cursor.rect, {x=cursor.pos.x*my_base_size, y=cursor.pos.y*my_base_size})
    last_keys = keys
end

edit_menu.update_scale_factor = function(self)
    local old_scale_factor = edit_menu.scale_factor;
    edit_menu.scale_factor = imgui.input_int("scale factor", edit_menu.scale_factor)
    if not (old_scale_factor == edit_menu.scale_factor) then
        if old_scale_factor > edit_menu.scale_factor then
            scene.zoom_camera(self, 1+1/4);
        else
            scene.zoom_camera(self, 1-1/4);
        end
    end
end

edit_menu.update_layer_render = function(self)
    imgui.start("layers")
    for k, v in pairs(edit_menu.layers) do
        local label = "don't "
        if not v.draw then
            label = "do "
        end
        if imgui.button(label .. "render layer: " .. k) == 1.0 then
            v.draw = not v.draw
        end
    end
    imgui.stop()
end

edit_menu.update = function(self, delta)
    edit_menu.world = scene.get_world(self)
    edit_menu.actorman = world.get_actorman(edit_menu.world)

    edit_menu.update_cursor(self, delta)

    imgui.start("level edit menu")
    edit_menu.update_scale_factor(self)
    imgui.stop()

    edit_menu.update_layer_render(self)

    local camera = scene.get_camera_center(self);
    camera.x = (cursor.pos.x*my_base_size) - camera.x
    camera.y = (cursor.pos.y*my_base_size) - camera.y
    scene.move_camera(self, camera)
end

edit_menu.draw = function(self, window)
    -- scene.draw(self, window)
    scene.apply_view(self, window)
    for k, v in pairs(edit_menu.layers) do
        if v.draw then
            world.draw_layer(edit_menu.world, window, k-1)
        end
        if v == 5 then
            world.draw_actors(edit_menu.world, window)
        end
    end
    rectangle_shape.draw(cursor.rect, window)
end

edit_menu.message = function()
    local signal = edit_menu.signal
    edit_menu.signal = nil
    return signal;
end

edit_menu.release = function()
    cursor = {}
    cursor.rect = nil;
    cursor.pos = {x=0, y=0}

    last_keys = {up=false, down=false, left=false, right=false}
end

return edit_menu
