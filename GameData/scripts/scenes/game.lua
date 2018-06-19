package.path = package.path .. ";GameData/scripts/?.lua"
local music_list = require 'music_list'

local camera_lag = 10.0

local my_world = nil
local my_actorman = nil

function update_camera(self, target)
    local camera = scene.get_camera_center(self)
    local target_rect = actor.get_rect(target)
    target_rect.x = target_rect.x + (target_rect.width / 2)
    target_rect.y = target_rect.y + (target_rect.height / 2)

    camera_diff = {}
    camera_diff.x = (target_rect.x - camera.x) / camera_lag
    camera_diff.y = (target_rect.y - camera.y) / camera_lag
    scene.move_camera(self, camera_diff)
end

me = {
    init = function()
        scene.init_world(me.self)
        my_world = scene.get_world(me.self)
        my_actorman = world.get_actorman(my_world)
    end,
    update = function(delta)
        my_world = scene.get_world(me.self)
        my_actorman = world.get_actorman(my_world)
        local target = actor_manager.get_camera_target(my_actorman)
        if target then
            update_camera(me.self, target)
        end
    end,
    wakeup = function()
        music.play(music_list.overworld)
    end,
    draw = function(window)
        scene.draw(me.self, window)
    end
}
