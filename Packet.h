#pragma once
#include <string>
#include <cstdlib>

class Packet {

public:
	void set_sourceID(int source);	//setter for sourceID
	void set_targetID(int target);  //setter for targetID
	void set_data(std::string d);   //setter for data
	int get_targetID();				//getter for targetID
	int get_sourceID();				//getter for sourceID
	std::string get_data();			//getter for data
	Packet(std::string d = "default", int tID = rand(), int sID = rand()); //The constructor will assign a default data value and random source target IDs if not specified.
	
	//The functions below are getters and setters for the variables used to calculate the travel time
	bool get_bool_entered();
	void set_bool_entered(bool state);

	void set_time_entered(int timestamp);
	int get_time_entered();

	void set_time_to_travel(int val);
	int get_time_to_travel();


private:
	int targetID;
	int sourceID;
	bool entered_network;	//signifies if the packet entered the network
	int time_entered;		//holds the time that the packet entered the network
	int time_to_travel;		//holds travel time 

	std::string data;
};