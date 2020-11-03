#include <vector>
#include <iostream>
#include <cstring>
#include <cstddef>
#include <memory>
#include <cstdint>

#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include "interface/IClient.hpp"

template<typename T>
concept isLayoutStd = std::is_standard_layout<T>::value;

template<typename T>
struct MessageHeader {
    T code{};
    uint32_t size = 0;
};

constexpr uint8_t MAGIC_NB_1 = 0xFA;
constexpr uint8_t MAGIC_NB_2 = 0xDA;

template<typename T>
class Message {
    public:
        Message() = default;
        ~Message();

        void empty() {
            head = {};
            body.clear();
        }
        size_t size()const {
            return body.size();
        }
        bool validMagic()const {
            return this->magic1 == MAGIC_NB_1 && this->magic2 == MAGIC_NB_2;
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
        uint8_t magic1 = 0xFA;
        uint8_t magic2 = 0xDA;
        MessageHeader<T> head{};
        std::vector<std::byte> body;
};

template<typename T>
struct OwnedMsg {
    T msg;
    std::shared_ptr<ecs::IClient<T>> remote;
};

#endif //_MESSAGE_HPP_
