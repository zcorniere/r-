#include "Snitch.hpp"
#include "Storage.hpp"

Storage::Storage(const std::string &base, std::function<bool(std::filesystem::path)> selector) : base_path(base)
{
    for (const auto &e: std::filesystem::directory_iterator(base)) {
        if (selector(e.path())) {
            Snitch::info("STORAGE") << "File Indexed : " << e << Snitch::endl;
            storage_map.insert({e.path().string(), {e.path().stem(), base_id++}});
        }
    }
}

Storage::~Storage()
{};

std::optional<long> Storage::getIdFromPath(const std::string &path) {
    if (storage_map.contains(path)) {
        return std::optional(storage_map.at(path).second);
    } else {
        return std::optional<long>();
    }
}

std::optional<std::string> Storage::getPathFromId(const long id) {
    for (auto &[i, e]: storage_map) {
        if (e.second == id)
            return std::optional<std::string>(i);
    }
    return std::optional<std::string>();
}

std::optional<std::string> Storage::getPathFromName(const std::string &name) {
    for (auto &[i, e]: storage_map) {
        if (e.first == name)
            return std::optional<std::string>(i);
    }
    return std::optional<std::string>();
}

std::optional<long> Storage::getIdFromName(const std::string &name) {
    for (auto &[i, e]: storage_map) {
        if (e.first == name)
            return std::optional<long>(e.second);
    }
    return std::optional<long>();
}

const std::unordered_map<std::string, std::pair<std::string, long>> &Storage::getStorage()const {
    return storage_map;
}

std::ostream &operator<<(std::ostream &os, const Storage &stor) {
    const auto map = stor.getStorage();
    os << "Storage(";
    for (const auto &[i, e] : map) {
        os << "(path: " << i << "id: " << e.second << "),";
    }
    os << ")";
    return os;
}
