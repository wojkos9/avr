import numpy as np
import sys
import sounddevice as sd
import matplotlib.pyplot as plt

def foo(s):
    with open("wave.h", "w") as f:
        f.write("static const uint8_t wave[] = {")
        f.write(",".join((str(int(x)) for x in s)))
        f.write("};")

sr = 8000
f1 = 440 # float(sys.argv[1])
f2 = 660
# n = int(sys.argv[2])
n = 2**5-1
ts = 1/f1
at = 0.3
t = np.arange(1, ts*sr, 1)
t1 = t/sr
# s1 = (1+np.sin(2*np.pi*(\
#     (np.sin(2*np.pi*t1/t1[-1])+1)/2*(f2-f1)+f1 \
#     )))/2*n
s1 = (1+np.sin(2*np.pi*f1*t1))*n/2
s = np.round(s1)
print(len(s))


# s = np.tile(s, 100)
print(s)
foo(s)

# s = np.tile(s, max(1, int(3 * sr / len(s))))
# print(s)

# sd.play(at*s/n, samplerate=sr)
# sd.wait()
# print(s)
# q = 1000
# plt.plot(t[:q], s[:q])
# plt.plot(t[:q], s1[:q])
# plt.show()
