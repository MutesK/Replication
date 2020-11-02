//
// Created by junmkim on 2020-11-02.
//

#include "Common.h"
#include "ReplicationManager.h"
#include "ConnectEnviorment.h"
#include <exception>

using namespace Replication;
int main()
{
    ReplicationManager Manager;
    ConnectEnviorment Enviorment;

    Enviorment._ConnectionSize = 1000;
    Enviorment._Ip = "127.0.0.1";
    Enviorment._Port = 6357;


    if(false == Manager.Initialize(ReplicationMode::EMaster, Enviorment))
    {
        return false;
    }

    auto Kill = Manager.IssuedPublish<int32_t>({"kill"});
    auto death = Manager.IssuedPublish<int32_t>({"kill"});
    auto money = Manager.IssuedPublish<int32_t>({"kill"});
    auto hp = Manager.IssuedPublish<int32_t>({"kill"});
    auto mp = Manager.IssuedPublish<int32_t>({"kill"});
    auto sp = Manager.IssuedPublish<int32_t>({"kill"});

    while(true)
    {
        Manager.Comsume();
    }


    return 0;
}