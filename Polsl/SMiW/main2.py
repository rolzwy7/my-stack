import math
import numpy as np
import simpleaudio as sa

# Config - Start
SOUND_FILEPATH = "timmies.wav"
PLAY_ORIGINAL = False
# Config - End

import soundfile as sf
data, samplerate = sf.read(SOUND_FILEPATH)
print(len(data), "(%s)" % type(data))
print(samplerate, "Hz")

FILE_OUT = "%s-out.wav" % SOUND_FILEPATH

print("Starting...")
send_out = []


populate = True
Fs = samplerate
delay = 1500
range = 12
sweep = 0.3125

bufor = [0] * (range + delay + 1)
i = 0
for sample in data:
    sample_out = sample[0]

    if populate is True:
        # print("*pop*", i)
        bufor[i % len(bufor)] = sample_out
        if i == (range + delay) - 1:
            populate = False
            i = -1
    else:
        sin_ref = range * math.sin(2*math.pi*i*sweep/Fs)
        cur_delay = math.ceil(abs(sin_ref))

        idx = i % len(bufor)
        idxd = (i + delay + cur_delay) % len(bufor)

        sample_cpy = sample_out
        sample_out = bufor[idx] + bufor[idxd]

        send_out.append([sample_out, sample_out])
        bufor[idx] = sample_cpy
    i += 1


send_out_np = np.asarray(send_out)
print(send_out_np)

sf.write(FILE_OUT, send_out_np, Fs)
print("Playing...", end=" ")
wave_obj = sa.WaveObject.from_wave_file(FILE_OUT)
play_obj = wave_obj.play()
play_obj.wait_done()
print("done")
