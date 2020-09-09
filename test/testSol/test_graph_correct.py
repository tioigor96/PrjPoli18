import string
import random
from subprocess import Popen, PIPE
import networkx as nx


def id_gen(size=200, chars=string.ascii_lowercase):
    return ''.join(random.choice(chars) for _ in range(size))


for i in range(100):
    print(i)
    s = id_gen(i)
    p1 = Popen("/home/igor/CLionProjects/PrjPoli18/cmake-build-debug/PrjPoli18", stdin=PIPE, stdout=PIPE)
    p2 = Popen("/home/igor/CLionProjects/PrjPoli18/testgraph", stdin=PIPE, stdout=PIPE)

    p1.stdin.write(s.encode('utf-8'))
    p1.stdin.close()
    out1 = p1.stdout.read()
    out1 = out1.decode('utf-8')
    p1.stdout.close()
    p1.terminate()
    f = open("/tmp/dot1.dot", "w")
    f.write(out1)
    f.close()

    p2.stdin.write(s.encode('utf-8'))
    p2.stdin.close()
    out2 = p2.stdout.read()
    out2 = out2.decode('utf-8')
    p2.stdout.close()
    p2.terminate()
    f = open("/tmp/dot2.dot", "w")
    f.write(out2)
    f.close()

    g1 = g1 = nx.drawing.nx_pydot.read_dot("/tmp/dot1.dot")
    g2 = g1 = nx.drawing.nx_pydot.read_dot("/tmp/dot2.dot")

    res = nx.is_isomorphic(g1, g2)

    if res == False:
        print("AIAIAIAIA!")
        print(s)
        break
