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
    
    static void generateArgumentToAnalysis(const std::string& rnam, const std::string& mirna,
                                           const std::string& method, const std::string& humanizer,
                                           const std::string& backend, const bool circ, const size_t org,
                                           std::string& cmd, const bool prefold, const bool dontFold);

    static void generateArgumentToComparison(const std::string& rnam, const std::string& humanizer,
                                             const bool circ, const size_t org, const std::string& tBulge,
                                             const std::string& tInterior, std::string& cmd, const bool prefold, const bool dontFold);
};

#endif
