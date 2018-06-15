actor_speed = 0.0002

function init_actor(self)
    actor.set_scale(self, {x=0.75, y=0.75})
    actor.set_collision_bounds(self, {x=100, y=100})
end

function update_actor(self, delta)
    player = actor_manager.get_player(me.manager)
    goal = actor.get_rect(player)
    pos = actor.get_rect(self)
    vel = {x = 0, y = 0}
    old_vel = actor.get_velocity(self)

    -- @todo: library this out in lua
    vel.x = goal.x - pos.x
    vel.y = goal.y - pos.y
    -- standard normalization of vector
    len = math.sqrt((vel.x*vel.x) + (vel.y*vel.y))
    vel.x = vel.x / len
    vel.y = vel.y / len

    -- now add speed
    vel.x = vel.x * delta * actor_speed;
    vel.y = vel.y * delta * actor_speed;

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
    end,
    init = function()
        init_actor(me.self)
    end
}
