local spr = nil;
local meTile = nil;

function init_actor(self)
    actor_manager.set_camera_target(me.manager, me.handle)
    actor_manager.set_player(me.manager, me.handle)
    actor.set_scale(self, {x=0.75, y=0.75})
    actor.set_origin(self, {x=9, y=1})
    actor.set_collision_bounds(self, {x=50, y=80})

    local spr_man = sprite_manager.get("Overworld.png", 16);
    spr = sprite_manager.make_sprite(spr_man, {x=0, y=0}, {x=1, y=1})
    local tset = tile_set.get("hero")
    meTile = tile_set.get_tile(tset, 1);
    tile.set_scale(meTile, {x=0.2, y=0.2})
end

function update_actor(self, delta)
    vel = {x = 0, y = 0}
    old_vel = actor.get_velocity(self)
    if (input.is_key_pressed(input.up) == 1.0) then
        vel.y = -5
    elseif (input.is_key_pressed(input.down) == 1.0) then
        vel.y = 5
    end

    if (input.is_key_pressed(input.left) == 1.0) then
        vel.x = -5
    elseif (input.is_key_pressed(input.right) == 1.0) then
        vel.x = 5
    end

    if vel.x ~= old_vel.x or vel.y ~= old_vel.y then
        anim_changed = false
        if (vel.x > 0) then
            actor.set_tileset(self, 2)
            anim_changed = true
        elseif (vel.x < 0) then
            actor.set_tileset(self, 3)
            anim_changed = true
        end

        if (vel.y > 0) then
            actor.set_tileset(self, 0)
            anim_changed = true
        elseif (vel.y < 0) then
            actor.set_tileset(self, 1)
            anim_changed = true
        end

        if anim_changed then
            actor.reset_anim(self)
        end
    end

    if vel.x == 0 and vel.y == 0 then
        actor.pause_anim(self)
    else
        actor.play_anim(self)
    end

    actor.set_velocity(self, vel)

    local target_rect = actor.get_rect(me.self)
    sprite.set_position(spr, target_rect)
    tile.set_position(meTile, target_rect)
    tile.update(meTile, delta)
end

me = {
    tileset = "hero",
    update = function(delta)
        update_actor(me.self, delta)
    end,
    init = function()
        init_actor(me.self)
    end,
    draw = function(window)
        actor.draw(me.self, window)
        sprite.draw(spr, window)
        tile.draw(meTile, window)
    end
}
