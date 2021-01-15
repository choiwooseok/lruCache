#ifndef LRUCACHE_H_
#define LRUCACHE_H_
#include <unordered_map>
#include <list>
#include <stdexcept>

namespace cache {

template<typename KEY_T, typename VAL_T>
class LRUCache {
private:
  int capacity;
  std::list<std::pair<KEY_T, VAL_T> > items;
  std::unordered_map<KEY_T, typename std::list<std::pair<KEY_T, VAL_T> >::iterator> lookup;

  // non-copyable
  LRUCache(const LRUCache&) = delete;
  LRUCache& operator=(const LRUCache&) = delete;

  // Cut out if capacity exceeded
  int prune() {
    if( capacity == 0 || lookup.size() < capacity ) {
      return 0;
    }
    int cnt = 0;
    while(lookup.size() > capacity) {
      lookup.erase(items.back().first);
      items.pop_back();
      ++cnt;
    }
    return cnt;
  }

public:
  LRUCache(int capacity) : capacity(capacity) {}
  virtual ~LRUCache() = default;
    
  std::list<std::pair<KEY_T, VAL_T> > getItems() { return items; }

  int size() { return lookup.size(); }

  bool empty() { return lookup.empty(); }
    
  void clear() {
    lookup.clear();
    items.clear();
  }

  bool contains(const KEY_T& key) {
    return lookup.find(key) != lookup.end();
  }

  void remove(const KEY_T& key) {
    auto it = lookup.find(key);
    if(it == lookup.end()) {
      return;
    }
    items.erase(it->second);
    lookup.erase(it);
  }

  void put(const KEY_T& key, const VAL_T& val) {
    auto it = lookup.find(key);
    if( it != lookup.end() ) {
      it->second->second = val;
      items.splice(items.begin(), items, it->second);
      return;
    }
    items.emplace_front(key, val);
    lookup[key] = items.begin();
    prune();
  }

 /*
  * @return VAL_T& Valid until the next [insert/delete] occurs.
  */
  const VAL_T& get(const KEY_T& key) {
    const auto it = lookup.find(key);
    if( it == lookup.end() ) {
      throw std::invalid_argument("Key does not exist");
    }
    items.splice(items.begin(), items, it->second);
    return it->second->second;
  }
};

} /* namespace cache */
#endif
