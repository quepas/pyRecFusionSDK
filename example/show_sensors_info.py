import sys

import pyRecFusionSDK as rf

print(f"Using RecFusionSDK v{rf.version()}")
rf.init()

sensor_manager = rf.SensorManager()
sensors = sensor_manager.open_all()

if not sensors:
    sys.exit("ERROR: Couldn't open any sensors!")


# TODO: check if it is neccessary to open the sensor before!
for num, sensor in enumerate(sensors, start=1):
    print(f"Sensor #{num} info:")
    print(f"\t* Device name: {sensor.device_name}")
    print(f"\t* UUID: {sensor.uuid}")
    print("\t* Depth formats:")
    for idx, fmt in enumerate(sensor.depth_formats):
        print(f"\t\t- Depth format #{idx}: {fmt}")

    print("\t* Color formats:")
    for idx, fmt in enumerate(sensor.color_formats):
        print(f"\t\t- Color format #{idx}: {fmt}")
