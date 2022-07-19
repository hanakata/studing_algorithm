#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

class Fukumenzan{
    private:
    vector<string> problem_;
    vector<vector<int>> board_;
    set<int> used_;

    const int NOTIN = -1;
    public:
    Fukumenzan(const vector<string>& input) : problem_(input){}

    void init(){
        board_.resize(problem_.size());
        for(int i = 0; i < problem_.size(); ++i){
            board_[i].assign(problem_[i].size(), NOTIN);
        }
        used_.clear();
    }
    int get_size() const{
        return problem_.size();
    }
    int get_digit() const{
        return problem_.back().size();
    }
    int get_digit(int row)const{
        return problem_[row].size();
    }
    bool is_used(int val) const{
        return used_.count(val);
    }
    int get_val(int row, int digit) const{
        if(digit >= get_digit(row)){
            return 0;
        }
        return board_[row][get_digit(row) - 1 - digit];
    }
    char get_char(int row, int digit) const{
        return problem_[row][get_digit(row) - 1 - digit];
    }
    void print() const {
        for (const vector<int>& vec : board_){
            for (int v : vec) {
                cout << v;
            }
            cout << endl;
        }
    }
    void set_val(int row, int digit, int val);
    void reset_val(int row, int digit, int val);
    bool is_valid();
};

void Fukumenzan::set_val(int row, int digit, int val){
    char c = get_char(row, digit);
    for(int r = 0; r < get_size(); ++r){
        for(int d = 0; d < get_digit(r); ++d){
            if(problem_[r][d] == c){
                board_[r][d] = val;
            }
        }
    }
    used_.insert(val);
}

void Fukumenzan::reset_val(int row, int digit, int val){
    char c = get_char(row, digit);
    for(int r = 0; r < get_size(); ++r){
        for(int d = 0; d < get_digit(r); ++d){
            if(problem_[r][d] == c){
                board_[r][d];
            }
        }
    }
    used_.erase(val);
}

bool Fukumenzan::is_valid(){
    for (const vector<int>& val:board_){
        if(val[0] == 0){
            return false;
        }
    }

    int kuriagari = 0;
    for (int digit = 0; digit < get_digit(); ++digit){
        int sum = 0;
        for (int row = 0; row < get_size(); ++row){
            if(get_val(row, digit) == NOTIN){
                return true;
            }
            if(row != get_size() - 1){
                sum += get_val(row, digit);
            }
        }
        sum += kuriagari;
        kuriagari = sum / 10;
        if(sum % 10 != get_val(get_size() - 1, digit)){
            return false;
        }
    }
    return (kuriagari == 0);
}

void dfs(Fukumenzan& fu, int row, int digit, vector<Fukumenzan>& res){
    if(row == 0 && digit == fu.get_digit()){
        res.push_back(fu);
        return;
    }
    int next_row = row + 1, next_digit = digit;
    if(next_row == fu.get_size()){
        next_row = 0, next_digit = next_digit + 1;
    }
    if(fu.get_val(row, digit) != -1){
        dfs(fu, next_row, next_digit, res);
    }else{
        for(int val = 0; val <= 9; ++val){
            if(fu.is_used(val)){
                continue;
            }
            fu.set_val(row, digit, val);
            if(fu.is_valid()){
                dfs(fu, next_row, next_digit, res);
            }
            fu.reset_val(row, digit, val);
        }
    }
}

vector<Fukumenzan> solve(Fukumenzan& fu){
    for(int i = 0; i < fu.get_size() -1; ++i){
        if(fu.get_digit(i) > fu.get_digit()){
            return vector<Fukumenzan>();
        }
    }
    fu.init();

    vector<Fukumenzan> res;
    dfs(fu, 0, 0, res);
    return res;

}

int main(){
    cout << "Fukumenzan Input: " << endl;
    int N;
    cin >> N;
    vector<string> input(N);
    for(int i = 0; i < N; ++i){
        cin >> input[i];
    }
    Fukumenzan fu(input);
    const vector<Fukumenzan>& res = solve(fu);
    cout << "The num of solutions: " << res.size() <<endl;
    for(int i = 0; i < res.size(); ++i){
        cout << i << " th solution" << endl;
        res[i].print();
    }
}