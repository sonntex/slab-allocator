#pragma once

#include <variti/util/slab.hpp>

namespace variti { namespace util {

class thread_local_slab
{
public:

  static void initialize(std::size_t size, std::size_t min_object_size, float factor);
  static void finalize();

  static slab& inst();
};

}}
