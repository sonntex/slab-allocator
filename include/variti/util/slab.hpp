#pragma once

#include <thread>

#include <small/quota.h>
#include <small/slab_arena.h>
#include <small/slab_cache.h>
#include <small/small.h>

namespace variti { namespace util {

std::thread::id slab_get_thread_id(const void* p);

class slab
{
public:

  slab(std::size_t size, std::size_t min_object_size, float factor);

  slab(const slab&) = delete;
  slab& operator=(const slab&) = delete;
  slab(slab&&) = delete;
  slab& operator=(slab&&) = delete;

 ~slab();

  std::size_t size() const;
  std::size_t min_object_size() const;
  std::size_t max_object_size() const;
  float factor() const;

  void* malloc(std::size_t n);
  void free(const void* p, std::size_t n);

private:

  std::size_t size_;
  std::size_t min_object_size_;
  float factor_;

  struct quota quota_;
  struct slab_arena arena_;
  struct slab_cache cache_;
  struct small_alloc allocator_;
};

}}
