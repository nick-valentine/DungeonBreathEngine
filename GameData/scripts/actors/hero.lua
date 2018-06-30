local spr_man = nil;
local spr = nil;
local meTile = nil;

me = {}

me.tileset = "hero"
me.footsteps = nil
me.particles = nil

me.init = function()
    actor_manager.set_camera_target(me.manager, me.handle)
    actor_manager.set_player(me.manager, me.handle)
    actor.set_scale(me.self, {x=0.75, y=0.75})
    actor.set_origin(me.self, {x=9, y=1})
    actor.set_collision_bounds(me.self, {x=50, y=80})

    spr_man = sprite_manager.get("Overworld.png", 16)
    spr = sprite_manager.make_sprite(spr_man, {x=0, y=0}, {x=1, y=1})
    local tset = tile_set.get("hero")
    meTile = tile_set.get_tile(tset, 1);
    tile.set_scale(meTile, {x=0.2, y=0.2})
    tile_set.release(tset)

    me.footsteps = sound.get("./GameData/sound/inventory/cloth.wav")
    sound.set_loop(me.footsteps, 1.0)
    sound.set_volume(me.footsteps, 25)

    me.particles = particle_effect.get("Overworld.png", 16, 
        {x=16, y=16}, 
        {x=16, y=16},
        {x=16, y=16},
        {x=10, y=10},
        {x=-4, y=0},
        {x=2, y=0},
        10,
        2,
        1000,
        1000
    )
end

me.update_velocity = function(vel, delta)
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
    return vel
end

me.update_animation = function(vel, old_vel, delta)
    if vel.x ~= old_vel.x or vel.y ~= old_vel.y then
        local anim_changed = false
        if (vel.x > 0) then
            actor.set_tileset(me.self, 2)
            anim_changed = true
        elseif (vel.x < 0) then
            actor.set_tileset(me.self, 3)
            anim_changed = true
        end

        if (vel.y > 0) then
            actor.set_tileset(me.self, 0)
            anim_changed = true
        elseif (vel.y < 0) then
            actor.set_tileset(me.self, 1)
            anim_changed = true
        end

        if anim_changed then
            actor.reset_anim(me.self)
        end
    end

    if vel.x == 0 and vel.y == 0 then
        actor.pause_anim(me.self)
        sound.pause(me.footsteps)
    else
        actor.play_anim(me.self)
        if sound.is_playing(me.footsteps) == 0.0 then
            sound.play(me.footsteps)
        end
    end
end

me.update = function(delta)
    local vel = {x = 0, y = 0}
    local old_vel = actor.get_velocity(me.self)

    vel = me.update_velocity(vel, delta)

    me.update_animation(vel, old_vel, delta)

    actor.set_velocity(me.self, vel)

    local target_rect = actor.get_rect(me.self)
    sprite.set_position(spr, target_rect)
    tile.set_position(meTile, target_rect)
    tile.update(meTile, delta)

    particle_effect.update(me.particles, delta)
end

me.draw = function(window)
    actor.draw(me.self, window)
    sprite.draw(spr, window)
    tile.draw(meTile, window)
    particle_effect.draw(me.particles, window)
end

me.hurt = function(pain)
    logger.info(pain.raw_damage, pain.force.x, pain.force.y)
end

me.collide = function(other)
    logger.info("i am colliding")
end

me.release = function()
    sprite_manager.remove_sprite(spr_man, spr)
    sprite_manager.release(spr_man)
    tile.release(meTile)
    sound.release(me.footsteps)
    particle_effect.release(me.particles)
end

