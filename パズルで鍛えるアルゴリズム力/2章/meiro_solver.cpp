#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

using Cor = pair<int, int>;
const vector<Cor> DIR = {Cor(1, 0), Cor(0,1), Cor(-1,0),Cor(0,-1)};
const int NOTIN = -1;

void solve(const vector<string>& board, const Cor& start, const Cor& goal){
    int H = board.size(), W = board[0].size();
    vector<vector<Cor>> nodes;

    vector<vector<int>> dist(H, vector<int>(W, NOTIN));
    vector<vector<Cor>> arrow(H, vector<Cor>(W, Cor(NOTIN, NOTIN)));
    nodes.push_back(vector<Cor>(1, start));
    dist[start.first][start.second] = 0;
    while(!nodes.back().empty()){
        const vector<Cor>& cur = nodes.back();
        vector<Cor> nex;
        for(const Cor& cell : cur){
            int x = cell.first, y = cell.second;
            for(int direction = 0; direction < 4; ++direction){
                int nex_x = x + DIR[direction].first;
                int nex_y = y + DIR[direction].second;
                if(nex_x < 0 || nex_x >= H){
                    continue;
                }
                if(nex_y < 0 || nex_y >= W){
                    continue;
                }
                if(board[nex_x][nex_y] == '#'){
                    continue;
                }
                if(dist[nex_x][nex_y] != NOTIN){
                    continue;
                }
                dist[nex_x][nex_y] = dist[x][y] + 1;
                arrow[nex_x][nex_y] = Cor(x, y);
                nex.push_back(Cor(nex_x, nex_y));
            }
        }
        nodes.push_back(nex);
    }
    if(dist[goal.first][goal.second] == NOTIN){
        cout << "No Path" << endl;
        return;
    }
    vector<string> res = board;
    int cur_x = goal.first, cur_y = goal.second;

    while (arrow[cur_x][cur_y] != Cor(NOTIN,NOTIN)){
        res[cur_x][cur_y] = 'o';
        int nex_x = arrow[cur_x][cur_y].first;
        int nex_y = arrow[cur_x][cur_y].second;
        cur_x = nex_x, cur_y = nex_y;
    }
    cout << "----- solution -----" << endl;
    for(const string& str : res){
        cout << str << endl;
    }
    cout << "length = " << dist[goal.first][goal.second] << endl;
}

int main(){
    cout << "Maze Input: " << endl;
    int H, W;
    cin >> H >> W;
    vector<string> board(H);
    for (int x = 0; x < H; ++x){
        cin >> board[x];
    }
    Cor start, goal;
    for (int x = 0; x < H; ++x){
        for(int y = 0; y < W; ++y){
            if(board[x][y] == 'S'){
                start = Cor(x, y);
            }else if(board[x][y] == 'G'){
                goal = Cor(x, y);
            }

        }
    }
    solve(board, start, goal);
}