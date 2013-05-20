#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <list>

class Service
{

public:
    static void startRemo(const std::string& cmd);
    static void getFoldingBackend(std::list<std::string>& backends);
    static void getHybridizeBackend(std::list<std::string>& backends);
    static void getHumanizerBackend(std::list<std::string>& backends);
    static void generateArgument(const std::string& rnam, const std::string& mirna,
                                 const std::string& method, const std::string& humanizer,
                                 const std::string& backend, const unsigned int circ, const unsigned int org,
                                 std::string& cmd);

};


#endif
