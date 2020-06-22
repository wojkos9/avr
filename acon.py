import numpy as np

fname = "/home/wojtek/test.wav"

with open(fname, "rb") as f:
    f.seek(44)
    c = f.read()

import sounddevice as sd

c1 = np.array(list(c), dtype=np.uint8) * (31 / 255)
c1 = np.uint8(c1)
print(max(c1))


print(c1)

sd.play(c1 * 8, samplerate=11025)
sd.wait()