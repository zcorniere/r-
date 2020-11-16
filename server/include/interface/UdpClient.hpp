#ifndef _UDPCLIENT_HPP_
#define _UDPCLIENT_HPP_

#include "MsgQueue.hpp"
#include "Protocol.hpp"
#include "interface/IClient.hpp"
#include "Snitch.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

namespace ecs {
namespace udp {

template<typename T>
class Client: public IClient<T> {
    public:
        Client(boost::asio::io_context &io_context,
               std::shared_ptr<boost::asio::ip::udp::endpoint> remote_endpoint_,
               boost::asio::ip::udp::socket &_socket) :
            remote_endpoint(remote_endpoint_),
            socket(_socket),
            context(io_context)
        {};
        virtual ~Client() { this->disconnect(); };
        virtual void disconnect()final {
            if (this->isConnected())
                boost::asio::post(context, [this]() { socket.close(); });
        }
        virtual void send(const Message<T> &msg)final {
            boost::asio::post(context,
                [this, msg]() {
                    bool writeMsg = !q_out.empty();
                    q_out.push_back(msg);
                    if (!writeMsg) {
                        writeHeader();
                    }
                });
        }

        virtual bool isConnected()const final { return socket.is_open(); }
        virtual std::string getRemoteIp()const final {
            if (this->isConnected())
                return socket.remote_endpoint().address().to_string();
            return std::string("Not Connected");
        }

    protected:
        virtual void readHeader()final {}
        virtual void readBody()final {}

        virtual void writeHeader()final { writeBody(); }
        virtual void writeBody()final {
            auto len = sizeof(q_out.front().head) + q_out.front().head.size;
            std::vector<std::byte> buffer;
            buffer.resize(len);
            std::memcpy(buffer.data(), &q_out.front().head, sizeof(q_out.front().head));
            std::memcpy(buffer.data() + sizeof(q_out.front().head), q_out.front().body.data(), q_out.front().body.size());

            socket.async_send_to(
                boost::asio::buffer(buffer, buffer.size()),
                *remote_endpoint,
                [this](std::error_code ec, std::size_t len) {
                   (void)len;
                    if (!ec) {
                        q_out.pop_front();
                        if (!q_out.empty())
                            writeHeader();
                    } else {
                        Snitch::err(std::to_string(this->getId())) << "Write Header failed: " << ec.message() << Snitch::endl;
                        socket.close();
                    }
            });
        }
        virtual void addToMsgQueue()final {}

    public:
        std::shared_ptr<boost::asio::ip::udp::endpoint> remote_endpoint;

    private:
        boost::asio::ip::udp::socket &socket;
        boost::asio::io_context &context;

        MsgQueue<Message<T>> q_out;
        Message<T> tmp;
};

}
}
#endif //_UDPCLIENT_HPP_
