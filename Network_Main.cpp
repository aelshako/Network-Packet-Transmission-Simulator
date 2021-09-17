// Network_Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "NetworkObject.h"
#include "Packet.h"
#include <cstdlib>
#include <ctime>


int main(){

	srand(time(0));

	int num_cycles = 100;		//Looping over everything a large number of times(I chose 100) and displaying averages at end
	int total_packets = 0;
	int total_nodes = 0;
	int count = 0;

	//Note: my code may take a minute or two to finish executing since I am running a large number of iterations
	for (int i = 0; i < num_cycles; i++) {  //****(EXTRA CREDIT)**** We will loop a large number of times over the operations

		int num_objects = rand() % 3 + 2;	//capping at 3 because we don't want the program to take too long to execute, we add two so we don't have a single node network, or a zero-node network(would cause problems w/ array access)
		NetworkObject* arr_objects = new NetworkObject[num_objects];	//arr_objects points to an array of NetworkObjects of size num_objects
		

		int maxPacks = rand() + 5000;			//This will be used to set out maxPackets for each node; I am adding 5000 to ensure that its not too low, so a sufficient number of packets are able to travel through the network
		int num_packets = rand() % 300 + 1000;	//creating a random variable to hold number of packets to add to first object (I'm adding 1000 to make it fairly large)
		if (num_packets > maxPacks) {	//capping the number of packets that we create if it exceeds maxPackets(because there is no reason to create packets that we won't use)
			num_packets = maxPacks;
		}

		total_nodes += num_objects;		//incrementing the number of total nodes(used to compute avg later)
		total_packets += num_packets;	//incrementing the total number of packets(used to compute avg later)
		Packet* arr_packets = new Packet[num_packets];	//arr_packets is an array of packets of size num_packets

		for (int i = 0; i < num_objects; i++) {		//creating/initializing objects
			arr_objects[i] = NetworkObject(rand());		//filling arr_objects with random objectID NetworkObjects
			arr_objects[i].setProb_NODE(rand()% 100 + 1);	//setting a random probability
			arr_objects[i].setmaxPackets(maxPacks);			//setting maxPackets
		}

		for (int i = 0; i < num_objects - 1; i++) {		//setting next for all but last element(b/c the next variable is a nullptr by default)
			arr_objects[i].setnext(&arr_objects[i + 1]);
		}
			
		for (int i = 0; i < num_packets; i++) {		//creating packets with random size(num_packets)
			arr_packets[i] = Packet();
		}
		arr_objects[0].addPackets(arr_packets, num_packets, true);	//adding created packets to first NetworkObject, the true signifies that we are adding to the first node(allows for setting the time each packet entered the network)
		
		
		for (int i = 0; i < num_objects; i++) {	//calling update on all elements in the network
			arr_objects[i].update();
		}


				delete[] arr_objects;	// Freeing up the memory for arr_objects since its no longer needed
				delete[] arr_packets;	// Freeing up the memory for arr_packets since its no longer needed
			
		//resetting the randomized variables in the loop
				num_packets = 0;		
				num_objects = 0;
				maxPacks = 0;
	}
	
	    std::cout << "\n" <<"Number of cycles: " << num_cycles << std::endl;
		std::cout << "Average Number of nodes :" << double(total_nodes)/num_cycles << std::endl << std::endl;

		std::cout << "Total number of packets created: " << total_packets << std::endl;
		std::cout << "Total Number of packets transmitted: " << NetworkObject::num_transmitted << std::endl;
		std::cout << "Average number packets transmitted: " << double(NetworkObject::num_transmitted)/double(num_cycles) << std::endl << std::endl;
		
		
		std::cout << "Number of Packets dropped: " << NetworkObject::num_dropped << std::endl;	
		std::cout << "Average Percentage of packets lost: " << (double)((((double)NetworkObject::num_dropped) / (total_packets)) * 100.0 )<<  "%" <<std::endl << std::endl;


		if (NetworkObject::num_transmitted == 0) {	
			std::cout << "Average packet travel time: " << "Cannot be computed(no packets reached end of network!)" << std::endl;
		}
		else {
			std::cout << "Average packet travel time(secs): " << double(NetworkObject::total_travel_time) / (NetworkObject::num_transmitted) << std::endl;
		}
	

	
}

