#include "port.h"


#define PORT_High 65535
#define PORT_Low 0

Port::Port(String pattern):Field(pattern){
}
		Port::~Port(){
		}

    bool Port::set_value(String val){
    	String* sub_strings;
        size_t size=0;
    	val.split("=",&sub_strings,&size);
    	if(size!=2){
			return false;
    	}
    	String* sub_numbers;
    	size_t size_numbers;
    	sub_strings[1].trim().split("-",&sub_numbers,&size_numbers);
    	if(size_numbers!=2){
			return false;
    	}
    	int low=sub_numbers[0].trim().to_integer();
    	int high=sub_numbers[1].trim().to_integer();
    	if((low>high)||low<PORT_Low||high>PORT_High){
            return false;
        }
    	
    	//printf("low value port returned %n \n",&low);
    	//printf("high value port returned %n \n",&high);
    	return true;
    }

    bool Port::match_value(String val) const{
        int value=val.trim().to_integer();
        if( (value>(range[1])) || (value<(range[0])) ){
            return false;
        }
        return true;
    }
