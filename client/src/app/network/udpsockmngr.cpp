/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#include "app/network/udpsockmngr.hpp"

network::UdpSockMngr::UdpSockMngr(Console &console, const std::string &ip, short port) :
    console(console), socket(context, udp::endpoint(udp::v4(), 0)) , resolver(context), received_messages()
{
    udp::resolver::query query(udp::v4(), ip, std::to_string(port));
    endpoint = *resolver.resolve(query).begin();
    do_receive();
    run_thread = std::thread([this](){context.run();});
}

network::UdpSockMngr::~UdpSockMngr()
{
    const std::lock_guard lock(this->socket_mutex);
    context.stop();
    if (run_thread.joinable())
        run_thread.join();
}

void network::UdpSockMngr::do_receive()
{
    socket.async_wait(udp::socket::wait_read, [&](const boost::system::error_code &error) {
        const std::lock_guard lock(this->socket_mutex);
        auto len = socket.available();
        if (error || len < sizeof(protocol::MessageHeader<UdpCode>))
            return;
        std::vector<std::byte> buffer;
        buffer.resize(len);
        auto size = socket.receive(boost::asio::buffer(buffer, len));
        buffer.resize(size);

        protocol::MessageReceived<UdpCode> current(std::move(buffer));
        if (current.head().firstbyte != protocol::magic_number.first || current.head().secondbyte != protocol::magic_number.second) {
        } else if (!protocol::check_size(current.head().code, current.head().body_size)) {
            console.log("Error : UDP package has wrong body size");
        } else {
            received_messages.push_back(current);
        }
        do_receive();
    });
}

void network::UdpSockMngr::send(protocol::MessageToSend<UdpCode> message)
{
    const std::lock_guard lock(this->socket_mutex);
    assert(message.body.size() == message.head.body_size);
    std::size_t length = sizeof(message.head) + message.head.body_size;
    std::vector<std::byte> buffer;
    buffer.resize(length);
    std::memcpy(buffer.data(), &message.head, sizeof(message.head));
    std::memcpy(buffer.data() + sizeof(message.head), message.body.data(), message.head.body_size);

    if (message.head.code == protocol::udp::Code::Input) {
        auto keys_size = static_cast<std::uint32_t>(sizeof(protocol::input::KeysEvent) * protocol::input::keys_array_size);
        protocol::udp::from_client::Input input;
        std::memcpy(&input.nb_keys, message.body.data(), sizeof(input.nb_keys));
        std::memcpy(input.keys.data(), message.body.data() + sizeof(input.nb_keys), keys_size);
        std::memcpy(&input.pos, message.body.data() + sizeof(input.nb_keys) + keys_size, sizeof(input.pos));
        // PRINT ALL DEBUG
        std::cout << std::dec << std::endl;
        std::cout << "I send Input: buffer.size(): " << std::dec << buffer.size() << " | length: " << length << std::endl;
        std::cout << "total sizeof : " << sizeof(protocol::udp::from_client::Input::nb_keys) + keys_size + sizeof(protocol::udp::from_client::Input::pos) << std::endl;
        std::cout << "message.head.firstbyte  : " <<  static_cast<int>(message.head.firstbyte) << std::endl;
        std::cout << "message.head.secondbyte : " << static_cast<int>(message.head.secondbyte) << std::endl;
        std::cout << "message.head.code       : " << std::hex << static_cast<int>(message.head.code) << std::endl;
        std::cout << "message.head.body_size  : " << std::dec << static_cast<int>(message.head.body_size) << std::endl;
        std::cout << "body:" << std::hex;
        for (auto i = 0; i < message.head.body_size; ++i) {
            std::cout << int(message.body[i]) << " ";
        }
        std::cout << std::dec << std::endl;
        std::cout << "cast in protocol::Input:";
        std::cout << "Input.nb_keys  : " << input.nb_keys << std::endl;
        std::cout << "Input.keys     : ";
        for (auto i = 0; i < input.nb_keys; ++i) {
            std::cout << "[";
            std::cout.put('A' + static_cast<int>(input.keys[i].key) - 3);
            std::cout << " : " << (input.keys[i].pressed ? "PRESSED" : "RELEASED") << "] ";
        }
        std::cout << std::endl;
        std::cout << "Input.MousePos : {" << input.pos.x << ", " << input.pos.y << "}" << std::endl;

    }

    socket.send_to(boost::asio::buffer(buffer, length), endpoint);
}

std::vector<protocol::MessageReceived<UdpCode>> network::UdpSockMngr::receive()
{
    const std::lock_guard lock(this->socket_mutex);
    auto ret = received_messages;
    received_messages.clear();
    return std::move(ret);
}
