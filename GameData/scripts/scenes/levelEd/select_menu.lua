local select_menu = {}
select_menu.signal = nil

select_menu.current = {}
select_menu.current.name = ""
select_menu.current.tileset = ""
select_menu.current.size_x = 0
select_menu.current.size_y = 0

select_menu.index = nil
select_menu.dir_items = {}

select_menu.init = function()
    select_menu.index = index.get("GameData/levels");
    select_menu.dir_items = index.all(select_menu.index);
end

select_menu.update = function(self, delta)
    imgui.start("new level")
    select_menu.current.name = imgui.input_text("level name", select_menu.current.name)
    select_menu.current.tileset = imgui.input_text("tileset", select_menu.current.tileset)
    select_menu.current.size_x = imgui.input_int("size x", select_menu.current.size_x)
    select_menu.current.size_y = imgui.input_int("size y", select_menu.current.size_y)
    if imgui.button("next") == 1.0 then
        select_menu.signal = select_menu.current
    end
    if imgui.button("back") == 1.0 then
        select_menu.signal = {}
        select_menu.signal.pop = true
    end
    imgui.stop()
    imgui.start("existing levels")
        for k, v in pairs(select_menu.dir_items) do
            if imgui.button(v) == 1.0 then
                select_menu.signal = {}
                select_menu.signal.name = v
            end
        end
    imgui.stop()
end

select_menu.draw = function(self, window)

end

select_menu.message = function()
    local signal = select_menu.signal
    select_menu.signal = nil
    return signal
end

select_menu.release = function()

end

return select_menu;
