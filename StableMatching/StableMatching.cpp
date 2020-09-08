#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> stableMatching(vector<vector<int>> man_list, vector<vector<int>> woman_list) {
        int man_num = man_list.size();
        int woman_num = woman_list.size();
        // 男女数量不同，无法完美匹配
        if (man_num != woman_num) return {};
        int n = man_num;

        // 将女性喜好列表的索引和数据置反，方便处理
        vector<vector<int>> inverse_womanlist;
        for (int i = 0; i < n; ++i) {
            vector<int> prefer(n, -1);
            for (int j = 0; j < n; ++j) {
                prefer[woman_list[i][j]] = j;
            }
            inverse_womanlist.push_back(prefer);
        }
        // 记录最终的匹配结果
        vector<vector<int>> S = {};
        // 记录单身男性
        queue<int> free_man;
        for (int i = 0; i < n; ++i) {
            free_man.push(i);
        }
        // husband[w] = m：女性 w 的伴侣是 m
        vector<int> husband(n, -1);
        // 为每个男性维护一个指针（索引），记录喜爱列表中下一个求婚的女性索引
        vector<int> man_pointer(n, 0);
        // G-S算法主体
        while (!free_man.empty()) {
            int m = free_man.front();
            int w = man_list[m][man_pointer[m]];
            // 男方求婚指针向前
            man_pointer[m]++;
            // 女方无配偶
            if (husband[w] == -1) {
                S.push_back({m,w});
                free_man.pop();
                husband[w] = m;
            }
            // 男人m比当前配偶更有吸引力
            else if (inverse_womanlist[w][husband[w]] > inverse_womanlist[w][m]) {
                // 找到 S 中原来关于 w 的一对
                int index;
                for (index = 0; index < S.size(); index++) {
                    if (S[index][1] == w) break;
                }
                int old_m = S[index][0];

                // 从 S 中删除 m'-w
                S.erase(S.begin() + index);
                // 在 S 中添加 m -w
                S.push_back({m, w});
                free_man.pop();
                // w 原来的配偶变为单身汉
                free_man.push(old_m);
                husband[w] = m;
            }
            else {
                // w 拒绝 m
            }
        }
        return S;
    }
};

int main() {
    // 索引代表男性编号（0，1，2），数组代表喜好女性的列表
    vector<vector<int>> manlist = {{0,1,2},
                                   {1,0,2},
                                   {0,1,2}};
    // 索引代表女性编号（0，1，2），数组代表喜好男性的列表
    vector<vector<int>> womanlist = {{1,2,0},
                                     {0,1,2},
                                     {0,1,2}};
    Solution test;
    vector<vector<int>> result;

    result = test.stableMatching(manlist, womanlist);
    for (int i = 0; i < manlist.size(); ++i) {
        cout << result[i][0] << " - " << result[i][1] << endl;
    }
    return 0;
}
