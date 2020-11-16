#include "Snitch.hpp"
#include "Storage.hpp"

Storage::Storage(const std::string &base, std::function<bool(std::filesystem::path)> selector) : base_path(base)
{
    for (const auto &e: std::filesystem::directory_iterator(base)) {
        if (selector(e.path())) {
            Snitch::info("STORAGE") << "File Indexed : " << e << Snitch::endl;
            storage_map.insert({e.path().string(), base_id++});
        }
    }
}

Storage::~Storage()
{};

std::optional<long> Storage::getIdFromPath(const std::string &path) {
    if (storage_map.contains(path)) {
        return std::optional(storage_map.at(path));
    } else {
        return std::optional<long>();
    }
}

std::optional<std::string> Storage::getPathFromId(const long id) {
    for (auto &[i, e]: storage_map) {
        if (e == id)
            return std::optional<std::string>(i);
    }
    return std::optional<std::string>();
}

const std::unordered_map<std::string, long> &Storage::getStorage()const {
    return storage_map;
}

std::ostream &operator<<(std::ostream &os, const Storage &stor) {
    const auto map = stor.getStorage();
    os << "Storage(";
    for (const auto &[i, e] : map) {
        os << "(path: " << i << "id: " << e << "),";
    }
    os << ")";
    return os;
}
