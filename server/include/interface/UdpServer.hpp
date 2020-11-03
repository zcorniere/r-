#include <unordered_map>

#ifndef _UDPSERVER_HPP_
#define _UDPSERVER_HPP_

#include "interface/IServer.hpp"
#include "UdpClient.hpp"
#include "Protocol.hpp"

namespace ecs {
namespace udp {

template<typename T, typename E>
class Server: public IServer<T> {
    public:
        Server(const unsigned port) :
            asio_acceptor(asio_context,
                          boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
        {};
        virtual ~Server() { this->stop(); };

        virtual bool start()final {
            try {
                waitForClientConnection();
                context_thread = std::thread([this]() { asio_context.run(); });
            } catch (const std::exception &e) {
                std::cerr << "[SERVER] Exception: " << e.what() << std::endl;
                return false;
            }
            std::cout << "[SERVER] Server Started" << std::endl;
            return true;
        }
        virtual void stop()final {
            asio_context.stop();
            if (context_thread.joinable()) { context_thread.join(); }
            std::cout << "[SERVER]: Stopped..." << std::endl;
        }
        virtual void update(const size_t maxMessage = -1, const bool wait = false) {
            for (auto &[e, i] : msg_in) {
                if (!client_list.contains(e))
                    client_list.insert(e, std::make_shared<Client<T, E>>(asio_context, e, asio_acceptor));
                this->onMessage(i);
            }
        }
        virtual void onMessage(T msg) = 0;

    protected:
        virtual void waitForClientConnection()final {
            asio_acceptor.async_receive_from(
                boost::asio::buffer(&msg, sizeof(T)), *tmp_end,
                [this](std::error_code ec, std::size_t len) {
                    if (!ec) {
                        msg_in[tmp_end].push_back(msg);
                        tmp_end = std::make_shared<boost::asio::ip::udp::endpoint>();
                    } else {
                        std::cerr << "[SERVER]: Connection Error :" << ec.message() << std::endl;
                    }
                    waitForClientConnection();
                });
        }

    private:
        std::unordered_map<std::shared_ptr<boost::asio::ip::udp::endpoint>, std::deque<T>> msg_in;
        std::unordered_map<std::shared_ptr<boost::asio::ip::udp::endpoint>, std::shared_ptr<Client<T, E>>> client_list;

        boost::asio::io_context asio_context;
        std::thread context_thread;

        T msg;
        std::shared_ptr<boost::asio::ip::udp::endpoint> tmp_end;

        boost::asio::ip::udp::socket asio_acceptor;
        uint32_t base_id = 10000;
};

}
}

#endif //_UDPSERVER_HPP_
