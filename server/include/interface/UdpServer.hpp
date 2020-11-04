#include <unordered_map>

#ifndef _UDPSERVER_HPP_
#define _UDPSERVER_HPP_

#include "interface/IServer.hpp"
#include "UdpClient.hpp"
#include "Protocol.hpp"

namespace ecs {
namespace udp {

template<typename T>
class Server: public IServer<T>, public IClient<T> {
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
                    client_list.insert(e, std::make_shared<Client<T>>(asio_context, e, asio_acceptor));
                this->onMessage(i);
            }
        }
        virtual void onMessage(T msg) = 0;

    protected:
        virtual void waitForClientConnection()final {
        }
        virtual void readHeader()final {
            asio_acceptor.async_receive_from(boost::asio::buffer(&tmp.head, sizeof(MessageHeader<T>))
               *tmp_end,
               [this](std::error_code ec, std::size_t len) {
                    if (!ec) {
                        if (tmp.head.size > 0) {
                            tmp.body.resize(tmp.head.size);
                            readBody();
                        } else {
                            addToMsgQueue();
                        }
                    } else {
                        std::cerr << "[SERVER] Write Body failed: " << ec.message() << std::endl;
                        asio_acceptor.close();
                    }
            });
        }
        virtual void readBody()final {
            asio_acceptor.async_receive_from(boost::asio::buffer(tmp.body.data(), tmp.body.size())
               *tmp_end,
               [this](std::error_code ec, std::size_t len) {
                    if (!ec) {
                        addToMsgQueue();
                    } else {
                        std::cerr << "[SERVER] Write Body failed: " << ec.message() << std::endl;
                        asio_acceptor.close();
                    }
            });
        }
        virtual void writeHeader()final {};
        virtual void writeBody()final {};
        virtual void addToMsgQueue()final {
            if (!client_list.contains(tmp_end))
                client_list.insert(tmp_end, std::make_shared<Client<T>>(asio_context, tmp_end, asio_acceptor));
            tmp.remote = client_list.at(tmp_end);
            msg_in[tmp_end].push_back(tmp);
            tmp_end.reset();
            tmp_end = std::make_shared<boost::asio::ip::udp::endpoint>();
        }

    private:
        std::unordered_map<std::shared_ptr<boost::asio::ip::udp::endpoint>, std::deque<Message<T>>> msg_in;
        std::unordered_map<std::shared_ptr<boost::asio::ip::udp::endpoint>, std::shared_ptr<Client<T>>> client_list;

        boost::asio::io_context asio_context;
        std::thread context_thread;

        Message<T> tmp;
        std::shared_ptr<boost::asio::ip::udp::endpoint> tmp_end;

        boost::asio::ip::udp::socket asio_acceptor;
        uint32_t base_id = 10000;
};

}
}

#endif //_UDPSERVER_HPP_
