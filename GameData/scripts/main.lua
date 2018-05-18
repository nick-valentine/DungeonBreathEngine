print("Hello World")
print("Volume: ", config.get_int("volume", 100))
print("Accept Button:",  config.get_string("accept", "enter"))

config.set("volume", 40)
config.set("accept", "k:g")

print("Volume: ", config.get_int("volume", 100))
print("Accept Button:",  config.get_string("accept", "enter"))


logger.info(logger.log, "hi", 5, 7)
logger.debug(logger.log, "how")
logger.warn(logger.log, "are")
logger.error(logger.log, "you")
