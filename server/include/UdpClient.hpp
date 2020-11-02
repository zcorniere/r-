#ifndef _UDPCLIENT_HPP_
#define _UDPCLIENT_HPP_

#include "MsgQueue.hpp"
#include "Protocol.hpp"
#include "interface/IClient.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

namespace ecs {
namespace udp {

template<typename T, typename E>
class Client: public IClient<E> {
    public:
        Client() = delete;
        Client(boost::asio::io_context &io_context,
               std::shared_ptr<boost::asio::ip::udp::endpoint> remote_endpoint_,
               boost::asio::ip::udp::socket &_socket) :
            socket(_socket),
            remote_endpoint(remote_endpoint_),
            context(io_context)
        {};
        virtual void gitId(const uint32_t _id = 0)final { id = _id; }
        virtual void disconnect()final {
            if (this->isConnected())
                boost::asio::post(context, [this]() { socket.close(); });
        }
        virtual void send(const T &msg)final {
            boost::asio::post(context,
                [this, msg]() {
                    q_out.push_back(msg);
                    if (!q_out.empty()) {
                        writeBody();
                    }
            });
        }

        virtual bool isConnected()const final { return socket.is_open(); }
        virtual std::string getRemoteIp()const final {
            if (this->isConnected())
                return socket.remote_endpoint().address().to_string();
            return std::string("Not Connected");
        }
        virtual const uint32_t &getId()const final { return id; }

    protected:
        virtual void readHeader()final {}
        virtual void readBody()final {}
        virtual void writeHeader()final { writeBody(); }
        virtual void writeBody()final {
            boost::asio::async_write(socket,
                boost::asio::buffer(&q_out.front(), sizeof(q_out.front())),
                [this](std::error_code ec, std::size_t len) {
                    if (!ec) {
                        q_out.pop_front();
                        if (!q_out.empty())
                            writeBody();
                    } else {
                        std::cerr << "[" << id << "] Write Bodyr failed: " << ec.message() << std::endl;
                        socket.close();
                    }
            });
        }
        virtual void addToMsgQueue()final {}

    private:
        boost::asio::ip::udp::socket &socket;
        std::shared_ptr<boost::asio::ip::udp::endpoint> remote_endpoint;
        const boost::asio::io_context &context;

        MsgQueue<E> q_out;
        uint32_t id = 0;
};

}
}
#endif //_UDPCLIENT_HPP_
