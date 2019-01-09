#include "stdafx.h"
#include "packet.h"
#include <string>	//This allows us to use std::string
#include <cstdlib>
#include <ctime> 
#include <iostream>


Packet::Packet(std::string d, int tID, int sID) { //Packet constructor
	data = d;
	targetID = tID;
	sourceID = sID;
	entered_network = false;
	time_entered = 0;
	
	//std::cout << "New Packet created!!!" << " with data " << d << ", target ID " << tID << ", Source ID " << sID << std::endl;
	//std::cout << "Num packets created = " << num_Packets_created << std::endl;
}

 void Packet::set_sourceID(int source){ //sourceID setter
	 sourceID = source;
}
 
 void Packet::set_targetID(int target){  //targetID setter
	 targetID = target;
 }

 void Packet::set_data(std::string d) { //data setter
	 data = d;
 }

 int Packet::get_sourceID() {	//sourceID getter
	 return sourceID;
 }

 int Packet::get_targetID() { //targetID getter
	 return targetID;
 }
 std::string Packet::get_data() { //data getter
	 return data;
 }

 bool Packet::get_bool_entered() {		//tells whether a packet entered the network
	 return entered_network;
 }

 void Packet::set_bool_entered(bool state) {	//setter for entered_network
	 entered_network = state;
 }

 void Packet::set_time_entered(int timestamp) {	//setter for time_entered
	 time_entered = timestamp;
 }

 int Packet::get_time_entered() {				//getter for time_entered
	 return time_entered;
 }

 void Packet::set_time_to_travel(int val) {		//getter for time_to_travel
	 time_to_travel = val;
 }

 int Packet::get_time_to_travel() {				//setter for time_to_travel
	 return time_to_travel;
 }

