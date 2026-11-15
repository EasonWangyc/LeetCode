/*
68. 文本左右对齐

给定一个单词数组 words 和一个长度 maxWidth ，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。

你应该使用 “贪心算法” 来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。

要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

文本的最后一行应为左对齐，且单词之间不插入额外的空格。

注意:

单词是指由非空格字符组成的字符序列。
每个单词的长度大于 0，小于等于 maxWidth。
输入单词数组 words 至少包含一个单词。
*/
#include <bits/stdc++.h>
using namespace std;

vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> ans;
    int n = words.size();
    int i = 0;

    while (i < n) {
        int j = i;
        int len = 0; // 当前行所有单词的字符总长度

        // 1. 贪心：计算当前行最多能放下多少个单词 [i, j-1]
        while (j < n && len + words[j].size() + (j - i) <= maxWidth) {
            len += words[j].size();
            j++;
        }

        string line = "";
        int word_count = j - i;

        // 2. 情况 1：最后一行，或者当前行只有一个单词 -> 左对齐
        if (j == n || word_count == 1) {
            for (int k = i; k < j; k++) {
                line += words[k];
                if (k < j - 1) line += " "; // 单词间加一个空格
            }
            // 行尾剩余空间全部补空格
            line.append(maxWidth - line.size(), ' ');
        } 
        // 3. 情况 2：普通行 -> 左右均匀对齐
        else {
            int total_spaces = maxWidth - len;
            int gaps = word_count - 1;
            int avg_space = total_spaces / gaps;
            int extra_space = total_spaces % gaps;

            for (int k = i; k < j; k++) {
                line += words[k];
                if (k < j - 1) {
                    // 依照题意：左侧间隔多分配一个余数空格
                    int spaces_to_add = avg_space + (k - i < extra_space ? 1 : 0);
                    line.append(spaces_to_add, ' ');
                }
            }
        }

        ans.push_back(line);
        i = j; // 推进到下一行的起始单词
    }

    return ans;
}

int main() {
    vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
    int maxWidth = 16;
    vector<string> res = fullJustify(words, maxWidth);
    for (const string& s : res) {
        cout << "\"" << s << "\"\n";
    }
    return 0;
}