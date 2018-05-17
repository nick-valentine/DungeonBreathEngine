print("Hello World")
print("Volume: ", config.get_int("volume", 100))
print("Accept Button:",  config.get_string("accept", "enter"))

config.set("volume", 40)
config.set("accept", "k:g")

print("Volume: ", config.get_int("volume", 100))
print("Accept Button:",  config.get_string("accept", "enter"))
