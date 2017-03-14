import sys, time
from socket import *


try: assert(len(sys.argv) == 3)
except:
    print('usage: {} ip_address port'.format(sys.argv[0]))
    sys.exit(1)


HOST, PORT = (sys.argv[i] for i in range(1, 3))
REQNUM = 10000


def main():
    print('sending {} requests ...'.format(REQNUM))
    start = time.time()

    for i in range(REQNUM):
        with socket(AF_INET, SOCK_STREAM) as s:
            s.connect((HOST, int(PORT)))
            s.sendall(b'GET /\r\n\r\n')
            data = s.recv(1024)

    elapsed = (time.time() - start)
    print('elapsed:\t{}\ts'.format(elapsed))
    print('perf:\t\t{}\treq/s'.format(REQNUM / elapsed))


if __name__ == '__main__':
    main()
