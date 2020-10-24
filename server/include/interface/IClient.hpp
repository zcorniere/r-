#include <memory>

#include "Message.hpp"

#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

template<typename T>
class IClient: public std::enable_shared_from_this<IClient<T>> {
    public:
        IClient() = delete;
        virtual ~IClient() { this->disconnect(); };

        virtual void giveId(const uint32_t id = 0) = 0;
        virtual void disconnect() = 0;
        virtual void send(const Message<T> &msg) = 0;

        virtual bool isConnected()const = 0;
        virtual std::string getRemoteIp()const = 0;
        virtual const uint32_t &getId()const = 0;
        operator bool() { return this->isConnected(); };

    protected:
        virtual void readHeader() = 0; // ASYNC
        virtual void readBody() = 0; // ASYNC
        virtual void writeHeader() = 0; // ASYNC
        virtual void writeBody() = 0; // ASYNC
        virtual void addToMsgQueue() = 0;

};

#endif //_CLIENT_HPP_
