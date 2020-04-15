#include "events.h"

void EventHandler::InvokeEvent(Event *event,bool isDelete)
{
    std::vector<listener> vec = this->listenersHigh[event->name];
    for(int i=0;i<vec.size();i++){
        vec[i](event);
        if(event->CancleState){
            return;
        }
    }
    vec = this->listenersMid[event->name];
    for(int i=0;i<vec.size();i++){
        vec[i](event);
        if(event->CancleState){
            return;
        }
    }
    vec = this->listenersLow[event->name];
    for(int i=0;i<vec.size();i++){
        vec[i](event);
        if(event->CancleState){
            return;
        }
    }

    if(isDelete)
    {
        delete event;
    }
}
 
void EventHandler::RegistryListeners(std::string event,listener lis,int Level)
{
    switch(Level)
    {
        case Event_Low:
            this->listenersLow[event].push_back(lis);
            break;
        case Event_Mid:
            this->listenersMid[event].push_back(lis);
            break;
        case Event_High:
            this->listenersHigh[event].push_back(lis);
            break;
    }
}