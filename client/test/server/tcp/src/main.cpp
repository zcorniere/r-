
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "protocol.hpp"
#include "utils.hpp"

static std::vector<std::byte> receive(socket_ptr &sock, boost::system::error_code &error)
{
    std::vector<std::byte> buff;
    protocol::MessageHeader<TcpCode> head;
    buff.resize(sizeof(head));
    sock->read_some(boost::asio::buffer(buff, buff.size()), error);
    if (error)
        return std::vector<std::byte>();
    std::memcpy(&head, buff.data(), sizeof(head));
    buff.resize(buff.size() + head.body_size);
    sock->read_some(boost::asio::buffer(buff.data() + sizeof(head), head.body_size), error);
    return buff;
}

void session(socket_ptr sock)
{
    std::cout << "[TCP] connection accepted" << std::endl;
    boost::system::error_code error;
    try {
        for (;;) {
            std::cout << "#####" << std::endl;
            auto buff = receive(sock, error);
            if (error == boost::asio::error::eof) {
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }
            protocol::MessageReceived<TcpCode> received(std::move(buff));
            print(received);
            std::cout << "--" << std::endl;
            process(sock, received);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

[[noreturn]] void server(boost::asio::io_service& io_service, unsigned short port)
{
    std::cout << "TCP SERVER is running" << std::endl;
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
    for (;;) {
        socket_ptr sock(new tcp::socket(io_service));
        a.accept(*sock);
        boost::thread t(boost::bind(session, sock));
    }
}

int main()
{
    try {
        boost::asio::io_service io_service;
        server(io_service, 25545);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}