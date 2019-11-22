#pragma once

#include <boost/asio/io_context.hpp>

#include <memory>

namespace variti { namespace util {

template <typename T, typename Allocator, typename... Args>
std::shared_ptr<T> slab_allocate_shared(Allocator allocator, Args... args)
{
  T* p = allocator.allocate(1);
  new ((void*)p) T(std::forward<Args>(args)...);
  std::shared_ptr<T> res(p,
    [allocator](T* p) mutable {
      p->~T();
      allocator.deallocate(p, 1);
    });
  return res;
};

template <typename T, typename Allocator, typename... Args>
std::shared_ptr<T> slab_allocate_shared(Allocator allocator, boost::asio::io_context* io, Args... args)
{
  T* p = allocator.allocate(1);
  new ((void*)p) T(std::forward<Args>(args)...);
  std::shared_ptr<T> res(p,
    [allocator, io](T* p) mutable {
      io->post(
        [allocator, p]() mutable {
          p->~T();
          allocator.deallocate(p, 1);
        });
    });
  return res;
};

}}
