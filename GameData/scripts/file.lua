local file = {}

file.exists = function(name)
    local f = io.open(name, "rb")
    if f then f:close() end
    return f ~= nil
end

file.read = function(name)
    if not file.exists(name) then
        return {}
    end
    lines = {}
    for line in io.lines(name) do
        lines[#lines + 1] = line
    end
    return lines
end

return file;
