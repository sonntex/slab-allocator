#include <variti/slab.hpp>

#include <iostream>
#include <list>

int main(int argc, char* argv[])
{
  using namespace variti;
  using namespace variti::util;
  thread_local_slab::initialize(1024 * 1024 * 1024, 2, 2.f);
  slab_allocator<int> allocator;
  using int_ptr = std::shared_ptr<int>;
  std::list<int_ptr, slab_allocator<int_ptr>> list(allocator);
  list.push_back(slab_allocate_shared<int>(allocator, 1));
  list.push_back(slab_allocate_shared<int>(allocator, 2));
  list.push_back(slab_allocate_shared<int>(allocator, 3));
  for (auto& item : list) {
    std::cout << *item << "\n";
    item = nullptr;
  }
  return 0;
}
