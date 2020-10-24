#include <vector>
#include <iostream>
#include <cstring>
#include <cstdint>

#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

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

        template<typename D>
        void insert(D &data) {
            static_assert(std::is_standard_layout<D>::value, "This type requires specialisation");
            size_t i = body.size();
            body.resize(i + sizeof(D));
            std::memcpy(body.data() + i, &data, sizeof(D));
            head.size = body.size();
        };
        // extract data from the end of the buffer
        template<typename D>
        void extract(D &data) {
            static_assert(std::is_standard_layout<D>::value, "This type requires specialisation");
            size_t i = body.size() - sizeof(D);
            std::memcpy(&data, body.data() + i, sizeof(D));
            body.resize(i);
            head.size = body.size();
        };

    public:
        MessageHeader<T> head{};
        std::vector<uint8_t> body;
};
#endif //_MESSAGE_HPP_
