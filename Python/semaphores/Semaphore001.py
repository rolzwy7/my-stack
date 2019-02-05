from threading import Thread, Semaphore

a = Semaphore(value=1)
b = Semaphore(value=0)
c = Semaphore(value=0)

def printA():
    global a, b, c
    for i in range(10):
        a.acquire()
        print("A", end="")
        b.release()

def printB():
    global a, b, c
    for i in range(10):
        b.acquire()
        print("B", end="")
        c.release()

def printC():
    global a, b, c
    for i in range(10):
        c.acquire()
        print("C", end="")
        a.release()

pool = [
    Thread(target=printA),
    Thread(target=printB),
    Thread(target=printC),
]

for thread in pool:
    thread.start()
