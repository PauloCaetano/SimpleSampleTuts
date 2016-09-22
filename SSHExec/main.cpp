#include "ssh/sshexception.h"
#include "ssh/misc.h"
#include "ssh/sshsession.h"

#include <boost/exception/all.hpp>
using boost::diagnostic_information;
#include <boost/bind.hpp>

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;

using CommandList = vector<string>;

CommandList CreateCommands()
{
    vector<string> commands;
    commands.push_back("date");
    commands.push_back("cd some_dir ; ./run_some_script.sh");
    commands.push_back("ls -ltr ./some_dir/*.result");
    return commands;
}

void ShowStatus(string s)
{
    cout << s << '\n';
}

int main(int /*argc*/, char */*argv*/[])
{
    try
    {
        CommandList commands{CreateCommands()};
        pt::pcaetano::bluesy::ssh::ConnectionInfo ci;
        ci.host = "localhost";
        ci.port = "22";
        ci.user = "user";
        ci.pwd = "password";

        pt::pcaetano::bluesy::ssh::SSHSession sess(ci, boost::bind(ShowStatus, _1));

        for (auto const& cmd: commands)
        {
            sess.ExecuteCommand(cmd, boost::bind(ShowStatus, _1));
        }
    }
    catch (std::exception& ex)
    {
        cerr << diagnostic_information(ex) << endl;
        exit(1);
    }

}
