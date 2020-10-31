#include <vector>
#include <iostream>
#include <cstring>
#include <memory>
#include <cstdint>

#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

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
        ~Message();

        void empty() {
            head = {};
            body.clear();
        }
        size_t size()const {
            return body.size();
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
        MessageHeader<T> head{};
        std::vector<uint8_t> body;
};

#include "interface/IClient.hpp"

template<typename T>
struct OwnedMsg {
    T msg;
    std::shared_ptr<ecs::IClient<T>> remote;
};

#endif //_MESSAGE_HPP_
