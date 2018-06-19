local my_base_size = 64

local edit_menu = {}

edit_menu.signal = nil

edit_menu.world = nil
edit_menu.actorman = nil
edit_menu.scale_factor = 1.0

edit_menu.layers = {}

edit_menu.tiles = {}
edit_menu.actors = {}

local cursor = {}
cursor.rect = nil;
cursor.pos = {x=0, y=0}
cursor.target = {}
cursor.layer = 0
cursor.sprite = nil
cursor.label = nil
cursor.collision_type = 0

function reset_cursor(c)
    if c.label then
        label.release(c.label)
        c.label = nil
    end
    c.label = nil
    c.sprite = nil
end

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

edit_menu.init_tiles = function(signal)
    local tset = tile_set.get(signal.tileset)

    local keys = tile_set.keys(tset)
    for k, v in pairs(keys) do
        local index = #edit_menu.tiles+1
        edit_menu.tiles[index] = {}
        edit_menu.tiles[index].tile = tile_set.get_tile(tset, v)
        edit_menu.tiles[index].sprite = tile.get_icon(edit_menu.tiles[index].tile)
    end

    tile_set.release(tset)
end

edit_menu.init_actors = function()
    local idx = index.get("./GameData/scripts/actors")
    local actors = index.all(idx)
    for k, v in pairs(actors) do
        local i = #edit_menu.actors+1
        edit_menu.actors[i] = {}
        edit_menu.actors[i].name = v
    end
    index.release(idx)
end

edit_menu.init = function(self, signal)

    for i = 0, 10 do
        edit_menu.layers[#edit_menu.layers + 1] = {draw= true}
    end

    scene.init_world(self)
    edit_menu.world = scene.get_world(self)
    edit_menu.actorman = world.get_actorman(edit_menu.world)
    if signal.tileset then
        logger.info("creating file")
        edit_menu.write_level_header(signal)
        -- collision
        edit_menu.write_default_layer(signal)
        -- layer 1
        edit_menu.write_default_layer(signal)
    end
    world.change_level(edit_menu.world, signal.name, {x=-1, y=-1})

    local world_size = world.get_size(edit_menu.world)
    signal.size_x = world_size.x
    signal.size_y = world_size.y
    signal.tileset = world.get_tileset(edit_menu.world)
    signal.script = world.get_script_name(edit_menu.world)

    cursor.rect = rectangle_shape.get()
    rectangle_shape.set_size(cursor.rect, {x=my_base_size, y=my_base_size})
    rectangle_shape.set_position(cursor.rect, cursor.pos)
    rectangle_shape.set_outline_color(cursor.rect, {r=0, g=0, b=255})
    rectangle_shape.set_outline_thickness(cursor.rect, 1)
    rectangle_shape.set_fill_color(cursor.rect, {r=0, g=0, b=0, a=0})

    edit_menu.init_tiles(signal)
    edit_menu.init_actors()
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
    if cursor.sprite then
        sprite.set_position(cursor.sprite, {x=cursor.pos.x*my_base_size, y=cursor.pos.y*my_base_size})
    end
    if cursor.label then
        label.set_position(cursor.label, {x=cursor.pos.x*my_base_size, y=cursor.pos.y*my_base_size, width=100, height=50})
    end
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

edit_menu.update_actor_select = function()
    imgui.start("actors")
    for k, v in pairs(edit_menu.actors) do
        if imgui.button(v.name) == 1.0 then
            reset_cursor(cursor)
            cursor.target = {}
            cursor.target.actor = v.name
            local pos = {}
            pos.x = cursor.pos.x
            pos.y = cursor.pos.y
            pos.width = 100
            pos.height = 50
            lab = label.get(pos, v.name)
            cursor.label = lab
        end
    end
    imgui.stop()
end

edit_menu.update_tile_menu = function(self)
    imgui.start("tiles")
    for k, v in pairs(edit_menu.tiles) do
        imgui.start_child("tile: " .. k, {x=60, y=60})
        if imgui.image_button(v.sprite) == 1.0 then
            reset_cursor(cursor)
            cursor.target = {}
            cursor.target.tile = k
            cursor.sprite = v.sprite
        end
        imgui.stop_child()
    end
    imgui.stop()
end

edit_menu.update = function(self, delta)
    edit_menu.world = scene.get_world(self)
    edit_menu.actorman = world.get_actorman(edit_menu.world)
    world.set_edit_mode(edit_menu.world, 1.0)

    edit_menu.update_cursor(self, delta)

    imgui.start("level edit menu")
    edit_menu.update_scale_factor(self)
    cursor.layer = imgui.input_int("layer", cursor.layer)
    cursor.collision_type = imgui.input_int("collision type", cursor.collision_type)
    if imgui.button("add collision") == 1.0 then
        world.add_collision(
            edit_menu.world,
            cursor.collision_type,
            {x=cursor.pos.x*my_base_size, y=cursor.pos.y*my_base_size}
        )
    end
    if imgui.button("add") == 1.0 then
        if cursor.target.tile then
            world.set_tile(
                edit_menu.world, 
                edit_menu.tiles[cursor.target.tile].tile,
                cursor.layer,
                cursor.pos
            )
        end
        if cursor.target.actor then
            world.add_actor(
                edit_menu.world,
                cursor.target.actor,
                {x=cursor.pos.x*my_base_size, y=cursor.pos.y*my_base_size}
            )
        end
    end
    if imgui.button("save") == 1.0 then
        world.save_edits(edit_menu.world)
    end
    if imgui.button("exit") == 1.0 then
        edit_menu.signal = {pop= true}
    end
    imgui.stop()

    edit_menu.update_layer_render(self)
    edit_menu.update_tile_menu(self)
    edit_menu.update_actor_select(self)

    local camera = scene.get_camera_center(self);
    camera.x = (cursor.pos.x*my_base_size) - camera.x
    camera.y = (cursor.pos.y*my_base_size) - camera.y
    scene.move_camera(self, camera)
end

edit_menu.draw = function(self, window)
    scene.apply_view(self, window)
    for k, v in pairs(edit_menu.layers) do
        if v.draw then
            world.draw_layer(edit_menu.world, window, k-1)
        end
        if k == 5 then
            world.draw_actors(edit_menu.world, window)
        end
    end
    if cursor.rect then
        rectangle_shape.draw(cursor.rect, window)
    end
    if cursor.sprite then
        sprite.draw(cursor.sprite, window)
    end
    if cursor.label then
        label.draw(cursor.label, window)
    end
end

edit_menu.message = function()
    local signal = edit_menu.signal
    edit_menu.signal = nil
    return signal;
end

edit_menu.release = function()
    reset_cursor(cursor)
    cursor.pos = {x=0, y=0}
    cursor.layer = 0
    if cursor.rect then
        rectangle_shape.release(cursor.rect)
    end
    cursor.rect = nil;

    last_keys = {up=false, down=false, left=false, right=false}

    for k, v in pairs(edit_menu.tiles) do
        tile.release(v.tile)
    end
    edit_menu.tiles = {}
    edit_menu.actors = {}
end

return edit_menu
