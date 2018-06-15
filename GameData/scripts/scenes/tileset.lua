local checked = 0;
local input_text_field = "";
local input_int_field = 0;
local input_float_field = 0;
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
        imgui.text("hello progress:");
        imgui.progressbar(0.5)
        input_text_field = imgui.input_text("input text: ", input_text_field)
        input_int_field = imgui.input_int("input int: ", input_int_field)
        input_float_field = imgui.input_float("input float: ", input_float_field)
        imgui.stop()
    end,
    wakeup = function()

    end,
}
