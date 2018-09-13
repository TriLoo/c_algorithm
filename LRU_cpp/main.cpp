/**
 * @author smh
 * @date 2018.09.12
 *
 * @brief LUR的C++实现
 *   LRU: Least recently used
 *
 *   思路：
 *       1. LRU的主要思想是，替换掉最近不使用的内存页
 *       2. 基于likned list + hashtable of pointers to the linked list nodes 是常用的实现方式。具体如下：
 *           a. On an ccess of a value, you move the corresponding node in the linked list to the head
 *           b. When you need to remove a value from the cache, you remove from the tail end
 *           c. When you add a value to cache, you just place it at the head of the linked list
 *       3. LRU具备的操作
 *           a. set(key, value):如果key在hashmap中存在，则先重置对应的value值，然后获取对应的节点cur，将cur从链表中删除并
 *               放置在链表的头部；如果key不在hashmap中，则新建一个节点，并将节点放到链表的头部。当cache存满的时候，将链表最后
 *               一个节点删除即可。
 *           b. get(key): 如果key在hashmap中存在，则把相应的节点放在链表的头部，并返回对应的value的值，如果不存在，则返回-1
 *
 *       4. 具体实现
 *           根据上述分析，LRU用到的数据结构为list和unordered_map。list的大小是固定的，unordered_map的内容为：key对应list的
 *           节点，value对应该key所对应的value。所以LRU的数据主要还是放在后面的这个map中.
 */
#include <iostream>
#include <list>
#include <unordered_map>
#include <cassert>

using namespace std;

template <typename Key, typename Value>
class LRUCache
{
public:
    LRUCache(int n): lruSize_(n){}

    Value lruGet(Key k);
    int lruSet(Key k, Value v);
private:
    int lruSize_;
    list<Key> keyNodes_;                      // Store keys of cache
    unordered_map<Key, Value> kvMaps_;        //
    //unordered_map<Key, decltype(keyNodes_.begin())> item_map;   // 另一种数据结构
};

template <typename Key, typename Value>
Value LRUCache::lruGet(Key k)
{
    assert(kvMaps_.find(k) != kvMaps_.end());

    return kvMaps_[k];
}

template <typename Key, typename Value>
int LRUCache::lruSet(Key k, Value v)
{
    auto it = kvMaps_.find(k);
    if(it == kvMaps_.end())   // cache中没有这个kv对
    {
        if(keyNodes_.size() < lruSize_)
        {
            keyNodes_.push_front(k);
            kvMaps_[k] = v;
            return 0;
        }

        auto ele = keyNodes_.back();
        kvMaps_.erase(ele);
        keyNodes_.pop_back();
        keyNodes_.push_front(k);
        kvMaps_[k] = v;
    }
    else
    {
        kvMaps_[k] = v;
        keyNodes_.remove(k);
        keyNodes_.push_front(k);
    }

    return 0;
}

int main() {
    // under test

    return 0;
}
