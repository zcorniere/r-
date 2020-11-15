
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>
#include "protocol.hpp"
#include "utils.hpp"

static std::vector<std::byte> receive(udp::socket& sock, udp::endpoint &endpoint)
{
    sock.wait(boost::asio::socket_base::wait_read);
    auto len = sock.available();
    std::vector<std::byte> buff;
    buff.resize(len);
    auto size = sock.receive_from(boost::asio::buffer(buff, len), endpoint);
    buff.resize(size);
    print(protocol::MessageReceived<UdpCode>(buff));
    return std::move(buff);
}

[[noreturn]] void server(boost::asio::io_context& io_context, unsigned short port)
{
    std::cout << "UDP SERVER is running" << std::endl;
    udp::socket sock(io_context, udp::endpoint(udp::v4(), port));
    udp::endpoint endpoint;
    for (;;) {
        std::cout << "#####" << std::endl;
        // receive data
        protocol::MessageReceived<UdpCode> message(std::move(receive(sock, endpoint)));
        std::cout << "--" << std::endl;
        process(sock, endpoint, message);
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        server(io_context, 25555);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}