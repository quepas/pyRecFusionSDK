# ConsoleReconstruction example with only the sensor reconstruction logic
from argparse import ArgumentParser
import sys
import pyRecFusionSDK as rf

parser = ArgumentParser()
parser.add_argument("license_key", type=str)
args = parser.parse_args()


print(f"Using RecFusionSDK v{rf.version()}")

if not rf.activate(args.license_key):
    print("ERROR: Invalid RecFusion license. Export will be disabled")

rf.init()
sensor_manager = rf.SensorManager()

if sensor_manager.device_count == 0:
    rf.deinit()
    sys.exit("No sensors are available")

sensor = sensor_manager.sensor(0)

if not sensor.open():
    rf.deinit()
    sys.exit("Couldn't open sensor")

cw, ch, dw, dh = sensor.image_size
print(f"Image color size: {cw}x{ch}, depth size: {dw}x{dh}")

params = rf.ReconstructionParams()

# TODO: add ReconstructionParams::add_from_sensor(int, Sensor) ?? copy_from_sensor? fill_from_sensor?
params.set_image_size(cw, ch, dw, dh)
params.set_intrinsics(sensor.depth_intrinsics)
params.set_color_intrinsics(sensor.color_intrinsics)
params.set_depth_to_color_transformation(sensor.depth_to_color_transformation)

reconstruction = rf.Reconstruction(params)
img_color = rf.ColorImage.empty(cw, ch)
img_depth = rf.DepthImage.empty(dw, dh)

# int frame = 0
max_frames = 100

for frame in range(max_frames):
    if not sensor.read_image(img_depth, img_color):
        continue
    if not reconstruction.add_frame2(0, img_depth, img_color):
        break
    print("Processed frame:", frame)

sensor.close()
print("Finished reconstruction")

if not reconstruction.good:
    rf.deinit()
    sys.exit("Failed to reconstruct a mesh")

mesh = reconstruction.get_mesh()
print("Mesh center: ", mesh.center)
print("Mesh #vertices: ", mesh.vertex_count)
print("Mesh #triangles: ", mesh.triangle_count)

rf.deinit()
