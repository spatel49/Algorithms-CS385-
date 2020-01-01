string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct Edge{
    int from, to, weight;

    Edge(int _from, int _to, int _weight) {
         from = _from;
         to = _to;
         weight = _weight;
    }
};

bool sort_by_weight(Edge *x, Edge *y) {
    return x->weight < y->weight;
}

int find(int node, int nodes[]){
    while (nodes[node] != -1){
        node = nodes[node];
    }
    return node;
}

void union_nodes(int x, int y, int nodes[]) {
    nodes[y] = x;
}

int kruskals(int g_nodes, int g_edges, vector<int> g_from, vector<int> g_weight){
    Edge **edges = new Edge*[g_edges];
    for (int i = 0; i < g_edges; i++){
        edges[i] = new Edge(g_from[i], g_to[i], g_weight[i]);
    }
    sort(edges, edges + g_edges, sort_by_weight);
    int mstWeight = 0;
    int *nodes = new int[g_nodes];
    fill(nodes, nodes + g_nodes, -1);
    for (int i = 0; i < g_edges; i++) {
        int findX = find(edges[i]->from, nodes),
            findY = find(edges[i]->to, nodes);
        if(findX != findY){
            mstWeight += edges[i]->weight;
            union_nodes(findX, findY, nodes);
        }
    }

    delete [] nodes;
    for (int i = 0; i < g_edges; i++){
        edges[i];
    }
    delete [] edges;
}

int res = kruskals(g_nodes, g_edges, g_from, g_to, g_weight);

fout << res << endl;

fout.close();
