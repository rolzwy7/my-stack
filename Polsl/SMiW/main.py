from math import pi, sin

import simpleaudio as sa

# Config - Start
SOUND_FILEPATH = "rice_fields.wav"
PLAY_ORIGINAL = False
# Config - End

import soundfile as sf
data, samplerate = sf.read(SOUND_FILEPATH)
print(len(data))
print(data[:10])
print(samplerate)
exit(0)

FILE_OUT = "%s-out.txt" % SOUND_FILEPATH

def yield_samples():
    with open(SOUND_FILEPATH, "rb") as fh:
        for line in fh:
            line = line.strip(b"\n").strip(b"\r")
            line = str(line, "utf8")
            l, r = line.split("\t")
            l, r = float(l), float(r)
            yield l, r

DEST = open(FILE_OUT, "wb")
def send_out(sample):
    global DEST
    temp = "%s\t%s\n" % (sample, sample)
    DEST.write(temp.encode())

print("Starting...")

delay = 15
range = 12
sweep_freq = 0.3125
fs = 44100

ahead = delay + range

arr = [0] * (ahead + 1)
start_playing = False

it = 0
cit = 0
for sample in yield_samples():
    sample = sample[0]
    if PLAY_ORIGINAL:
        send_out(sample_out)
        continue

    if start_playing:
        dx = cit + delay + round(range * sin(2*pi*cit*sweep_freq/fs));
        # print("playing:", dx - cit)
        sample_out = arr[cit % ahead] + arr[dx % ahead]
        send_out(sample_out)
        cit = (cit + 1)

    arr[it] = sample
    it = (it + 1) % ahead;

    if start_playing or it == delay + 1:
        start_playing = True

DEST.close()

print("Playing...", end=" ")
wave_obj = sa.WaveObject.from_wave_file(FILE_OUT)
play_obj = wave_obj.play()
play_obj.wait_done()
print("done")
