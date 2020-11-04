#include <vector>
#include <iostream>
#include <cstring>
#include <cstddef>
#include <memory>
#include <cstdint>

#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include "interface/IClient.hpp"
#include "Protocol.hpp"

template<typename T>
concept isLayoutStd = std::is_standard_layout<T>::value;

template<typename T>
struct MessageHeader {
    T code{};
    uint32_t size = 0;
};

template<typename T>
class Message {
    public:
        Message() = default;
        Message(const uint8_t m1, const uint8_t m2) : magic1(m1), magic2(m2) {}
        ~Message() {};

        void empty() {
            head = {};
            body.clear();
        }
        size_t size()const {
            return body.size();
        }
        bool validMagic(const uint8_t &m1, const uint8_t &m2)const {
            return this->magic1 == m1 && this->magic2 == m2;
        }
        bool validMagic(const std::pair<uint8_t, uint8_t> &p)const {
            return this->validMagic(p.first, p.second);
        }

        template<isLayoutStd D>
        void insert(D &data) {
            size_t i = body.size();
            body.resize(i + sizeof(D));
            std::memcpy(body.data() + i, &data, sizeof(D));
            head.size = body.size();
        };
        // extract data from the end of the buffer
        template<isLayoutStd D>
        void extract(D &data) {
            size_t i = body.size() - sizeof(D);
            std::memcpy(&data, body.data() + i, sizeof(D));
            body.resize(i);
            head.size = body.size();
        };

    public:
        std::shared_ptr<ecs::IClient<T>> remote = nullptr;
        uint8_t magic1;
        uint8_t magic2;
        MessageHeader<T> head{};
        std::vector<std::byte> body;
};

template<typename T>
struct OwnedMsg {
    T msg;
    std::shared_ptr<ecs::IClient<T>> remote;
};

#endif //_MESSAGE_HPP_
