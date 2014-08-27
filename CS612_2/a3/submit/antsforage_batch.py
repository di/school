from subprocess import Popen, PIPE


for i in range(1001):
    p = Popen(['java', 'sim.app.antsforage.AntsForageWithUI'], stdout=PIPE, stderr=PIPE, stdin=PIPE)
    f = open("./output/ants.out", 'a')
    f.write(p.stdout.read())
    print i
    f.close()
