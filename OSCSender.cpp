#include "OSCSender.h"

OSCSender::OSCSender()
{
    socket = NULL;
}

void OSCSender::setServer(const string hostname, const int port)
{
    if(socket)
        shutdown();

    socket = new UdpTransmitSocket(IpEndpointName(hostname.c_str(), port));

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
        static const int OUTPUT_BUFFER_SIZE = 1024;
        char buf[OUTPUT_BUFFER_SIZE];

        osc::OutboundPacketStream p(buf, OUTPUT_BUFFER_SIZE);

        p << osc::BeginBundleImmediate;
        p << osc::BeginMessage(addr.c_str());
        for(int i = 0; i < args.size(); ++i)
        {
            if(args.at(i)->getType() == OSC_TYPE_INT32)
                p << ((OSCArgInt32*)args.at(i))->get();
            else if(args.at(i)->getType() == OSC_TYPE_FLOAT)
                p << ((OSCArgFloat*)args.at(i))->get();
            else if(args.at(i)->getType() == OSC_TYPE_STRING)
                p << ((OSCArgString*)args.at(i))->get().c_str();
            else
            {
                assert(false && "bad argument type");
            }
        }
        p << osc::EndMessage;
        p << osc::EndBundle;

        socket->Send(p.Data(), p.Size());
    }
    catch(std::exception &e)
    {
        cerr << "OSCSender::send:" << endl
             << e.what() << endl;
    }
}

void OSCSender::send_lo()
{
    try
    {
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
    }
    catch(std::exception &e)
    {
        cerr << "OSCSender::send_lo:" << endl
             << e.what() << endl;
    }
}

void OSCSender::shutdown()
{
    if(socket)
        delete socket;

    socket = NULL;
}

