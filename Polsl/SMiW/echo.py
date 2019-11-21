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
buffor = [0] * 240 # 20ms - 960
buffor_full = False
it = 0
for sample in yield_samples():
    sample = sample[0]
    if it == 240:
        buffor_full = True
        it = 0
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
