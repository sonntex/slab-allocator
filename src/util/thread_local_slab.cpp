#include <variti/util/thread_local_slab.hpp>

namespace variti { namespace util {

thread_local slab* slab_ = nullptr;

void thread_local_slab::initialize(std::size_t size, std::size_t min_object_size, float factor)
{
  assert(!slab_);
  slab_ = new slab(size, min_object_size, factor);
}

void thread_local_slab::finalize()
{
  assert(slab_);
  delete slab_;
  slab_ = nullptr;
}

slab& thread_local_slab::inst()
{
  assert(slab_);
  return *slab_;
}

}}
