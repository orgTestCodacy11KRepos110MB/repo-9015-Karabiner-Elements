#include "dispatcher_utility.hpp"
#include "monitor/version_monitor.hpp"
#include "run_loop_thread_utility.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
  auto scoped_dispatcher_manager = krbn::dispatcher_utility::initialize_dispatchers();
  auto scoped_run_loop_thread_manager = krbn::run_loop_thread_utility::initialize_shared_run_loop_thread();

  signal(SIGINT, [](int) {
    CFRunLoopStop(CFRunLoopGetMain());
  });

  auto monitor = std::make_unique<krbn::version_monitor>(krbn::constants::get_version_file_path());

  monitor->changed.connect([](auto&& version) {
    krbn::logger::get_logger()->info("changed");
  });

  monitor->async_start();

  CFRunLoopRun();

  monitor = nullptr;

  scoped_run_loop_thread_manager = nullptr;
  scoped_dispatcher_manager = nullptr;

  std::cout << "finished" << std::endl;

  return 0;
}
