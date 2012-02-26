#include "OSCReceiver.h"

OSCReceiver::OSCReceiver()
{
}

OSCReceiver::~OSCReceiver()
{
    lo_server_thread_free(st);
}

void OSCReceiver::setPort(const int _port)
{
    port = _port;
}

void OSCReceiver::startListening()
{
    boost::thread listen(boost::bind(&OSCReceiver::listening, this));
}

void OSCReceiver::listening()
{
    const char *p = lexical_cast<string>(port).c_str();
    st = lo_server_thread_new(p, error);
    lo_server_thread_add_method(st, NULL, NULL, _genericHandler, NULL);
    lo_server_thread_start(st);

//    while(1)
//    {
//        usleep(1);
//    }
}

int OSCReceiver::genericHandler(const char *path, const char *types, lo_arg **argv, int argc, void *data)
{
    cout << "path:" << path << endl;

    for(int i = 0; i < argc; ++i)
    {
        cout << "arg" << i << ":" << types[i] << " ";
        lo_arg_pp((lo_type)types[i], argv[i]);
        cout << endl;
    }

    return 1;
}
