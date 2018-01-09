#include <iostream>
#include "Runway.hpp"
#include "Plane.hpp"
using namespace std;


Runway::Runway( int limit ) {
    queue_limit = limit;
    num_land_requests = 0;
    num_takeoff_requests = 0;
    num_land_finished = 0;
    num_takeoff_finished = 0;
    num_land_accepted = 0;
    num_takeoff_accepted = 0;
    num_land_refused = 0;
    num_takeoff_refused = 0;
    num_emergency = 0;
    num_crashed = 0;
    land_wait_total = 0;
    takeoff_wait_total = 0;
    idle_time_total = 0;
    
};

Error_code Runway::can_land( const Plane &current ) {
    Error_code result;
    if ( landings.size() < queue_limit ) {
        result = success;
        landings.push( current );
    }
	else {
        result = fail;
    }
    num_land_requests++;
    if ( result == success ) {
        num_land_accepted++;
    } else {
        num_land_refused++;
    }
    return result;
};

Error_code Runway::can_depart( const Plane &current ) {
    Error_code result;
    if ( takeoffs.size() < queue_limit ) {
        result = success;
        takeoffs.push( current );
    } else {
        result = fail;
    }
    num_takeoff_requests++;
    if ( result == success ) {
        num_takeoff_accepted++;
    } else {
        num_takeoff_refused++;
    }
    return result;
};

Runway_activity Runway::activity( int time, Plane &moving ) {
    Runway_activity cur_state;
    if( moving.get_status() == emergency ){
    	cur_state = emergency_land;
    	num_land_finished++;
		num_emergency++;
		return emergency_land; 
	}
    if ( !landings.empty() ) {
        cur_state = land;
        moving = landings.front();
        landings.pop();
        if(moving.crashed(time)){
        	num_crashed++;
        	land_wait_total += moving.get_fuel();
		}else{
			num_land_finished++;
			land_wait_total += time - moving.started();
		}         
    } else if ( !takeoffs.empty() ) {
        cur_state = takeoff;
        moving = takeoffs.front();
        takeoffs.pop();
        num_takeoff_finished++;
        takeoff_wait_total += time - moving.started();
    } else {
        cur_state = idle;
        idle_time_total++;
    }
    return cur_state;
}
double Runway::busy(int current_time)const{
	return ( double )idle_time_total / ( double )current_time;
}
void Runway::shut_down( int time ) const {
//（这里可以优化UI）-----可以考虑把输出导入到Exel表格
    cout << "Simulation has concluded after " << time << " time units." << endl
         << "Total number of planes processed during the Simulation: "
         << num_takeoff_requests + num_land_requests << "." << endl;
    cout << "Total number of planes asking to land: " << num_land_requests << endl;
    cout << "Total number of planes asking to takeoff: " << num_takeoff_requests << endl;
    cout << "Total number of planes refused to land: " << num_land_refused << endl;
    cout << "Total number of planes refused to takeoff: " << num_takeoff_refused << endl;
    cout << "Total number of planes accepted to land: " << num_land_accepted << endl;
    cout << "Total number of planes accepted to takeoff: " << num_takeoff_accepted << endl;
    cout << "Total number of planes landed successfully: " << num_land_finished << endl;
    cout << "Total number of planes takeoff successfully: " << num_takeoff_finished << endl;
    cout << "Total number of planes crashed: " << num_crashed << endl;
	cout << "Total number of emergencies: " << num_emergency << endl;  
    cout << "Total time all the planes wait( for landing ): " << land_wait_total << endl;
    cout << "Total time all the planes wait( for taking off ): " << takeoff_wait_total << endl;
    cout << "Average time that every planes wait( for landing ): "
         << ( double )land_wait_total / ( double )num_land_finished << endl;
    cout << "Average time that every planes wait( for taking off ): "
         << ( double )takeoff_wait_total / ( double )num_takeoff_finished << endl;
    cout << "Total time the Runway idle: " << idle_time_total << endl;
    cout << "Persentage of time Runway idle: " << ( double )idle_time_total / ( double )time << endl;
    cout << "Average rate of plane wanting to land: " << ( double )num_land_requests / ( double )time << endl;
    cout << "Average rate of plane wanting to takeoff: " << ( double )num_takeoff_requests / ( double )time << endl;
};
