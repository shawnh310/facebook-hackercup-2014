import sys

T = int(sys.stdin.readline())

def find_min_move(N,K,C):
    if K <= N:
        miss = N-K        
        return miss + C
    else:
        m = K / N
        r = K % N
        if C <= m * N:
            return C
        else:
            e = N-r-1
            miss = 1
            while e > 0:
                if m >= e:
                    break
                else:
                    e -= m
                    miss+=1
                    e-=1
            return miss + C

for case_id in range(1,T+1):
    N, K, C = map(int, sys.stdin.readline().split())
    print "Case #%s: %s" % (case_id, find_min_move(N,K,C))