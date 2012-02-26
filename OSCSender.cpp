#include "OSCSender.h"

OSCSender::OSCSender()
{
}

void OSCSender::setServer(const string hostname, const int port)
{
    this->host = hostname;
    this->port = port;
}

void OSCSender::setAddress(const string address)
{
    addr = address;
}

void OSCSender::addInt(const int32_t arg)
{
    args.push_back(new OSCArgInt32(arg));
}

void OSCSender::addFloat(const float arg)
{
    args.push_back(new OSCArgFloat(arg));
}

void OSCSender::addString(const string arg)
{
    args.push_back(new OSCArgString(arg));
}

void OSCSender::send()
{
    try
    {
        cout << "send()" << endl;
        string p = lexical_cast<string>(port);
        lo_address t = lo_address_new(host.c_str(), p.c_str());

        lo_message msg = lo_message_new();
        for(int i = 0; i < args.size(); ++i)
        {
            if(args.at(i)->getType() == OSC_TYPE_INT32)
                lo_message_add_int32(msg, ((OSCArgInt32*)args.at(i))->get());
            else if(args.at(i)->getType() == OSC_TYPE_FLOAT)
                lo_message_add_float(msg, ((OSCArgFloat*)args.at(i))->get());
            else if(args.at(i)->getType() == OSC_TYPE_STRING)
                lo_message_add_string(msg, ((OSCArgString*)args.at(i))->get().c_str());
            else
            {
                assert(false && "bad argument type");
            }
        }

        lo_send_message(t, addr.c_str(), msg);
        args.clear();
    }
    catch(std::exception &e)
    {
        cerr << "OSCSender::send_lo:" << endl
             << e.what() << endl;
    }
}

