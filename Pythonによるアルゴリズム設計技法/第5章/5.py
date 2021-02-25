def tree_walk(T, r):
    for u in T[r]:
        tree_walk(T,u)

def rec_dfs(G,s,S=None):
    if S is None: S = set()
    S.add(s)
    for u in G[s]:
        if u in S: continue
        rec_dfs(G,u,S)
    return S

def iter_dfs(G,s):
    S,Q = set(), []
    Q.append(s)
    while Q:
        u = Q.pop()
        ifu in S: continue
        S.add(u)
        Q.extend(G[u])
        yield u