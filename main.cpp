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

    Enviorment._ConnectionSize = 10;
    Enviorment._Password = "Wnsals640803";
    Enviorment._Ip = "127.0.0.1";
    Enviorment._Port = 6379;


    if(false == Manager.Initialize(ReplicationMode::EMaster, Enviorment))
    {
        return false;
    }

    PublishProperty<int32_t> Kill = Manager.IssuedPublish<int32_t>({"kill"});

    while(true)
    {
        Kill = 1;

        Manager.Comsume();
    }


    return 0;
}