#pragma once

#define REPLICATION_REDIS

#include <functional>
#include <list>
#include <algorithm>
#include <string>
#include <memory>
#include <exception>
#include <ctime>
#include <cstdlib>

#ifndef WIN32
#define abstract
#endif

#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_map>

namespace Util
{
    template<typename ... Args>
    std::string Format(const std::string &format, Args ... args)
    {
        size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size <= 0)
        {
            throw std::runtime_error("Error during formatting.");
        }
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }
}