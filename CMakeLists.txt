cmake_minimum_required(VERSION 3.15)
project(Replication)

set(CMAKE_CXX_STANDARD 17)

find_package(hiredis REQUIRED)

include_directories(${hiredis_INCLUDE_DIRS})
include_directories(.)

add_executable(Replication
        Command.cpp
        Command.h
        Common.h
        ConnectEnviorment.h
        Connection.cpp
        Connection.h
        ConnectionPool.h
        MultipleCallbackProperty.h
        Property.h
        PublishProperty.h
        ReplicationImpl.h
        ReplicationManager.cpp
        ReplicationManager.h
        Runnable.h
        SharedPool.h
        SubscribeProperty.h
        TypeDefine.h
        TypeTraits.h RedisConnection.cpp RedisConnection.hpp RedisCommon.h RedisAuthCommand.cpp RedisAuthCommand.hpp RedisPublishCommand.cpp RedisPublishCommand.hpp RedisSubscribeCommand.cpp RedisSubscribeCommand.hpp RedisReplicationImpl.cpp RedisReplicationImpl.hpp main.cpp)


target_link_libraries(Replication ${hiredis_LIBRARIES})


add_compile_options("-lhiredis")