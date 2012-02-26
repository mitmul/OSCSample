#ifndef OSCRECEIVER_H
#define OSCRECEIVER_H

#include <unistd.h>
#include <iostream>
#include <lo.h>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost;

class OSCReceiver
{
public:
    OSCReceiver();
    ~OSCReceiver();

    void setPort(const int _port);
    void startListening();

private:
    void listening();
    static void error(int num, const char *msg, const char *path)
    {
        cerr << "liblo server error " << num
             << "in path " << path
             << ": " << msg << endl;
    }

    static int _genericHandler(const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data)
    {
        ((OSCReceiver*)user_data)->genericHandler(path, types, argv, argc, data);
    }
    int genericHandler(const char *path, const char *types, lo_arg **argv, int argc, void *data);

    lo_server_thread st;
    int port;
};

#endif // OSCRECEIVER_H
