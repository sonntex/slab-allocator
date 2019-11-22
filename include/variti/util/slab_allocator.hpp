#pragma once

#include <variti/util/thread_local_slab.hpp>

namespace variti { namespace util {

template <typename T>
class slab_allocator
{
public:

  using value_type = T;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;

  template <typename U>
  struct rebind
  {
    typedef slab_allocator<U> other;
  };

  slab_allocator() {}

  template <typename U>
  slab_allocator(const slab_allocator<U> &) {}

  pointer allocate(size_t n, const void* = 0)
  {
    auto p = static_cast<pointer>(thread_local_slab::inst().malloc(sizeof(value_type) * n));
    if (!p && n)
      throw std::bad_alloc();
    return p;
  }

  void deallocate(const_pointer p, size_t n)
  {
    thread_local_slab::inst().free(p, sizeof(value_type) * n);
  }
};

template <>
class slab_allocator<void>
{
public:

  using value_type = void;
  using pointer = void*;
  using const_pointer = const void*;

  template <class U> struct rebind { typedef slab_allocator<U> other; };
};

}}
