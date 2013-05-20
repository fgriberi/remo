#include <iostream>
#include <sstream>
#include <acuoso/acuoso.h>
#include <fideo/fideo.h>
#include <etilico/etilico.h>
#include "service.h"

void Service::startRemo(const std::string& cmd)
{
    etilico::Command command = cmd;
    etilico::runCommand(command);
}

void Service::getFoldingBackend(std::list<std::string>& backends)
{
    //fideo::IFold::getAvailableBackends(backends);
    backends.push_back("RNAFold");
    backends.push_back("UNAFold");
}

void Service::getHybridizeBackend(std::list<std::string>& backends)
{
    //fideo::IHybridize::getAvailableBackends(backends);
    backends.push_back("RNAup");
    backends.push_back("RNAcofold");
    backends.push_back("RNAduplex");
    backends.push_back("RNAhybrid");
    backends.push_back("IntaRNA");
}

void Service::getHumanizerBackend(std::list<std::string>& backends)
{
    //acuoso::ICodonUsageModifier::getAvailableBackends(backends);
    backends.push_back("geneDesign");
}

void Service::generateArgument(const std::string& rnam, const std::string& mirna,
                               const std::string& method, const std::string& humanizer,
                               const std::string& backend, const unsigned int circ, const unsigned int org,
                               std::string& cmd)
{
    std::string command;
    command = "./install/remo -s ";
    command += rnam;
    command += " -m ";
    command += mirna;
    std::string version;
    if (method == "Ad hoc")
    {
        command += " -f ";
        command += backend;
        version = "OldTablesGenerator";
    }
    else
    {
        command += " -y ";
        command += backend;
        version = "NewTablesGenerator";
    }
    command += " -u ";
    command += humanizer;
    command += " -o ";
    std::ostringstream convert;
    convert << org;
    command += convert.str();
    command += " -c ";
    circ == 1 ? command += "true" : command += "false";
    command += " -v ";
    command += version;
    cmd = command;
}