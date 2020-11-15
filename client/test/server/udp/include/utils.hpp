



#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "protocol.hpp"

using boost::asio::ip::udp;

std::string udpCode_interpreter(UdpCode code);
void print(protocol::MessageReceived<UdpCode> message);
void print(protocol::MessageToSend<UdpCode> message);
void process(udp::socket &sock, udp::endpoint &endpoint, protocol::MessageReceived<UdpCode> receive);
void printInput( protocol::MessageReceived<UdpCode> receive);

#endif