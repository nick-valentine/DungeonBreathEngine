local checked = 0;
me = {
    init = function()

    end,
    update = function(delta)
        imgui.start("tileset editor")
        if imgui.button("hello world!") == 1.0 then
            logger.info("hello world!")
        end
        checked = imgui.checkbox("this is checkbox", checked)
        if  checked == 1.0 then
            logger.info("checkbox is checked")
        end
        imgui.progressbar(0.5)
        imgui.stop()
    end,
    wakeup = function()

    end,
}
