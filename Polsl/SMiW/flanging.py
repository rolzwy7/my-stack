SOUND_FILEPATH = "sample-data.txt"


def yield_samples():
    with open(SOUND_FILEPATH, "rb") as fh:
        for line in fh:
            line = line.strip(b"\n").strip(b"\r")
            line = str(line, "utf8")
            l, r = line.split("\t")
            l, r = float(l), float(r)
            yield l, r

DEST = open("%s-out" % SOUND_FILEPATH, "wb")
def send_out(sample):
    global DEST
    temp = "%s\t%s\n" % (sample, sample)
    DEST.write(temp.encode())

# Code here - Start
buffor = [0] * 6000 # 20ms - 960
delay = 480
new_delay = delay
shifts = list(range(1,120))
shifts_len = len(shifts)
buffor_full = False
sit = 0
it = 0
it_g = 0
for sample in yield_samples():
    it_g += 1
    if it_g > 48000 * 6:
        break



    sample = sample[0]
    if it == new_delay:
        buffor_full = True
        it = 0
        new_delay = delay + shifts[sit%shifts_len]
        sit += 1

    if buffor_full:
        buffor[it] = buffor[it] + sample
    else:
        buffor[it] = sample

    send_out(buffor[it])

    if buffor_full:
        buffor[it] = sample

    it += 1

# Code here - End

DEST.close()
