#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <utility>
using namespace std;

const int EMPTY = 0;
const int PLUS = 1;
const int MINUS = 2;
const int MUL = 3;
const int DIV = 4;

const int TARGET = 100;

pair<vector<double>, vector<int>> calc_empty(const vector<int>& signs){
    vector<double> new_vals;
    vector<int> new_signs;

    double val = 1;

    for (int i = 0;i < signs.size(); ++i){
        double add = i + 2;

        if(signs[i] == EMPTY){
            val = val * 10 + add;
        }else{
            new_vals.push_back(val);
            new_signs.push_back(signs[i]);
            val = add;
        }
    }
    new_vals.push_back(val);
    return make_pair(new_vals, new_signs);
}

pair<vector<double>, vector<int>>
calc_mul_div(const vector<double>& vals, const vector<int>& signs){
    vector<double> new_vals;
    vector<int> new_signs;

    double val = vals[0];
    for(int i = 0; i < signs.size(); ++i){
        double add = vals[i + 1];

        if (signs[i] == MUL){
            val *= add;
        }else if (signs[i] == DIV){
            val /= add;
        }else{
            new_vals.push_back(val);
            new_signs.push_back(signs[i]);
            val = add;
        }
    }
    new_vals.push_back(val);
    return make_pair(new_vals, new_signs);
}

double calc_plus_minus(const vector<double>& vals, const vector<int>& signs){
    double res = vals[0];
    for(int i = 0; i < signs.size(); ++i){
        double add = vals[i + 1];
        if (signs[i] == PLUS){
            res += add;
        }else if(signs[i] == MINUS){
            res -= add;
        }
    }
    return res;
}

double calc(const vector<int>& signs){
    pair<vector<double>, vector<int>> step1 = calc_empty(signs);
    pair<vector<double>, vector<int>> step2 = calc_mul_div(step1.first, step1.second);
    return calc_plus_minus(step2.first, step2.second);
}

string decode(const vector<int>& sign){
    string res = "1";
    for(int i = 0; i < sign.size(); ++i){
        if(sign[i] == PLUS){
            res += " + ";
        }else if(sign[i] == MINUS){
            res += " - ";
        }else if(sign[i] == MUL){
            res += " * ";
        }else if(sign[i] == DIV){
            res += " / ";
        }
        res += to_string(i + 2);
    }
    return res;
}

void rec(const vector<int>& vec, vector<string>& res){
    if(vec.size() == 8){
        const double EPS = 1e-9;
        if(abs(calc(vec) - TARGET) < EPS){
            res.push_back(decode(vec));
        }
        return;
    }

    for (int add = 0; add < 5; ++add){
        //vecの末尾にaddを追加
        vector<int> vec2 = vec;
        vec2.push_back(add);
        rec(vec2, res);
    }
}

int main(){
    vector<int> vec;
    vector<string> res;
    rec(vec, res);

    cout << "The number of solutions:" << res.size() << endl;
    for(const string& str : res){
        cout << str << "=" << TARGET << endl;
    }
}