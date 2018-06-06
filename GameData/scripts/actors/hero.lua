function update_actor(self, delta)
    actor_manager.set_camera_target(me.manager, me.handle)
    actor.set_scale(self, {x=0.75, y=0.75})
    actor.set_collision_bounds(self, {x=100, y=100})
    -- rect = actor.get_rect(me.self)
    --print(rect.left, rect.top, rect.width, rect.height)
    --print(input.is_key_pressed(input.device, input.up))
    vel = {x = 0, y = 0}
    old_vel = actor.get_velocity(self)
    if (input.is_key_pressed(input.device, input.up) == 1.0) then
        --print("setting velocity to minus 50")
        vel.y = -5
    elseif (input.is_key_pressed(input.device, input.down) == 1.0) then
        vel.y = 5
    end
    
    if (input.is_key_pressed(input.device, input.left) == 1.0) then
        vel.x = -5
    elseif (input.is_key_pressed(input.device, input.right) == 1.0) then
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
end

me = {
    tileset = "hero",
    update = function(delta)
        update_actor(me.self, delta)
    end
}
