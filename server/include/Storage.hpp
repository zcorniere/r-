#include <functional>
#include <unordered_map>
#include <filesystem>
#include <optional>

#ifndef _STORAGE_HPP_
#define _STORAGE_HPP_

class Storage {
    public:
        Storage(const std::string &base, std::function<bool(std::filesystem::path)> selector);
        ~Storage();
        std::optional<long> getIdFromPath(const std::string &path);
        std::optional<std::string> getPathFromId(const long id);
        std::optional<std::string> getPathFromName(const std::string &name);
        std::optional<long> getIdFromName(const std::string &name);
        const std::unordered_map<std::string, std::pair<std::string, long>> &getStorage()const;

    private:
        long base_id = 0;
        std::string base_path;
        std::unordered_map<std::string, std::pair<std::string, long>> storage_map;
};

std::ostream &operator<<(std::ostream &os, const Storage &stor);

#endif //_STORAGE_HPP_
