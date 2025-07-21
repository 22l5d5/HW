
#include <iostream>
#include <vector>
using namespace std;

void ps_rec(vector<int>& s, int i, vector<int>& cur, vector<vector<int>>& res) {
    if (i == s.size()) {
        res.push_back(cur);
        return;
    }
    ps_rec(s, i + 1, cur, res);
    cur.push_back(s[i]);
    ps_rec(s, i + 1, cur, res);
    cur.pop_back();
}

vector<vector<int>> get_ps(vector<int>& s) {
    vector<vector<int>> res;
    vector<int> cur;
    ps_rec(s, 0, cur, res);
    return res;
}

int main() {
    int n;
    cout << "請輸入集合元素數量: ";
    cin >> n;
    vector<int> s(n);
    cout << "請輸入 " << n << " 個元素: ";
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    try {
        vector<vector<int>> ps = get_ps(s);
        for (const auto& sub : ps) {
            cout << "{ ";
            for (int e : sub) cout << e << " ";
            cout << "}" << endl;
        }
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}
