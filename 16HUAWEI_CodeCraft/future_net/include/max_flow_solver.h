/*************************************************************************
	> File Name: max_flow_solver.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Wed 30 Mar 2016 12:28:40 AM CST
*************************************************************************/

#ifndef _MAX_FLOW_SOLVER_H_
#define _MAX_FLOW_SOLVER_H_

#include <queue>

template<int N, int M, typename Type>
struct MaxFlow{
    int edge, source, sink;
    int lvl[N], cur[N];
    int fi[N], ne[M << 1], en[M << 1];
    Type cap[M << 1];
    const Type INF = 1000;

    void init(int S, int T) {
        source = S, sink = T;
        edge = 1, memset(fi, 0, sizeof(fi));
    }

    void _add(int x, int y, Type z) {
        ne[++edge] = fi[x]; fi[x] = edge; en[edge] = y; cap[edge] = z;
    }

    void add(int x, int y, Type z) {
        _add(x, y, z);
        _add(y, x, 0);
    }

    bool bfs() {
        std::queue<int> q;
        memset(lvl, 0, sizeof(lvl));
        q.push(source), lvl[source] = 1;
        while(q.size()) {
            int x = q.front(); q.pop();
            for (int go = fi[x]; go; go = ne[go]) if (cap[go] > 0 && !lvl[en[go]]) {
                int y = en[go];
                lvl[y] = lvl[x] + 1;
                q.push(y);
            }
        }
        return lvl[sink];
    }

    Type dfs(Type x, Type flow) {
        if (x == sink || flow == 0) {
            return flow;
        }
        Type ans = 0, tmp = 0;
        for (int &go = cur[x]; go; go = ne[go]) if (cap[go] > 0) {
            int y = en[go];
            if (lvl[y] == lvl[x] + 1 && (tmp = dfs(y, min(flow, (Type) cap[go]))) > 0) {
                ans += tmp, flow -= tmp;
                cap[go] -= tmp, cap[go ^ 1] += tmp;
                if (flow == 0) {
                    return ans;
                }
            }
        }
        return ans;
    }

    Type dinic() {
        Type ans = 0;
        while (bfs()) {
            memcpy(cur, fi, sizeof(fi));
            ans += dfs(source, INF);
        }	
        return ans;
    }
};
#endif /* _MAX_FLOW_SOLVER_H_ */
