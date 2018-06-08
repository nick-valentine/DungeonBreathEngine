print("Hello World")
print("Volume: ", config.get_int("volume", 100))
print("Accept Button:",  config.get_string("accept", "enter"))

config.set("volume", 40)
config.set("accept", "k:g")

print("Volume: ", config.get_int("volume", 100))
print("Accept Button:",  config.get_string("accept", "enter"))


logger.info("hi", 5, 7)
logger.debug("how")
logger.warn("are")
logger.error("you")

logger.debug(input.is_key_pressed(input.device, input.up));
