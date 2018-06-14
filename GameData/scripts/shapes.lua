local shapes = {}

shapes.rectangle = function(x, y, width, height)
    x = x or 0
    y = y or 0
    width = width or 0
    height = height or 0
    return {x=x, y=y, width=width, height=height}
end

return shapes;
