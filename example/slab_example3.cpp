#include <variti/slab.hpp>

#include <boost/asio/io_context.hpp>

#include <iostream>
#include <list>
#include <thread>

int main(int argc, char* argv[])
{
  using namespace variti;
  using namespace variti::util;
  using boost::asio::io_context;
  thread_local_slab::initialize(1024 * 1024 * 1024, 2, 2.f);
  io_context io;
  slab_allocator<int> allocator;
  using int_ptr = std::shared_ptr<int>;
  std::list<int_ptr, slab_allocator<int_ptr>> list(allocator);
  list.push_back(slab_allocate_shared<int>(allocator, &io, 1));
  list.push_back(slab_allocate_shared<int>(allocator, &io, 2));
  list.push_back(slab_allocate_shared<int>(allocator, &io, 3));
  std::thread work(
    [&list]() {
      for (auto& item : list) {
        std::cout << *item << "\n";
        item = nullptr;
      }
    });  
  io.run();
  work.join();
  return 0;
}
