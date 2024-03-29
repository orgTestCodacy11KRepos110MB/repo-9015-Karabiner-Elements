#pragma once

#include <pqrs/dispatcher.hpp>
#include <pqrs/process.hpp>

namespace krbn {
namespace console_user_server {
class shell_command_handler final : public pqrs::dispatcher::extra::dispatcher_client {
public:
  shell_command_handler(const shell_command_handler&) = delete;

  shell_command_handler(void)
      : dispatcher_client() {
  }

  ~shell_command_handler(void) {
    detach_from_dispatcher([this] {
      process_ = nullptr;
    });
  }

  void run(const std::string& command) {
    process_ = std::make_unique<pqrs::process::process>(weak_dispatcher_,
                                                        std::vector<std::string>{
                                                            "/bin/sh",
                                                            "-c",
                                                            command});

    process_->stdout_received.connect([this](auto&& buffer) {
      std::string s(buffer->begin(), buffer->end());
      format_message(s);
      if (s.size() > 0) {
        logger::get_logger()->info("shell_command stdout:{0}", s);
      }
    });

    process_->stderr_received.connect([this](auto&& buffer) {
      std::string s(buffer->begin(), buffer->end());
      format_message(s);
      if (s.size() > 0) {
        logger::get_logger()->error("shell_command stderr:{0}", s);
      }
    });

    process_->run();
  }

private:
  void format_message(std::string& s) {
    std::replace(s.begin(), s.end(), '\n', ' ');
    std::replace(s.begin(), s.end(), '\r', ' ');
    pqrs::string::trim(s);
    s = pqrs::string::truncate(s, 256);
  }

  std::unique_ptr<pqrs::process::process> process_;
};
} // namespace console_user_server
} // namespace krbn
