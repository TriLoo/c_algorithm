/**
 * \author smh
 * \date 2018.08.08
 *
 * \brief 华为2016校招笔试题目
 *
 * \brief 分析
 *          1. 看样子输出结果是对的，但是提交后结果错误
 *          2. 一种更巧妙的做法：把文件名以及它后面的行号作为一个整体的字符串存入到vector<pair<string, int>>的string中，
 *              后面的int就是出现的次数了，然后就可以直接用sort函数以及compare函数对这个vector根据int值进行排序了，排序的结果就
 *              直接是符合要求的出现顺序了。
 *              详细的代码可以参考牛客网上面的解析。
 */

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b)
{
    return a.second > b.second;
}

struct logNode
{
    logNode(string s, long l, int c=1):filename_(s), lines_(l), count_(c){}
    string filename_;
    long lines_;
    int count_;
};

class errorLog
{
public:
    errorLog(){}

    void add_log(string filename, long lin);
    void print_log();

private:
    string getfilename(string s);    // 提取文件名
    string flipstring(string s);       // 用于翻转字符串

    vector<logNode> log_contents_;
};

void errorLog::print_log()
{
    if (log_contents_.size() <= 0)
        return;

    vector<pair<int, int>> ranks_map;   // <对应的索引，出现的次数>

    int i = 0;
    for (auto & ele : log_contents_)
    {
        ranks_map.push_back(make_pair(i, ele.count_));
        ++i;
    }

    // 排序
    stable_sort(ranks_map.begin(), ranks_map.end(), compare);     // 保证相等元素的相对顺序在排序前后是一致的

    // 打印
    i = 0;
    for (auto& ele : ranks_map)
    {
        // 最多打印8条错误信息
        if(i == 8)
            break;

        auto error_log = log_contents_.at(ele.first);
        int len = error_log.filename_.length();
        if (len < 16)
            cout << error_log.filename_ << " " << error_log.lines_ << " " << error_log.count_ << " ";
        else
        {
            cout << error_log.filename_.substr(len-16) << " " << error_log.lines_ << " " << error_log.count_ << " ";
        }
    }
}

void errorLog::add_log(string filename, long lin)
{
    string file = getfilename(filename);

    if (log_contents_.size() == 0)
    {
        log_contents_.push_back(logNode(file, lin));
        return;
    }

    int flag = 0;
    // 判断是否已经有记录了
    for (auto& ele : log_contents_)
    {
        if (ele.filename_ == file && ele.lines_ == lin)   // 有相同的记录
        {
            flag = 1;
            ele.count_ += 1;
            break;
        }
    }
    // 如果没有记录，新增一条记录
    if (!flag)
        log_contents_.push_back(logNode(file, lin));
}

string errorLog::getfilename(string s)
{
    unsigned long idx = s.rfind('\\');
    return s.substr(idx+1);   // 返回最后一个子字符串
}

string errorLog::flipstring(string s)       // 用于翻转字符串
{
    int len = s.length();
    char c;
    for (int i = 0; i <= (len >> 1); ++i)
    {
        c = s.at(i);
        s.at(i) = s.at(len - i - 1);
        s.at(len - i - 1) = c;
    }

    return s;
}


int main() {
    //std::cout << "Hello, World!" << std::endl;
    string filename;
    long lines;

    errorLog logfile;
    // for test
    //cin >> filename >> lines;
    //logfile.add_log(filename, lines);
    //logfile.print_log();
    while (cin >> filename >> lines)
        logfile.add_log(filename, lines);

    logfile.print_log();

    return 0;
}
