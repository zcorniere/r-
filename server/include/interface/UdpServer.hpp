#include <unordered_map>

#ifndef _UDPSERVER_HPP_
#define _UDPSERVER_HPP_

#include "interface/IServer.hpp"
#include "UdpClient.hpp"
#include "Protocol.hpp"
#include "Snitch.hpp"

namespace ecs {
namespace udp {

template<typename T>
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
                Snitch::err("UDP_SERVER") << "Exception: " << e.what() << Snitch::endl;
                return false;
            }
            Snitch::info("UDP_SERVER") << "Server Started" << Snitch::endl;
            return true;
        }
        virtual void stop()final {
            asio_context.stop();
            if (context_thread.joinable()) { context_thread.join(); }
            Snitch::info("UDP_SERVER") << "Stopped..." << Snitch::endl;
        }
        virtual void update(const size_t maxMessage = -1, const bool wait = false) {
            if (wait) msg_in.wait();
            for (size_t i = 0; i < maxMessage && !msg_in.empty(); i++) {
                auto msg = msg_in.pop_front();
                this->onMessage(msg);
            }
        }

    protected:
        virtual void waitForClientConnection()final { readHeader(); }
        virtual void msgClient(const Message<T> &msg, std::shared_ptr<IClient<T>> cli)final { (void)msg; (void)cli; };
        void msgClient(const Message<T> &msg, std::shared_ptr<Client<T>> cli) {
            if (*cli) {
                cli->send(msg);
            } else {
                Snitch::warn("UDP_SERVER") << "Sending to invalid client" << Snitch::endl;
                this->onClientDisconnect(cli);
                client_list.erase(*(cli->remote_endpoint));
            }
        }
        virtual void msgAll(const Message<T> &msg, std::shared_ptr<IClient<T>> skip = nullptr)final {
            for (auto &[_, i] : client_list) {
                if (i == skip) continue;
                this->msgClient(msg, i);
            }
        }
        virtual void onMessage(Message<T> msg) = 0;

    private:
       void readHeader() {
            asio_acceptor.async_receive_from(
                boost::asio::buffer(this->buffer.data(), this->buffer.size()),
               tmp_end,
               [this](std::error_code ec, std::size_t len) {
                    (void)len;
                    std::memcpy(&this->tmp.head, this->buffer.data(), sizeof(tmp.head));
                    if (!ec) {
                        if (tmp.head.size > 0) {
                            tmp.body.resize(tmp.head.size);
                            readBody();
                        } else {
                            addToMsgQueue();
                        }
                    } else {
                        Snitch::err("UDP_SERVER") << "ReadHeader failed: " << ec.message() << Snitch::endl;
                    }
            });
        }
        void readBody()
        {
            std::memcpy(tmp.body.data(), buffer.data() + sizeof(tmp.head),
                        tmp.head.size);
            addToMsgQueue();
        }
        void addToMsgQueue() {
            // Snitch::debug("UDP_SERVER") << tmp << Snitch::endl;
            auto tmp_ptr = std::make_shared<boost::asio::ip::udp::endpoint>(tmp_end);
            if (!client_list.contains(*(tmp_ptr))) {
                client_list.insert({*(tmp_ptr), std::make_shared<Client<T>>(asio_context, tmp_ptr, asio_acceptor)});
                this->onClientConnect(client_list.at(*(tmp_ptr)));
            }
            tmp.remote = client_list.at(*(tmp_ptr));
            msg_in.push_back(tmp);
            tmp.empty();
            waitForClientConnection();
        }

    private:
        MsgQueue<Message<T>> msg_in;
        std::unordered_map<boost::asio::ip::udp::endpoint, std::shared_ptr<Client<T>>> client_list;

        boost::asio::io_context asio_context;
        std::thread context_thread;

        Message<T> tmp;
        boost::asio::ip::udp::endpoint tmp_end;

        boost::asio::ip::udp::socket asio_acceptor;
        uint32_t base_id = 1;
        std::array<std::byte, 65535> buffer;
};

}
}

namespace std {
template <>
struct hash<boost::asio::ip::udp::endpoint>
{
    size_t operator()(const boost::asio::ip::udp::endpoint &x) const
    {
        string k = x.address().to_string();
        k += std::to_string(x.port());
        return hash<string>()(k);
    }
};
}

#endif //_UDPSERVER_HPP_
