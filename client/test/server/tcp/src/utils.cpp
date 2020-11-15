
#include <filesystem>
#include <boost/dll/runtime_symbol_info.hpp>
#include "utils.hpp"

std::string assetsGetFullPath()
{
    boost::system::error_code ec;
    auto path = boost::dll::program_location(ec);
    if (ec != boost::system::errc::errc_t::success) {
        return std::filesystem::current_path().string();
    }
    return path.parent_path().string();
}

std::string tcpCode_interpreter(TcpCode code)
{
    if (code == TcpCode::AssetAsk) return "AssetAsk";
    if (code == TcpCode::AssetPackage) return "AssetPackage";
    return "ERROR in TcpCode";
}

void print(protocol::MessageReceived<TcpCode> message)
{
    std::cout << "message received" << std::endl;
    std::cout << "head.firstbyte  : " << std::to_string(static_cast<int>(message.head().firstbyte)) << std::endl;
    std::cout << "head.secondbyte : " << std::to_string(static_cast<int>(message.head().secondbyte)) << std::endl;
    std::cout << "head.code       : " << tcpCode_interpreter(message.head().code) << std::endl;
    std::cout << "head.bodysize   : " << std::to_string(message.head().body_size) << std::endl;
    auto body = message.body();
    for (int i = 0; i < message.head().body_size; ++i) {
        std::cout << " | " << static_cast<int>(static_cast<const char *>(body.data())[i]);
    }
    if (message.head().body_size > 0)
        std::cout << std::endl;
}

void print(protocol::MessageToSend<TcpCode> message)
{
    std::cout << "message sended" << std::endl;
    std::cout << "head.firstbyte  : " << std::to_string(static_cast<int>(message.head.firstbyte)) << std::endl;
    std::cout << "head.secondbyte : " << std::to_string(static_cast<int>(message.head.secondbyte)) << std::endl;
    std::cout << "head.code       : " << tcpCode_interpreter(message.head.code) << std::endl;
    std::cout << "head.bodysize   : " << std::to_string(message.head.body_size) << std::endl;
    std::cout << "body too large" << std::endl;
//    auto body = message.body;
//    for (int i = 0; i < message.head.body_size; ++i) {
//        std::cout << " | " << static_cast<int>(static_cast<char>(body[i]));
//    }
//    if (message.head.body_size > 0)
//        std::cout << std::endl;
}

std::vector<std::byte> getTextFile(const std::string &path)
{
    std::ifstream infile(path);
    std::string line;
    std::vector<std::byte> ret;
    while (std::getline(infile, line)) {
        auto size = ret.size();
        ret.resize(ret.size() + line.size());
        std::memcpy(ret.data() + size, line.data(), line.size());
    }
    return ret;
}

std::vector<std::byte> getBinFile(const std::string &path)
{
    std::vector<std::byte> ret;
    std::ifstream input( path, std::ios::binary);
    std::vector<unsigned char> buff(std::istreambuf_iterator<char>(input), {});
    ret.resize(buff.size());
    std::memcpy(ret.data(), buff.data(), buff.size());
    return std::move(ret);
}

std::vector<std::byte> assetPackageToMsgBody(protocol::tcp::AssetPackage asset)
{
    std::vector<std::byte> ret;
    auto size = sizeof(asset.type) + sizeof(asset.id_asset) + sizeof(asset.size_data) + sizeof(asset.size_config);
    ret.resize(size + asset.size_data + asset.size_config);
    std::memcpy(ret.data(), &asset.type, size);
    std::memcpy(ret.data() + size, asset.data.data(), asset.size_data);
    size += asset.size_data;
    if (asset.size_config)
        std::memcpy(ret.data() + size, asset.config.data(), asset.size_config);
    return std::move(ret);
}