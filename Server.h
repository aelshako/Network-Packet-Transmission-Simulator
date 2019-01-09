#include "stdafx.h"
#include "NetworkObject.h"
#pragma once

class Server : public NetworkObject{
public:
	Server(int tag);
private:
	int ServerId;
};