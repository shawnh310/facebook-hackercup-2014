import sys

T = int(sys.stdin.readline())

def find_len_base(N, L):
    base = 1
    for l in range(1,100+1):
        if N >= base and N < base+L**l:
            return l, base
        else:
            base += L**l  

for case_id in range(1,T+1):
    D, N = sys.stdin.readline().strip().split()
    N = int(N)    
    L = len(D)
    l, base = find_len_base(N, L)
    out = []    
    for i in range(0,l):
        for k in range(0,L):
            if N >= base and N < base + L**(l-(i+1)):
                out.append(D[k])
                break
            else:
                base += L**(l-(i+1))
    out = reduce( lambda x,y: x+y, out)
    print "Case #%s: %s" % (case_id, out)
                
        