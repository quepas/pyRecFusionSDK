# ConsoleReconstruction example with only the sensor reconstruction logic
import sys
from argparse import ArgumentParser

import pyRecFusionSDK as rf

parser = ArgumentParser()
parser.add_argument("output_file")
parser.add_argument("--num-frames", type=int, default=100)
args = parser.parse_args()

print(f"Using RecFusionSDK v{rf.version()}")
rf.init()

sensor_manager = rf.SensorManager()
sensor = sensor_manager.open_any()

if sensor is None or not sensor.open():
    rf.deinit()
    sys.exit("No sensors are available and cannot be opened.")

cw, ch, dw, dh = sensor.image_size

print(f"Image color size: {cw}x{ch}, depth size: {dw}x{dh}")

img_color = rf.ColorImage.empty(cw, ch)
img_depth = rf.DepthImage.empty(dw, dh)

recorder = rf.RFSRecorder(args.output_file)
# TODO: add init_from_sensor() ?
recorder.init(cw, ch, dw, dh, sensor.depth_intrinsics)
recorder.start()

num_processed_frames = 0
for i in range(args.num_frames):
    if not sensor.read_image(img_depth, img_color):
        print(f"WARNING: failed to read image #{i} from the sensor")
        continue
    recorder.add_frame(img_depth, img_color)
    print(f"Processed frame #{i}")
    num_processed_frames += 1

print(
    f"The sequence contains {num_processed_frames}/{args.num_frames} processed frames"
)

recorder.stop()
recorder.cleanup()
sensor.close()

rf.deinit()
