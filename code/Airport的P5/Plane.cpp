#include "Plane.hpp"
#include "Random.hpp"
using namespace std;

Plane::Plane() {
    flt_num = -1;
    clock_start = -1;
    state = null;
}

Plane::Plane( int flt, int time, Plane_status cur_state ) {
    flt_num = flt;
    clock_start = time;
    state = cur_state;
    Random random_fuel;
    fuel = (random_fuel.reseed() % 10) + 1;
//以下部分可以优化，属于UI部分；
    cout << "Plane number " << flt << " ready to";
    if ( state == arriving ) {
    	if(fuel <= 1){
    		cout << " land in an EMERGENCY" << endl;
    		state = emergency; 
		}
		else{
			cout << " land." << endl;
		}     
    } else {
        cout << " take off." << endl;
    }
    
}

Plane& Plane::operator=( const Plane& other ) {
    flt_num = other.flt_num;
    clock_start = other.clock_start;
    state = other.state;
    fuel = other.fuel;
    return ( *this );
}

void Plane::refuse() const {
//以下部分可以优化，属于UI部分；
    cout << "Plane number " << flt_num;
    if ( state == arriving ) {
        cout << " directed to another airport" << endl;
    } else {
        cout << " told to try taking off again later" << endl;
    }
}

void Plane::fly( int time ) const {
    int wait = time - clock_start;
    cout << "At time " << time << ": Plane number " << flt_num << " takes off after "
         << wait << " time unit" << ( wait == 1 ? "" : "s" ) << " int the takeoffs queue." << endl;
}


void Plane::land( int time ) const {
	
    int wait = time - clock_start;
    if(wait > fuel){
    	cout << "At time" << clock_start + fuel << ": Plane number " << flt_num << " crashed" << endl;
		return;
	}
	if(state == emergency){
		cout << "At time " << time << ": Plane number " << flt_num << " landed in an emergency" << endl;
		return; 
	}
    cout << "At time " << time << ": Plane number " << flt_num << "  landed after "
         << wait << " time unit" << ( wait == 1 ? "" : "s" ) << " int the landings queue." << endl;
}
Plane_status Plane::get_status() const{
	return state;
}
//用于与runway类沟通达到机场的时间
int Plane::started() const {
    return clock_start;
}
int Plane::get_fuel() const{
	return fuel;
}
bool Plane::crashed(int current_time){
	int wait = current_time - clock_start;
	if(wait > fuel){
		return true;
	}
	return false;
}
