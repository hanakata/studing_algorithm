#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

bool is_valid(int64_t val, const string& str){
    string sval = to_string(val);
    if(sval.size() != str.size()){
        return false;
    }

    for(int i = 0; i < sval.size(); i++){
        if(str[i] == '*'){
            continue;
        }
        if(sval[i] != str[i]){
            return false;
        }
    }
}

bool is_valid_sub(int v, int k, const string& str){
    char c = str[(int)str.size() - 1 - k];
    if (c == '*'){
        return true;
    }
    int real_val = c - '0';
    return (v == real_val);
}

int64_t decode(const vector<int>& vec){
    int64_t res = 0;
    int64_t order = 1;
    for (int v : vec){
        res += order * v;
        order *= 10;
    }
    return res;
}

class Mushikuizan{
    private:
        string multiplicand_,multiplier_, product_;
        vector<string> middle_;
        vector<pair<int64_t, int64_t>> res_;

    public:
        Mushikuizan(const string& multiplicand,
                    const string& multiplier,
                    const string& product,
                    const vector<string>& middle):
            multiplicand_(multiplicand), multiplier_(multiplier),product_(product),middle_(middle){

            }
    void rec_plier(int64_t plicand, vector<int>& vec){
        if(vec.size() == multiplier_.size()){
            int64_t plier = decode(vec);

            if(!is_valid(plicand * plier, product_)){
                return;
            }
            res_.emplace_back(plicand, plier);
            return;
        }

        for(int add = 1; add < 9; ++add){
            if(!is_valid_sub(add, vec.size(), multiplier_)){
                continue;
            }
            if(!is_valid(plicand * add, middle_[vec.size()])){
                continue;
            }
            vec.push_back(add);
            rec_plier(plicand, vec);
            vec.pop_back();
        }
    }

    void rec_plicand(vector<int>& vec){
        if(vec.size() == multiplicand_.size()){
            vector<int> vec2;
            rec_plier(decode(vec), vec2);
            return;
        }
        for (int add = 0; add <= 9; ++add){
            if(vec.empty() && add == 0){
                continue;
            }
            if(!is_valid_sub(add, vec.size(), multiplicand_)){
                continue;
            }
            vec.push_back(add);
            rec_plicand(vec);
            vec.pop_back();
        }
    }
    vector<pair<int64_t, int64_t>> solve(){
        res_.clear();
        vector<int> vec;
        rec_plicand(vec);
        return res_;
    }
};

int main(){
    cout << "Mushikuizan Input: " << endl;
    int A, B;
    cin >> A >> B;
    string hijou, jou, seki;
    vector<string> middle(B);
    cin >> hijou >> jou;
    for(int i = 0; i < B; ++i){
        cin >> middle[i];
    }
    cin >> seki;
    Mushikuizan mu(hijou, jou, seki, middle);
    const vector<pair<int64_t, int64_t>>& res = mu.solve();

    cout << "The num of solution. " << res.size() << endl;
    for (int i = 0; i < res.size(); ++i){
        cout << i << " th solution: " << res[i].first << "*" << res[i].second << "=" << res[i].first * res[i].second << endl;
    }
}