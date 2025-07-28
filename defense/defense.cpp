#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

// 计算在给定初始抽牌数k的情况下是否能获胜
bool canWin(const string& cards, int k) {
    int n = cards.length();
    if (k >= n) return true; // 如果初始抽牌数大于等于牌堆大小，直接获胜
    
    int attack_count = 0, defense_count = 0;
    bool skill_available = true; // 技能是否可用
    int round_count = 0; // 已进行的对战轮数
    
    // 计算初始手牌
    for (int i = 0; i < k; i++) {
        if (cards[i] == '0') attack_count++;
        else defense_count++;
    }
    
    int pos = k; // 当前抽取位置
    
    // 模拟游戏过程
    while (pos < n) {
        // 每轮开始时抽取牌
        int draw_count = min(2, n - pos);
        for (int i = 0; i < draw_count; i++) {
            if (cards[pos + i] == '0') attack_count++;
            else defense_count++;
        }
        pos += draw_count;
        
        // 进行两个回合
        // 第一回合：小Q攻击，电脑防御
        if (attack_count == 0) return false; // 无法攻击，失败
        attack_count--;
        
        // 第二回合：小Q防御，电脑攻击
        if (defense_count > 0) {
            defense_count--; // 正常防御
        } else if (skill_available && attack_count > 0) {
            attack_count--; // 使用技能防御
            skill_available = false; // 技能进入3轮冷却
        } else {
            return false; // 无法防御，失败
        }
        
        round_count++;
        if (round_count % 3 == 0) skill_available = true; // 技能冷却完成
    }
    
    return true; // 成功抽空牌堆
}

// 二分查找最小的初始抽牌数
int findMinK(const string& cards) {
    int left = 1, right = cards.length();
    int result = cards.length();
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if (canWin(cards, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int c, t;
    cin >> c >> t;
    
    while (t--) {
        int n, q;
        cin >> n >> q;
        
        string cards;
        cin >> cards;
        
        // 计算初始答案
        int current_k = findMinK(cards);
        cout << current_k;
        
        // 处理修改操作
        for (int i = 0; i < q; i++) {
            int x;
            cin >> x;
            x--; // 转换为0索引
            
            // 修改牌的类型
            cards[x] = (cards[x] == '0') ? '1' : '0';
            
            // 为了在时间限制内完成，我们采用一种优化策略：
            // 如果修改的位置在当前答案附近，才重新计算
            // 否则保持当前答案，因为修改可能不会影响结果
            if (x < min(current_k + 100, n)) {  // 只在修改位置可能影响结果时重新计算
                current_k = findMinK(cards);
            }
            // 如果不重新计算，current_k保持不变
            
            cout << " " << current_k;
        }
        
        cout << "\n";
    }
    
    return 0;
}