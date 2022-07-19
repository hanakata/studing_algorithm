#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

using Field = vector<vector<int>>;

class Sudoku{
    private:
        Field field_;
    public:
        Sudoku() : field_(9, vector<int>(9, -1)){

        }
    const Field& get(){
        return field_;
    }
    void put(int x, int y, int val){
        field_[x][y] = val;
    }

    void reset(int x, int y){
        field_[x][y] = -1;
    }
    void input(){
        for(int x = 0; x < 9; ++x){
            string line;
            cin >> line;
            for(int y = 0; y < 9; ++y){
                if(line[y] == '*'){
                    continue;
                }
                int val = line[y] - '0';
                put(x, y, val);
            }
        }
    }
    bool find_empty(int& x, int& y);
    vector<int> find_choices(int x, int y);

};
bool Sudoku::find_empty(int& x, int& y){
    for (x = 0; x < 9; ++x){
        for(y = 0; y < 9; ++y){
            if (field_[x][y] == -1){
                return true;
            }
        }
    }
    return false;
}

vector<int> Sudoku::find_choices(int x, int y){
    set<int> cannot_use;
    for(int i = 0; i < 9; ++i){
        if(field_[x][y] != -1){
            cannot_use.insert(field_[x][i]);
        }
    }
    for(int i = 0; i < 9; ++i){
        if (field_[i][y] != -1){
            cannot_use.insert(field_[i][y]);
        }
    }
    int x2 = x / 3 * 3, y2 = y / 3 * 3;
    for (int i = x2; i < x2 + 3; ++i){
        for(int j = y2; j < y2 + 3; ++j){
            if(field_[i][j] != -1){
                cannot_use.insert(field_[i][j]);
            }
        }
    }
    vector<int> res;
    for(int val = 1; val <= 9; ++val){
        if(!cannot_use.count(val)){
            res.push_back(val);
        }
    }
    return res;
}

void dfs(Sudoku& board, vector<Field>& res, bool all = true){
    if(!all && !res.empty()){
        return;
    }
    int x,y;
    if(!board.find_empty(x, y)){
        res.push_back(board.get());
        return;
    }

    const vector<int>& can_use = board.find_choices(x, y);

    for(int val :  can_use){
        board.put(x, y, val);
        dfs(board, res, all);
        board.reset(x,y);
    }
}

vector<Field> solve(Sudoku& board, bool all = true){
    vector<Field> res;
    dfs(board, res, all);
    return res;
}

int main(){
    cout << "Sudoku Input: " << endl;
    Sudoku board;
    board.input();

    vector<Field> res = solve(board);
    if(res.size() == 0){
        cout << "No solutions." << endl;
    }else if(res.size() > 1){
        cout << "More than one solution." << endl;
    }else{
        const Field& answer = res[0];
        for(int x = 0; x < 9; ++x){
            for(int y = 0; y < 9;++y){
                cout << answer[x][y] << "";
            }
        }
    }
}