# ConsoleReconstruction example with only the sensor reconstruction logic
import sys
import pyRecFusionSDK as rf

if not rf.activate("XXXXX-XXXXX-XXXXX-XXXXX-XXXXX"):
    print("Invalid RecFusion license. Export will be disabled")

rf.init()

sensor_manager = rf.SensorManager()

if sensor_manager.device_count() == 0:
    sys.exit("No sensors are available")

sensor = sensor_manager.sensor(0)

if not sensor.open():
    rf.deinit()
    sys.exit("Couldn't open sensor")

cw = sensor.color_width()
ch = sensor.color_height()
dw = sensor.depth_width()
dh = sensor.depth_height()

params = rf.ReconstructionParams()


params.set_image_size(cw, ch, dw, dh)
params.set_intrinsics(sensor.depth_intrinsics())
params.set_color_intrinsics(sensor.color_intrinsics())
params.set_depth_to_color_transformation(sensor.depth_to_color_transformation())

reconstruction = rf.Reconstruction(params)
img_color = rf.ColorImage.empty(cw, ch)
img_depth = rf.DepthImage.empty(dw, dh)

# int frame = 0
max_frames = 100

for frame in range(max_frames):
    if not sensor.read_image(img_depth, img_color):
        continue
    if not reconstruction.add_frame(0, img_depth, img_color):
        break
    print("Processed frame:", frame)

sensor.close()
print("Finished reconstruction")

mesh = reconstruction.get_mesh()

rf.deinit()
