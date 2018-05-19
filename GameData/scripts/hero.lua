function update(delta)
	print(input.is_key_pressed(input.device, input.up))
end

me = {
	tileset = "hero",
	update = update,
}