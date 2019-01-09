#pragma once
#include "stdafx.h"
#include "Packet.h"
#include <queue>



class NetworkObject
{
public:
	NetworkObject(int id);	//This constructor assigns an objectId to each created object
	NetworkObject();		//Default constructor(assigns objectId to zero)
	//~NetworkObject();
	int getObjectId();		//Returns the objectId
	void addPacketobj(Packet obj);	//Adds a Packet pointer to the packet queue
	void retrieve_Packets();	//This method pops all elements off the queue in a FIFO manner while displaying their values(sourceID, targetID, and data)
	void packets_isEmpty();		//This method checks if the queue is empty
	void packets_peekFront();	//This method peeks at the front of the queue
	void packets_peekBack();	//This method peeks at the back of the queue
	
	static int num_dropped;		//holds the total number of dropped packets
	static int num_transmitted;
	static float total_travel_time;
	void setmaxPackets(unsigned int max);
	unsigned int getmaxPackets();


	void addPackets(Packet Packets_to_add[], unsigned int size, bool is_start);
	Packet* getPackets( int n); // returns a pointer to the array of packets that have been removed
	void update();

	//int getnumDROPPED();			//returns number of dropped packets

	void setProb_NODE(int probability); //sets probability of packet loss for the specific NetworkObject object
	int getProb_NODE();			//returns the probability of packet loss for the specific NetworkObject object
	int get_numPackets();		//returns size of current packets queue
	//void setnext(NetworkObject& next_one);
	void setnext(NetworkObject* next_one);
	NetworkObject* getnext();

private:
	int objectId;
	unsigned int maxPackets; //This will be randomly generated only ONCE(we will make it the same for all N) 
  	std::queue<Packet> packets;	//packets is a queue of Packet pointers
	int probabilityOfPacketLoss;
	NetworkObject* next;
};

