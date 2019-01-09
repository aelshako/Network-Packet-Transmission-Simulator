#include "stdafx.h"
#include "NetworkObject.h"
#include <queue>		//This allows us to use std::queue
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Packet.h"
#include <random>

 int NetworkObject::num_dropped = 0;
 int NetworkObject::num_transmitted = 0;
 float NetworkObject::total_travel_time = 0;

NetworkObject::NetworkObject() {			//Default constructor(sets objectId = 0)
	objectId = 0;		
	next = nullptr;
}

NetworkObject::NetworkObject(int id) {		//This constructor is used when a network object is created with an objectId passed in
	objectId = id;						//setting the objectId
	next = nullptr;
}

int NetworkObject::getObjectId() {	//getter for the ObjectId of a NetworkObject
	return objectId;
}

void NetworkObject::addPacketobj(Packet obj) {	//This method takes a Packet object and adds it to the queue (it acts as an incremental helper function invoked by addpackets to add multiple packets)
	packets.push(obj);			//Pushing the pointer onto queue
	
	//I will leave the comments below because they are very useful since they allow the user to view which objects are being added(in real time)

    //std::cout << std::endl;			//Adding a blank line
	//std::cout << "Added an object to packets queue" << std::endl;	//This line and the 3 below it notify the user of the characteristics of the object that has been added to the queue
	//std::cout <<"targetID: " << obj.get_targetID() << std::endl; 
	//std::cout << "source ID: " << obj.get_sourceID() << std::endl;
	//std::cout << "data: " << obj.get_data() <<  std::endl << std::endl;
}

void NetworkObject::retrieve_Packets() {		//This method pops(removes) all of the elements from the queue 1 by 1 while displaying their internal values
	std::cout << "retrieve_packets:" << std::endl;
	if (packets.empty()) {			//If the queue is empty, we notify the user that the operation cannot be performed
		std::cout << "Cannot retrieve packets because the packets queue is empty!" << std::endl;
	}
	else {			//This code-block runs only when the queue is non-empty
		std::cout << "Packets will be popped off 1 by 1 and their members will be displayed below (in FIFO manner):" << std::endl;
		while (packets.empty() == false) {	//This loop runs so long as the queue is not empty
			Packet currentObj = packets.front();		//We start with the front of the queue to show packets in FIFO manner
			std::cout << "targetID: " << currentObj.get_targetID() << std::endl; //Displaying current targetID
			std::cout << "source ID: " << currentObj.get_sourceID() << std::endl; //Displaying current sourceID
			std::cout << "data:" << currentObj.get_data() << std::endl << std::endl; //Displaying the current data
			packets.pop();	//Popping the front-most queue element for each iteration of the loop
		}
	}
}

void NetworkObject::packets_isEmpty(){		//This method checks if the queue is empty
	if (packets.empty()==true) {	
		std::cout << std::endl <<"The queue of packet objects is EMPTY" << std::endl << std::endl;
	}
	else {
		std::cout <<std::endl <<"The queue of packet objects is NOT EMPTY" << std::endl << std::endl;
	}
}

void NetworkObject::packets_peekFront() {		//This method allows the user to peek onto the front of the packets queue
	std::cout << std::endl << "Peek Front:" << std::endl;
	if (packets.empty() == false) {
		Packet front = packets.front();	//Temporarily holding the frontmost element of the queue, so we can display its data
		std::cout << "targetID: " << front.get_targetID() << std::endl;
		std::cout << "source ID: " << front.get_sourceID() << std::endl;
		std::cout << "data:" << front.get_data() << std::endl << std::endl;
	}
	else {
		std::cout << std::endl <<"Cannot peek at front of queue because the queue is empty!" << std::endl; //printing error message if queue is empty
	}
	}

void NetworkObject::packets_peekBack() {	//This method allows the user to peek onto the back of the packets queue
	std::cout << std::endl << "Peek Back:" << std::endl;	
	if (packets.empty() == false) {	//This block of code executes if the packets queue is empty
		Packet back = packets.back();	//Temporarily holding the back-most queue element in the packets queue
		std::cout << "targetID: " << back.get_targetID() << std::endl;
		std::cout << "source ID: " << back.get_sourceID() << std::endl;
		std::cout << "data:" << back.get_data() << std::endl << std::endl;
	}
	else {
		std::cout << std::endl << "Cannot peek at front of queue because the queue is empty!" << std::endl; //printing error message if queue is empty
	}
}



void NetworkObject::addPackets(Packet Packets_to_add[],  unsigned int size, bool is_start) {		//adds an array of packet objects to the packets queue
		//The boolean variable is_start is used to signify whether packets are being added to the first node.
		//is_start allows us to set the time that a packet entered the network
	
	
	if (is_start == false) {		//we enter here if we are adding to a node that isn't at the front of the list
		if (size > maxPackets) {			//capping the size if its bigger than maxPackets (My code in main doesn't invoke this case, but I feel that its important to include this case as it makes the code more flexible/robust)
			size = maxPackets;
		}

		for (unsigned int i = 0; (i < size) && (packets.size() < maxPackets); i++) {	//adding the packets
			addPacketobj(Packets_to_add[i]);
		}
	}
	else {					//entering here means that is_start is true, so we are adding to the first NetworkObject, and must set the variable entered_network to true
		if (size > maxPackets) {			//capping the size if its bigger than maxPackets
			size = maxPackets;
		}

		for (unsigned int i = 0; (i < size) && (packets.size() < maxPackets); i++) {		//Adding the packets and setting the time they entered the network
			Packets_to_add[i].set_bool_entered(true);		//signifying that the packet entered the network
			Packets_to_add[i].set_time_entered(time(0));
			addPacketobj(Packets_to_add[i]);
		}
	}


}


Packet* NetworkObject::getPackets( int n ) {
	
	std::cout <<"\n" << "get_packets:" << std::endl;
	if (packets.empty()) {			//If the queue is empty, we notify the user that the operation cannot be performed
		std::cout << "Cannot get packets because the packets queue is empty! (returning nullptr)" << std::endl;
		return nullptr;
	}
	else {			//This code-block runs only when the queue is non-empty
		std::cout << "Packets will be popped off 1 by 1 and their members will be displayed below (in FIFO manner up to n):" << std::endl;
		int countpopped = 0;		//allows us to keep track of the number of popped elements, so we can pop only upto n
		Packet* packets_to_return = new Packet[n];	//making a dynamic array for later(to return to user)
				
		int Arrindex = 0;
		while ((packets.empty() == false) && (countpopped < n)) {	//This loop runs so long as the queue is not empty, and n packets haven't been popped yet
			Packet currentObj = (this->packets).front();		//We start with the front of the queue to show packets in FIFO manner
			std::cout << "targetID: " << currentObj.get_targetID() << std::endl; //Displaying current targetID
			std::cout << "source ID: " << currentObj.get_sourceID() << std::endl; //Displaying current sourceID
			std::cout << "data:" << currentObj.get_data() << std::endl << std::endl; //Displaying the current data
			
			packets_to_return[Arrindex] = currentObj;
			packets.pop();	//Popping the front-most queue element for each iteration of the loop
			countpopped++;
			Arrindex++;
		}

		return packets_to_return;
	}
}


void NetworkObject::setmaxPackets(unsigned int max) {	//setter for maxPackets
	maxPackets = max;
}


unsigned int NetworkObject::getmaxPackets() {	//getter for maxPackets
	return maxPackets;
}


void NetworkObject::update() {		//this function uses the probability of packet loss to determine whether a packet should be added to the next object. It also handles the travel time of each transmitted packet.


	if (next == nullptr) {  //if next is a null pointer, there is no next node (NetworkObject) so we remove all packets and count the total transmitted through the network

		while (this->packets.size() != 0) {		//looping as long as the current packets queue is non-empty

			int current_time = time(0);		//holding the current system time
			(this->packets).front().set_time_to_travel(current_time - (this->packets).front().get_time_entered());	//calculating travel time
			total_travel_time += (this->packets).front().get_time_to_travel();	//incrementing the total travel time(sum of all travel times)
			std::cout << "The packet entered at " << std::fixed << (this->packets).front().get_time_entered() << " and left at " << time(0) << ", so travel_time = " << (this->packets).front().get_time_to_travel() << std::endl;
			std::cout << "total_travel_time(secs) = " << total_travel_time << std::endl;
			
			this->packets.pop();
			num_transmitted++;	//incrementing the number of transmitted packets once a packet leaves the last node of the network
		}


	}
	else {//We enter here if we know that there exists a next Network Object(so we are not at the end of the list)
		srand(time(0));
		NetworkObject& nextOBJ = *(this->next);		//nextOBJ holds the next object in the linked list
		std::mt19937 random_num_generator(time(0));				//Utilizing the Marsenne Twister number generation technique to generate a random float value from 0 to 1 and assign it to r 
		
		while (this->packets.size() != 0) {			//we loop as long as the current packets queue is non-empty	
			float prob = float(probabilityOfPacketLoss) / 100.0;		//prob holds a scaled down float value of our probability of packet loss(between 0 and 1)
			//using the previously defined random number generator to generate random float numbers from 0 to 1
			std::uniform_real_distribution<float> create(0.0f, 1.0f);
			float r = 0;
			r = create(random_num_generator);

			if (r > prob) {			//if this condition is true, we add the front-most packet to the next object(only if space permits)
				if (nextOBJ.packets.size() < maxPackets) {
					Packet* current_front = &((this->packets).front());		//temporarily holding the frontmost packet in the current packets queue
					//nextOBJ.addPacketobj(current_front);		//will be swapped with addpackets later
				    nextOBJ.addPackets(current_front, 1, false);
	
					(this->packets).pop();						//removing front-most packet from current queue 
				
																
				}
				else {	//if there is no space in the next object, we don't remove anything (as per the specifications of the assignment)
				}
			}
			else {	//we enter here only if r is less than or equal to prob (this is the dropping case)
			   
				this->packets.pop();
				num_dropped++;
			}
		}
	}
}


void NetworkObject::setProb_NODE(int probability) {		//setter for the probability of packet loss of a certain node(NetworkObject)
	probabilityOfPacketLoss = probability;
}

int NetworkObject::getProb_NODE() {					//getter for the probability of packet loss of a certain node(NetworkObject)
	return probabilityOfPacketLoss;
}


int NetworkObject::get_numPackets() {		//returns the size of the packets queue
	return packets.size();
}

void NetworkObject::setnext(NetworkObject* next_one) {
	this->next = next_one;     //setting next
}

NetworkObject* NetworkObject::getnext() {		//getter for next(returns a pointer to the next Network object)
	return this->next;
}