#ifndef OSCSENDER_H
#define OSCSENDER_H

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <UdpSocket.h>
#include <OscOutboundPacketStream.h>
#include <lo.h>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

typedef enum _OSCArgType
{
    OSC_TYPE_NONE,
    OSC_TYPE_INT32,
    OSC_TYPE_FLOAT,
    OSC_TYPE_STRING,
    OSC_TYPE_BLOB,
    OSC_TYPE_BUNDLE,
    OSC_TYPE_INDEXOUTOFBOUNDS
} OSCArgType;

class OSCArg
{
public:
    OSCArg() {}
    virtual ~OSCArg() {}

    virtual OSCArgType getType() { return OSC_TYPE_NONE; }
    virtual string getTypeName() { return "none"; }
};

class OSCArgInt32 : public OSCArg
{
public:
    OSCArgInt32(int32_t _value) { value = _value; }
    ~OSCArgInt32() {}

    OSCArgType getType() { return OSC_TYPE_INT32; }
    string getTypeName() { return "int32_t"; }

    int32_t get() const { return value; }
    void set(int32_t _value) { value = _value; }

private:
    int32_t value;
};

class OSCArgFloat : public OSCArg
{
public:
    OSCArgFloat(float _value) { value = _value; }
    ~OSCArgFloat() {}

    OSCArgType getType() { return OSC_TYPE_FLOAT; }
    string getTypeName() { return "float"; }

    float get() const { return value; }
    void set(float _value) { value = _value; }

private:
        float value;
};

class OSCArgString : public OSCArg
{
public:
    OSCArgString(string _value) { value = _value; }
    ~OSCArgString() {}

    OSCArgType getType() { return OSC_TYPE_STRING; }
    string getTypeName() { return "string"; }

    string get() const { return value; }
    void set(const char* _value) { value = _value; }

private:
    string value;
};

class OSCSender
{
public:
    OSCSender();

    void setServer(const string hostname, const int port);
    void setAddress(const string address);
    void addInt(const int32_t arg);
    void addFloat(const float arg);
    void addString(const string arg);

    void send();
    void send_lo();

private:
    void shutdown();

    UdpTransmitSocket *socket;
    string host;
    int port;
    string addr;

    vector<OSCArg*> args;
};

#endif // OSCSENDER_H
