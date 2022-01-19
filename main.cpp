#include <cstdlib>
#include <random>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include "Header.h"


namespace Airport{
  using size_t = std::size_t;
  plane::plane(const size_t time_entered, const char plane_type, const size_t gas_left){
    this -> plane_ID= time_entered;  
    this -> entry_time = *new size_t;
    this -> finish_time = *new size_t;
    this -> type= plane_type;
    this -> gas_finish_time = plane_ID + gas_left;
}
size_t plane::gas_finshing_time() const{
    return gas_finish_time;
}
  airport::airport() : plane(0 , 'N', 0){
    landing=std::priority_queue<plane>();
    departing=std::queue<plane>();
    runway=std::queue<plane>();
  }

void plane::set_enque_time(const size_t enque_time, const size_t runway_duration){
    this -> entry_time = enque_time;
    this -> finish_time = enque_time + runway_duration;
}
  
size_t plane::ftime() const{
    return finish_time;
}
size_t plane::wait_time() const{
    return entry_time - plane_ID;
}
char plane::landing_or_departing() const{
    return type;
}
  
   bool airport::if_plane_departing() const{
    if(!departing.empty()){
      return true;
    }
    else{
      return false;
    }
  }
    bool airport::if_plane_landing() const{
      if(!landing.empty()){
      return true;
    }
    else{
      return false;
    }
  }
  
bool airport::no_runway_error() const{
    if(runway.size()<2){
        return true;
    }
    else{
        return false;
    }
}
  bool airport::if_plane_runway() const{
    if(!runway.empty()){
      return true;
    }
    else{
      return false;
    }
  }
   size_t airport::plane_depart(const size_t time, const size_t runway_duration){
       plane target = departing.front();
       target.set_enque_time(time, runway_duration);
       runway.push(target);
       departing.pop();
       return target.wait_time();
   }
    size_t airport::plane_land(const size_t time, const size_t runway_duration){
      plane target = landing.top();
      target.set_enque_time(time, runway_duration);
      runway.push(target);
      landing.pop();
      return target.wait_time();
}
    void airport::plane_crash(){
        landing.pop();
   }
size_t airport::first_plane_landing() const{
    plane top = landing.top();
    return top.gas_finshing_time();
}
plane airport::plane_in_runway() const{
    return runway.front();
}
void airport::clear_runway(){
    runway.pop();
}
void airport::landing_plane_generator( std::size_t& time, const size_t average_landing_time, const size_t runway_duration, const size_t min_gas, const size_t max_gas){
  double landing_probability= (1/static_cast<double>(average_landing_time))*100;
  double i=rand()%100;
  if(i<landing_probability){
    size_t time_left= rand()%(max_gas - min_gas+1) + min_gas;
    landing.push(plane(time, 'L', time_left));
  }
}
void airport::departing_plane_generator(size_t& time, const size_t average_departing_time, const size_t runway_duration){
  double departing_probability= (1/static_cast<double>(average_departing_time))*100;
  double i=rand()%100;
  if(i<departing_probability){
    departing.push(plane(time , 'D', 0));
  }
}
}
