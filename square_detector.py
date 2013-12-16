import sys

def find_first_block(image):
    N = len(image)
    for row in range(N):
        for col in range(N):
            if image[row][col] == '#':
                return row,col
                
def is_col_empty(image,row,col):
    N = len(image)
    for cur_row in range(row, N):
        if image[cur_row][col] != '.':
            return False
    return True
    
def is_col_height_h(image,row,col,h):
    N = len(image)
    if row + h-1 >= N:
        return False
    for cur_row in range(row, row+h):
        if image[cur_row][col] != '#':
            return False
    for cur_row in range(row+h, N):
        if image[cur_row][col] != '.':
            return False        
    return True

def contains_square(image):    
    row,col = find_first_block(image)
    for cur_col in range(0,col):
        if is_col_empty(image,row,cur_col) == False:
            return False
    
    w = 0
    for cur_col in range(col,N):
        if image[row][cur_col] != '#':
            break
        w += 1
    
    for cur_col in range(col, col+w):
        if is_col_height_h(image,row,cur_col,w) == False:
            return False
            
    for cur_col in range(col+w, N):
        if is_col_empty(image,row,cur_col) == False:
            return False
    
    return True

num_cases = int(sys.stdin.readline())

for case in range(1,num_cases+1):
    N = int(sys.stdin.readline())
    image = []
    for i in range(N):
        line = sys.stdin.readline().strip()
        image.append(list(line))
    has = contains_square(image)
    if has:
        print "Case #%s: YES" % case
    else:
        print "Case #%s: NO" % case
    
    