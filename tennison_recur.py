import sys

def win_chance(K, win_prob, num_win, num_lose, cur_prob, sun, ps, pr, pu, pw, pd, pl ):
    sun = min(1.0, sun)
    sun = max(0.0, sun)
    w = sun*ps + (1-sun)*pr
    if num_win+1 < K:
        win_chance(K, win_prob, num_win+1, num_lose, cur_prob*w*pw,     sun+pu,  ps, pr, pu, pw, pd, pl )
        win_chance(K, win_prob, num_win+1, num_lose, cur_prob*w*(1-pw), sun,     ps, pr, pu, pw, pd, pl )
    else:        
        win_prob[0] += w*cur_prob    
    l = 1 - w
    if num_lose+1 < K:
        win_chance(K, win_prob, num_win, num_lose+1, cur_prob*l*pl,     sun-pd, ps, pr, pu, pw, pd, pl )
        win_chance(K, win_prob, num_win, num_lose+1, cur_prob*l*(1-pl), sun,    ps, pr, pu, pw, pd, pl )
        
T = int(sys.stdin.readline().strip())
for case in range(1,T+1):
    K, ps, pr, pi, pu, pw, pd, pl = map(float, sys.stdin.readline().strip().split())
    K = int(K)
    win_prob = [0]
    win_chance(K, win_prob, 0, 0, 1.0, pi, ps, pr, pu, pw, pd, pl )
    print "Case #%s: %.6f" % (case, win_prob[0])
        
    
        
    