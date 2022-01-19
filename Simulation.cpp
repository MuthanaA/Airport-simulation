//  Simulation.cpp
//  Airport
//  Created by Muthana Alhadrab

#include "Header.h"

#include <iostream>
#include <cassert>
using namespace Airport;




int main(){
  srand(time(0));
  size_t landing_duration, take_off_duration, average_landing_time, average_take_off_time, min_gas, max_gas, simulation_duration;
  
  std::cout<<"I need your inputs to make the simulation first"<<std::endl;
  
  std::cout<<"What's The amount of time needed for one plane to land? (minutes)"<<std::endl;
  std::cin>>landing_duration;
  
  std::cout<<"What's The amount of time needed for one plane to take off? (minutes)"<<std::endl;
  std::cin>>take_off_duration;
  
  std::cout<<"What's The average amount of time between arrival of planes to the landing queue? (minutes)"<<std::endl;
  std::cin>>average_landing_time;
    
  std::cout<<"What's The average amount of time between arrival of planes to the takeoff queue? (minutes)"<<std::endl;
  std::cin>>average_take_off_time;
  
  std::cout<<"What's The maximum amount of time that a plane landing can have before it runs out of fuel and crashes? (minutes)"<<std::endl;
  std::cin>>max_gas;
  
  std::cout<<"What's The minimum amount of time that a plane landing can have before it runs out of fuel and crashes? (minutes)"<<std::endl;
  std::cin>>min_gas;
    
  std::cout<<"What's The total length of time to be simulated? (minutes)"<<std::endl;
  std::cin>>simulation_duration;
    
  airport airport;
  size_t clock;
  size_t landing_wait_time=0;
  size_t departing_wait_time=0;
  size_t crashed_planes=0;
  size_t planes_landed = 0, planes_departed = 0;
  for(clock=0 ; clock<simulation_duration ; ++clock){ //this is the time variable
    assert(airport.no_runway_error()); //no more than one plane  on the runway
    airport.landing_plane_generator(clock, average_landing_time, landing_duration, min_gas, max_gas);
    airport.departing_plane_generator(clock, average_take_off_time, take_off_duration);
    if(airport.if_plane_landing() && !airport.if_plane_runway()){//if there is a plane in the landing queue and none in the runway
      while(clock> airport.first_plane_landing()){// checks if the plane has crashed
        airport.plane_crash();
        crashed_planes++;
      }
    if (clock <= airport.first_plane_landing()){ //if not it will land normally
      landing_wait_time += airport.plane_land(clock , landing_duration);
      }
    } 
    else if(airport.if_plane_departing() && !airport.if_plane_runway() && !airport.if_plane_landing()){//if there is a plane in the departing queue and none in the runway{
      departing_wait_time += airport.plane_depart(clock , take_off_duration);
    }
    plane runway = airport.plane_in_runway();
    if(runway.ftime()==clock && runway.landing_or_departing() == 'L'){ //removes a plane from the runway once it finishes landing
      airport.clear_runway();
      planes_landed++;
    }
    else if(runway.ftime()==clock && runway.landing_or_departing() == 'D'){ //removes a plane from the runway once it finishes departing
      airport.clear_runway();
      planes_departed++;
    }

  }
  double average_waiting_time_landing=  static_cast<double>(landing_wait_time)/static_cast<double>(planes_landed);
  double average_waiting_time_departing=  static_cast<double>(departing_wait_time)/static_cast<double>(planes_departed);
    
  
  std::cout<<"Here are the outputs of the simulation: "<<std::endl;
  std::cout<<"The number of planes that took off in the simulated time: "<<planes_departed<<std::endl;
  std::cout<<"The number of planes that landed in the simulated time: "<<planes_landed<<std::endl;
  std::cout<<"The number of planes that crashed because they ran out of fuel before they could land: "<<crashed_planes<<std::endl;
  std::cout<<"The average time that a plane spent in the takeoff queue: "<<average_waiting_time_departing<<" Minutes"<<std::endl;
  std::cout<<"The average time that a plane spent in the landing queue: "<< average_waiting_time_landing <<" minutes"<<std::endl;
  
}
