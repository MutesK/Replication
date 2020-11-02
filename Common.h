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
#include <stdarg.h>

namespace Util
{
    struct StringHelper {
        static std::string Format(const std::string fmt, ...)
        {
            int size = ((int) fmt.size()) * 2;
            std::string buffer;
            va_list ap;
            while (1)
            {
                buffer.resize(size);
                va_start(ap, fmt);
                int n = vsnprintf((char *) buffer.data(), size, fmt.c_str(), ap);
                va_end(ap);
                if (n > -1 && n < size)
                {
                    buffer.resize(n);
                    return buffer;
                }
                if (n > -1)
                    size = n + 1;
                else
                    size *= 2;
            }

            return buffer;
        }
    };
}