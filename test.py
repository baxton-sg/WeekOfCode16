
import sys
import numpy as np



def pop_edge(g, node, visited):
    N = len(g[node])
    if 0 == N:
        return None

    n = None

    for a in range(N):
        i = np.random.randint(0, N)
        n = g[node][i]
        if n not in visited:
            break
        n = None
#    g[node].pop(i)
#    g[n].remove(node)
    return n







def print_path(N, graph, end_points, visited=None):
    if end_points[0] == end_points[1]:
        return True

    if not visited:
        visited = set([end_points[0]])

    while True:
        n = pop_edge(graph, end_points[0], visited)

        if not n:
            return False

        visited.add(n)

        res = print_path(N, graph, [n, end_points[1]], visited)

        if res:
            graph[end_points[0]].remove(n)
            graph[n].remove(end_points[0])

            # print "(%d, %d)" % (end_points[0], n)
            break

    return res



def solve(N, M, graph, parades):

    best_cnt = 0

    attempts = 10
    
    for a in range(attempts):
        # print "Attempt #", a

        g = []
        for n in range(N):
            g.append(graph[n][::-1])


        cnt = 0

        for p in range(len(parades)):
            # print "path for", parades[p]
            res = print_path(N, g, parades[p], None)
  
            if res:
                cnt += 1

        if best_cnt == 0 or cnt > best_cnt:
            best_cnt = cnt

    return best_cnt
    




def main():

    

    T = int(sys.stdin.readline().strip())

    for t in range(T):
        N = int(sys.stdin.readline().strip())

        edges = []
        for n in range(N):
            edges.append([])

        parades = []

        for n in range(N-1):
            line = sys.stdin.readline()
            a, b = [int(v) for v in line.strip().split(' ')]

            edges[a-1].append(b-1)
            edges[b-1].append(a-1)

        M = int(sys.stdin.readline().strip())
        for m in range(M):
            line = sys.stdin.readline()
            ui, vi = [int(v) for v in line.strip().split(' ')]
            parades.append([ui-1, vi-1])

            
        cnt = solve(N, M, edges, parades) 

        print cnt





main()
