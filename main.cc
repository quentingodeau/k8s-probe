#include <cerrno>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "spdlog/spdlog.h"

static std::sig_atomic_t g_signal{0};

static void SigHandler(int sig) { g_signal = sig; }

constexpr in_port_t PORT = 1234;

int main(int argc, char const *argv[]) {
  signal(SIGTERM, &SigHandler);
  signal(SIGUSR1, &SigHandler);

  spdlog::set_level(spdlog::level::info);

  /* create listening TCP socket */
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in servaddr = {0};
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  // binding server addr structure to listen_fd
  if (bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
    spdlog::error("Failed to bind the socket errno={}...", errno);
    return EXIT_FAILURE;
  }
  if (listen(listen_fd, 1) != 0) {
    spdlog::error("Failed to perform listen errno={}...", errno);
    return EXIT_FAILURE;
  }

  // create a thread that will send sigusr1
  std::thread t([]() {
    std::this_thread::sleep_for(std::chrono::seconds{10});
    spdlog::info("Send SIGUSR1");
    kill(getpid(), SIGUSR1);
  });
  t.detach();

  while (g_signal == 0) {
    struct sockaddr_in client;
    socklen_t client_size = sizeof(client);
    int connection_fd =
        accept(listen_fd, (struct sockaddr *)&client, &client_size);
    if (connection_fd < 0) {
      spdlog::error("Failed to accept a client...");
      continue;
    } else {
      spdlog::info("Server acccept the client...");
    }

    // After chatting close the socket
    close(connection_fd);
  }

  if (SIGUSR1 == g_signal) {
    spdlog::info("Start to not procssing incoming connection");

    while (SIGUSR1 == g_signal) {
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  }
  spdlog::info("End of application (signal={})", g_signal);

  return (g_signal == SIGTERM) ? EXIT_SUCCESS : EXIT_FAILURE;
}
