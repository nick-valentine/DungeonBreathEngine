function update_actor(self, delta)
		-- rect = actor.get_rect(me.self)
		--print(rect.left, rect.top, rect.width, rect.height)
		--print(input.is_key_pressed(input.device, input.up))
		vel = {x = 0, y = 0}
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
		
		actor.set_velocity(me.self, vel)
end

me = {
	tileset = "hero",
	update = function(delta)
		update_actor(me.self, delta)
	end
}