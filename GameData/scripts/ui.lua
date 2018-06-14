local ui = {}

ui.tex = "RPG_GUI_v1.png"

-- @todo add text button to remove that from engine

ui.left = function(m, tag, rect)
    return menu.add_sprite_button(
        m, tag, rect, ui.tex,
        {x=320, y=60,  width=40, height=40},
        {x=320, y=110, width=40, height=40},
        {x=320, y=10,  width=40, height=40}
    )
end

ui.right = function(m, tag, rect)
    return menu.add_sprite_button(
        m, tag, rect, ui.tex,
        {x=360, y=60,  width=40, height=40},
        {x=360, y=110, width=40, height=40},
        {x=360, y=10,  width=40, height=40}
    )
end

return ui;
