
#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include "protocol.hpp"

using boost::asio::ip::tcp;
typedef boost::shared_ptr<tcp::socket> socket_ptr;

std::string assetsGetFullPath();

#define ASSETS (assetsGetFullPath() + "/assets")

std::string tcpCode_interpreter(TcpCode code);
void print(protocol::MessageReceived<TcpCode> message);
void print(protocol::MessageToSend<TcpCode> message);
void process(socket_ptr sock, protocol::MessageReceived<TcpCode> receive);

std::vector<std::byte> getTextFile(const std::string &path);
std::vector<std::byte> getBinFile(const std::string &path);
std::vector<std::byte> assetPackageToMsgBody(protocol::tcp::AssetPackage asset);

#endif
