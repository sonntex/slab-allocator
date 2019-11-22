#include <variti/util/slab.hpp>

namespace variti { namespace util {

inline void* phys_to_virt_p(void* p) { return reinterpret_cast<char*>(p) + sizeof(std::thread::id); }
inline size_t phys_to_virt_n(size_t n) { return n - sizeof(std::thread::id); }
inline void* virt_to_phys_p(void* p) { return reinterpret_cast<char*>(p) - sizeof(std::thread::id); }
inline size_t virt_to_phys_n(size_t n) { return n + sizeof(std::thread::id); }

inline std::thread::id& phys_thread_id(void* p)
{ return *reinterpret_cast<std::thread::id*>(p); }

std::thread::id slab_get_thread_id(const void* p)
{
  return phys_thread_id(virt_to_phys_p(const_cast<void*>(p)));
}

slab::slab(std::size_t size, std::size_t min_object_size, float factor)
  : size_(size)
  , min_object_size_(min_object_size)
  , factor_(factor)
{
  quota_init(&quota_, QUOTA_MAX);
  slab_arena_create(&arena_, &quota_, 0, size, MAP_PRIVATE);
  slab_cache_create(&cache_, &arena_);
  small_alloc_create(&allocator_, &cache_, min_object_size, factor);
  small_alloc_setopt(&allocator_, SMALL_DELAYED_FREE_MODE, true);
  allocator_.objsize_max;
}

slab::~slab()
{
  small_alloc_destroy(&allocator_);
  slab_cache_destroy(&cache_);
  slab_arena_destroy(&arena_);
}

std::size_t slab::size() const
{
  return size_;
}

std::size_t slab::min_object_size() const
{
  return min_object_size_;
}

std::size_t slab::max_object_size() const
{
  return allocator_.objsize_max;
}

float slab::factor() const
{
  return factor_;
}

void* slab::malloc(size_t n)
{
  auto phys_n = virt_to_phys_n(n);
  auto phys_p = smalloc(&allocator_, phys_n);
  if (!phys_p)
    return nullptr;
  phys_thread_id(phys_p) = std::this_thread::get_id();
  return phys_to_virt_p(phys_p);
}

void slab::free(const void* p, size_t n)
{
  auto phys_p = virt_to_phys_p(const_cast<void*>(p));
  auto phys_n = virt_to_phys_n(n);
  assert(phys_thread_id(phys_p) == std::this_thread::get_id());
  smfree(&allocator_, phys_p, phys_n);
}

}}
