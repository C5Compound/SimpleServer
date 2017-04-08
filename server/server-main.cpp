#include <signal.h>
#include <thread>
#include <string>
#include <cstdio>
#include <iostream>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_int32(port, 8052, "listen port");

void exit_handler(int) {
    std::cout << "server exit" << std::endl;
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    signal(SIGTERM, exit_handler);

    google::InitGoogleLogging(argv[0]);
    gflags::SetVersionString("1.0.0-Alpha");
    gflags::SetUsageMessage(" Usage: --port <port> --log_dir <log directory>");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_log_dir.empty()) {
        std::cerr << "empty log dir" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (FLAGS_port < 0 || FLAGS_port > 65535) {
        std::cerr << "illegal port : " << FLAGS_port << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
