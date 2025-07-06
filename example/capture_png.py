"""
Example: save the first color and depth frames to PNG images.

This example uses only one sensor.
"""

import pyRecFusionSDK as rf

print(f"Using RecFusionSDK v{rf.version()}")
rf.init()

sensor_manager = rf.SensorManager()
sensor = sensor_manager.open_any()

if not sensor:
    rf.deinit()
    sys.exit("ERROR: no sensor was opened!")

cw, ch, dw, dh = sensor.image_size
print(f"Image color size: {cw}x{ch}, depth size: {dw}x{dh}")

img_color = rf.ColorImage.empty(cw, ch)
img_depth = rf.DepthImage.empty(dw, dh)

if sensor.read_image(img_depth, img_color):
    img_color.to_image("color.png")
    img_depth.to_image("depth.png")
    print("Saved images to `color.png` and `depth.png` files")
else:
    print("Failed to read color and depth images")

sensor.close()
rf.deinit()
