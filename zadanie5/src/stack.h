#ifndef STACK_H
#define STACK_H

#include <list>
#include <map>
#include <memory>
#include <optional>
#include <tuple>
#include <utility>

namespace cxx {
template <typename K, typename V>
class stack {
 public:
  stack() : data(std::make_shared<data_s>()), is_copyable(true) {}

  stack(stack const &that) : data(that.data), is_copyable(true) {
    if (that.is_copyable == false) {
      copy();
    }
  }
  
  stack(stack &&that) noexcept
      : data(std::move(that.data)), is_copyable(std::move(that.is_copyable)) {
    that.clear();
  }

  stack &operator=(stack that) noexcept {
    this->swap(that);
    return *this;
  }

  void push(K const &key, V const &value) {
    if (data.get() == nullptr) {
      data = std::make_shared<data_s>();
    }

    Guard guard(data);

    // One use_count corresponds to guard.
    if (data.use_count() > 2) {
      copy();
    }

    guard.add_possible_copy(this);

    map_iter_wrap map_it;
    same_key_list_iter_wrap same_key_list_it;

    std::tie(map_it, same_key_list_it) = data->add_to_map(key, value);
    guard.add_to_map(map_it);

    data->main_list.emplace_front(map_it, same_key_list_it);

    same_key_list_it.iter->second = {data->main_list.begin()};

    guard.add_to_list({data->main_list.begin()});
    guard.success();

    is_copyable = true;
  }

  void pop() {
    if (data.get() == nullptr || data->main_list.empty()) {
      throw std::invalid_argument("Stack does not contain any values.");
    }

    if (data.use_count() > 1) {
      copy();
    }

    data->pop_from_map(data->main_list.front().map_iter);
    data->main_list.pop_front();

    is_copyable = true;
  }

  void pop(K const &key) {
    if (data.get() == nullptr) {
      throw std::invalid_argument(
          "Stack does not contain any values corresponding to the given key.");
    }

    // Guard is used because map function find may throw an exception.
    Guard guard(data);

    if (data.use_count() > 2) {
      copy();
    }

    guard.add_possible_copy(this);

    map_iter_wrap map_it = {data->same_key_lists.find(key)};

    if (map_it.iter == data->same_key_lists.end()) {
      throw std::invalid_argument(
          "Stack does not contain any values corresponding to the given key.");
    }

    data->main_list.erase(
        map_it.iter->second.same_key_list.front().second.iter);
    data->pop_from_map(map_it);

    guard.success();
    is_copyable = true;
  }

  std::pair<K const &, V &> front() {
    if (data.get() == nullptr || data->main_list.empty()) {
      throw std::invalid_argument("Stack does not contain any values.");
    }

    if (data.use_count() > 1) {
      copy();
    }

    is_copyable = false;

    return {data->main_list.front().map_iter.iter->first,
            data->main_list.front().map_list_iter.iter->first};
  }

  std::pair<K const &, V const &> front() const {
    if (data.get() == nullptr || data->main_list.empty()) {
      throw std::invalid_argument("Stack does not contain any values.");
    }

    return {data->main_list.front().map_iter.iter->first,
            data->main_list.front().map_list_iter.iter->first};
  }

  V &front(K const &key) {
    if (data.get() == nullptr) {
      throw std::invalid_argument(
          "Stack does not contain any values corresponding to the given key.");
    }

    Guard guard(data);

    // One use_count corresponds to guard.
    if (data.use_count() > 2) {
      copy();
    }

    guard.add_possible_copy(this);

    map_iter_wrap map_it = {data->same_key_lists.find(key)};

    if (map_it.iter == data->same_key_lists.end()) {
      throw std::invalid_argument(
          "Stack does not contain any values corresponding to the given key.");
    }

    is_copyable = false;

    guard.success();

    return map_it.iter->second.same_key_list.front().first;
  }

  V const &front(K const &key) const {
    if (data.get() == nullptr) {
      throw std::invalid_argument("Stack does not contain any values.");
    }

    map_iter_wrap map_it = {data->same_key_lists.find(key)};

    if (map_it.iter == data->same_key_lists.end()) {
      throw std::invalid_argument("Stack does not contain any values.");
    }

    return map_it.iter->second.same_key_list.front().first;
  }

  size_t size() const noexcept {
    if (data.get() == nullptr) {
      return 0;
    }

    return data->main_list.size();
  }

  size_t count(K const &key) const {
    if (data.get() == nullptr) {
      return 0;
    }

    map_iter_wrap map_it = {data->same_key_lists.find(key)};

    if (map_it.iter == data->same_key_lists.end()) {
      return 0;
    }

    return map_it.iter->second.same_key_list.size();
  }

  void clear() noexcept {
    data.reset();
    is_copyable = true;
  }

 private:
  // Wrapper structs for iterators;
  struct list_iter_wrap;
  struct map_iter_wrap;
  struct same_key_list_iter_wrap;

  struct map_value_s;
  struct list_element_s;
  struct data_s;

 public:
  class const_iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = const K;
    using reference_type = const K &;
    using pointer_type = const K *;
    using iterator_type = std::map<K, map_value_s>::const_iterator;

   private:
    iterator_type iter;
    bool empty_contaier_it;

   public:
    const_iterator() : iter(), empty_contaier_it(true) {}
    const_iterator(const iterator_type &_iter)
        : iter(_iter), empty_contaier_it(false) {}
    const_iterator(const const_iterator &other) {
      empty_contaier_it = other.empty_contaier_it;
      iter = other.iter;
    }

    const_iterator &operator=(const const_iterator &other) {
      empty_contaier_it = other.empty_contaier_it;
      iter = other.iter;
      return *this;
    }

    reference_type operator*() const noexcept { return iter->first; }

    pointer_type operator->() const noexcept { return &(iter->first); }

    const_iterator &operator++() {
      iter++;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const const_iterator &iterator_1,
                           const const_iterator &iterator_2) {
      if (iterator_1.empty_contaier_it || iterator_2.empty_contaier_it) {
        return iterator_1.empty_contaier_it && iterator_2.empty_contaier_it;
      }
      return iterator_1.iter == iterator_2.iter;
    }

    friend bool operator!=(const const_iterator &iterator_1,
                           const const_iterator &iterator_2) {
      return !(iterator_1 == iterator_2);
    }
  };

  const_iterator cbegin() const {
    if (data.get() == nullptr) {
      return const_iterator();
    }
    return const_iterator((data.get()->same_key_lists).cbegin());
  }

  const_iterator cend() const {
    if (data.get() == nullptr) {
      return const_iterator();
    }
    return const_iterator((data.get()->same_key_lists).cend());
  }

 private:
  struct list_iter_wrap {
    std::list<list_element_s>::iterator iter;
  };

  struct map_iter_wrap {
    std::map<K, map_value_s>::iterator iter;
  };

  struct same_key_list_iter_wrap {
    std::list<std::pair<V, list_iter_wrap>>::iterator iter;
  };

  struct map_value_s {
    std::list<std::pair<V, list_iter_wrap>> same_key_list;
  };

  struct list_element_s {
    map_iter_wrap map_iter;
    same_key_list_iter_wrap map_list_iter;
  };

  struct data_s {
    std::map<K, map_value_s> same_key_lists;
    std::list<list_element_s> main_list;

    // Adds key and value to map.
    // Returns iterator to map with corresponding key and
    // iterator to list where the value is hold.
    std::pair<map_iter_wrap, same_key_list_iter_wrap> add_to_map(
        K const &key, V const &value) {
      map_iter_wrap map_it = {same_key_lists.find(key)};

      if (map_it.iter == same_key_lists.end()) {
        map_it.iter = same_key_lists
                          .emplace(key, map_value_s{std::list{std::make_pair(
                                            value, list_iter_wrap())}})
                          .first;
      } else {
        map_it.iter->second.same_key_list.emplace_front(
            value, list_iter_wrap());
      }

      return {map_it, {map_it.iter->second.same_key_list.begin()}};
    }

    // Removes first value from list at given iterator.
    void pop_from_map(map_iter_wrap map_it) {
      map_it.iter->second.same_key_list.pop_front();

      if (map_it.iter->second.same_key_list.empty()) {
        same_key_lists.erase(map_it.iter);
      }
    }
  };

  std::shared_ptr<data_s> data;
  bool is_copyable;

  void swap(stack &that) noexcept {
    std::swap(data, that.data);
    std::swap(is_copyable, that.is_copyable);
  }

  // Creates a copy of the data and swaps it if an exception has not been thrown.
  void copy() {
    std::shared_ptr<data_s> data_cpy = std::make_shared<data_s>();

    for (auto it = data->main_list.rbegin(); it != data->main_list.rend();
         it++) {
      map_iter_wrap map_it;
      same_key_list_iter_wrap map_list_it;

      std::tie(map_it, map_list_it) = data_cpy->add_to_map(
          it->map_iter.iter->first, it->map_list_iter.iter->first);
      data_cpy->main_list.emplace_front(map_it, map_list_it);

      map_list_it.iter->second = {data_cpy->main_list.begin()};
    }

    std::swap(data_cpy, data);
  }

  struct Guard {
    // Holds data that was used before call to given function.
    std::shared_ptr<data_s> data_before_cpy;
    // Holds pointer to stack used in given function.
    // this_stack is used to rollback data if copy was made before exception.
    stack<K, V> *this_stack;
    // Iterators to the points where new elements were added.
    std::optional<map_iter_wrap> map_it;
    std::optional<list_iter_wrap> list_it;
    bool succeed;

    Guard(std::shared_ptr<data_s> data1)
        : data_before_cpy(data1), this_stack(nullptr), succeed(false) {}

    void add_possible_copy(stack *this_stack1) { this_stack = this_stack1; }

    void add_to_map(map_iter_wrap map_it2) { map_it = map_it2; }

    void add_to_list(list_iter_wrap list_it2) { list_it = list_it2; }

    void success() { succeed = true; }

    ~Guard() {
      if (succeed) {
        return;
      }

      if (this_stack != nullptr && data_before_cpy != this_stack->data) {
        this_stack->data = data_before_cpy;
        return;
      }

      if (map_it.has_value()) {
        data_before_cpy->pop_from_map(map_it.value());
      }

      if (list_it.has_value()) {
        data_before_cpy->main_list.erase(list_it.value().iter);
      }
    }
  };
};
}  // namespace cxx

#endif /* STACK_H */