#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <utility>

using namespace std;



double calc_poland(const string& exp){
    //計算のための配列
    vector<double> space;
    //逆ポーランド記法expの各文字をcを順に見る
    for (char c : exp){
        if (c >= '0' && c <= '9'){
            int add = c - '0';
            space.push_back(add);
        }else{
            double second = space.back();
            space.pop_back();
            double first = space.back();
            space.pop_back();

            if (c == '+'){
                space.push_back(first + second);
            }else if (c == '-'){
                space.push_back(first - second);
            }else if (c == '*'){
                space.push_back(first * second);
            }else{
                space.push_back(first / second);
            }
        }
    }
    return space.back();
}

string decode_poland(const string& exp) {
    vector<string> space;
    for (char c : exp){
        if ( c >= '0' && c <= '9'){
            space.push_back({c});
        }else{
            string second = space.back();
            space.pop_back();
            string first = space.back();
            space.pop_back();

            if(c == '*' || c == '/'){
                if (first.size() > 1){
                    first = "(" + first + ")";
                }
                if (second.size() > 1){
                    second = "(" + second + ")";
                }
            }
            if(c == '+'){
                space.push_back(first + "+" + second);
            }else if(c == '-'){
                space.push_back(first + "-" + second);
            }else if(c == '*'){
                space.push_back(first + "*" + second);
            }else {
                space.push_back(first + "/" + second);
            }
        }
    }
    return space.back();
}

vector<string> solve(vector<int> val, int target){
    vector<string> res;

    const double EPS = 1e-9;
    auto check = [&](const string& exp) -> void {
        if (abs(calc_poland(exp) - target) < EPS){
            res.push_back(decode_poland(exp));
        }
    };

    sort(val.begin(), val.end());
    do{
        string fours = "";
        for (int v:val) fours += to_string(v);

        const string ops = "+-*/";
        for (char op1 : ops){
            for (char op2 : ops){
                for(char op3 : ops){
                    string exp = fours + op1 + op2 + op3;
                    check(exp);
                    swap(exp[3], exp[4]), check(exp);
                    swap(exp[4], exp[5]), check(exp);
                    swap(exp[2], exp[3]), check(exp);
                    swap(exp[4], exp[5]), check(exp);
                }
            }
        }
    }while(next_permutation(val.begin(), val.end()));
    return res;
}

int main() {
    vector<int> val(4);
    int target;
    for(int i = 0; i < 4; ++i){
        cout << i + 1 << " th number: ";
        cin >> val[i];
    }
    cout << "target number: ";
    cin >> target;

    vector<string> res = solve(val, target);

    for (const string& exp : res){
        cout << exp << "=" << target << endl;
    }
}