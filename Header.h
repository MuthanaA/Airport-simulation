#include <queue>

#ifndef AIRPORT_H
#define AIRPORT_H


using size_t= std::size_t;
namespace Airport{
class plane{
  public:
    plane(const size_t time_entered, const char lane_type, const size_t gas_left);
    //initializes a plane and sets some of it's private variables()
    void set_enque_time(size_t enque_time,  size_t runway_duration);
    //sets the final two member variables of a plane (finishing_time and entry_time)
    size_t ftime() const;
    //return the time that the plane in the runway will finish using it
    size_t wait_time() const;
    //returns the waiting time that a plane spent either in the landing or departing queue
    size_t gas_finshing_time() const;
    //returns the time a plane in the landing queue will run out of gas and crash
    char landing_or_departing() const;
    //returns the type of the plane, landing or departing 
  private:
    size_t plane_ID;
    //plane_ID is the time a plane has entered either the landing or departing queues
    size_t entry_time;
    //entry_time is the time that either a plane departing or landing has been authorized to enter the runway
    size_t finish_time;
    //finish_time is the time that a plane will finish using the runway
    char type;
    //bool type, D if departing, L if landing
    size_t gas_finish_time;
    //gas_finishing_time is used to find the time left for a plane in the landing queue before it runs out of gas and crashes
};

  class airport: public plane{
    public:
      airport();
      void insert_plane(const size_t &time_entered, const char type);
      //inserts a plane into either the landing or departing queues
      bool if_plane_departing() const;
      //postcondition: checks if there is a plane in the departing queue
      bool if_plane_landing() const;
      //postcondition: checks if there is a plane in the landing queue
      bool if_plane_runway() const;
      //postcondition: checks if there is a plane in the runway
      bool no_runway_error() const;
      //checks that there is no more than one plane in the runway at time
      size_t plane_depart( size_t time,  size_t runway_duration);
      //postconditions: next plane in the departing queue will use the runway, and returns the wait time spent in the departing queue
      size_t plane_land( size_t time,  size_t runway_duration);
      //postconditions: next plane in the landing queue will use the runway, and returns the wait time spent in the landing queue
      void plane_crash();
      //postcondition: if a plane crashes it will be removed from the landing queue.
      void clear_runway();
      //postconditions, clears the runway when a plane finishes using it.
      size_t first_plane_landing() const;
      //returns the finishing time for the first plane in the landing queue
      plane plane_in_runway() const;
      //returns a copy of the plane in the runway
      void landing_plane_generator( std::size_t& time, const size_t average_landing_time, const size_t runway_duration, const size_t min_gas, const size_t max_gas);
      //Postconditions: this functions inserts randomly inserts a plane to the landing queue with a specified probability of inserting it that is based on the aaverage time between each landing, also it will have some random gas finishing time within the range of min_gas and max_gas
      void departing_plane_generator( size_t& time, const size_t average_departing_time, const size_t runway_duration);
        //Postconditions: this functions inserts randomly inserts a plane to the landing queue with a specified probability of inserting it that is based on the aaverage time between each take off
    private:
      std::priority_queue<plane> landing;
      std::queue<plane> departing;
      std::queue<plane> runway;
};
inline bool operator< (plane const &a, plane const &b) {
    return a.gas_finshing_time()> b.gas_finshing_time();
}
inline bool operator> (plane const &a, plane const &b) {
    return a.gas_finshing_time()> b.gas_finshing_time();
  }
}
#endif





