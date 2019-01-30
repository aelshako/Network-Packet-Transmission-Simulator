# Network Packet Transmission Simulator #

## Project Description ##
This C++ project is a Network Packet Transmission Simulator that simulates and randomizes(via Mersenne Twister PRNG technique) packet transmission statistics across a network. 
It can be used to better understand the transfer of packets across a network as well as the packet loss/transmission rate and speed.
The FIFO queue data structure is used to make the project more realistic. 


## Motivation(and my other related projects) ##
This project presents an interesting model of basic packet transmission for a high number of randomized packets. With a more realistic(complex) network, we would have to first identify ideal paths(no loops).
To address this, we can model our network as a special multi(prev, next) link linked list. We would then run a more complex reduction/routing algorithm such as Dijkstra's routing algorithm
to promote efficiency and prevent loops within the network.

## NOTE: As a separate project, I've fully implemented Dijkstra's routing algorithm twice(in Java and C) while adhering to good design principles in both programs. ##
  
  if interested, please visit the following repos: 
 
 [Click for my Dijkstra C implementation](https://github.com/aelshako/Dijkstra-Routing-Algorithm-C-)
 
 
 [Click for my Dijkstra Java implementation](https://github.com/aelshako/Dijkstra-Routing-Algorithm-Java-)
         
         
 
  
