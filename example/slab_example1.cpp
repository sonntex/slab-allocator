#include <variti/slab.hpp>

#include <iostream>
#include <list>

int main(int argc, char* argv[])
{
  using namespace variti;
  using namespace variti::util;
  thread_local_slab::initialize(1024 * 1024 * 1024, 2, 2.f);
  slab_allocator<int> allocator;
  std::list<int, slab_allocator<int>> list(allocator);
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  for (auto& item : list)
    std::cout << item << "\n";
  return 0;
}
