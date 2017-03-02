import sys, time
from socket import *


HOST = ''
PORT = 2929
REQNUM = 100000

if len(sys.argv) != 2:
    raise Exception('usage: {} <IPaddress>'.format(sys.argv[0]))


def main():
    print('sending {} requests ...'.format(REQNUM))
    start = time.time()

    for i in range(REQNUM):
        with socket(AF_INET, SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            s.sendall(b'GET /\r\n\r\n')
            data = s.recv(1024)

    elapsed = (time.time() - start)
    print('elapsed:\t{}\ts'.format(elapsed))
    print('perf:\t\t{}\treq/s'.format(REQNUM / elapsed))


if __name__ == '__main__':
    main()
