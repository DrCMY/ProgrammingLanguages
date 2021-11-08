
int numberOfWays(vector<vector<int>> roads) {
    int n = roads.size() + 1;
    const int INF = n;
    for(int i = 0; i < roads.size(); i++){
        roads[i][0]--;
        roads[i][1]--;
    }
    vector<vector<int>> states;
    set<vector<int>> st;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                if(i != j && j != k && k != i){
                    vector<int> tmp = {i, j, k};
                    sort(tmp.begin(), tmp.end());
                    st.insert(tmp);
                }
            }
        }
    }
    for(vector<int> state: st){
        states.push_back(state);
    }
    vector<vector<int>> dist(n, vector<int>(n, INF));
    for(int i = 0; i < roads.size(); i++){
        dist[roads[i][0]][roads[i][1]] = 1;
        dist[roads[i][1]][roads[i][0]] = 1;
    }
    int res = 0;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    for(vector<int> state: states){
        int a = state[0];
        int b = state[1];
        int c = state[2];
        if(dist[a][b] == dist[b][c] && dist[c][a] == dist[b][c]){
            res++;
        }
    }
    return res;
}
