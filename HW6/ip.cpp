#include "ip.h"


#define MASK_SEGMENT 2
#define SEGMENTS 4


    Ip::Ip(String pattern):Field(pattern){	
    }
    Ip::~Ip(){
    
    }
    
    bool Ip::set_value(String val){
    	String* sub_strings;
        size_t size=0;
    	val.split("/",&sub_strings,&size);
    	if(size!=2){
            delete[] sub_strings;
			return false;
    	}
    	int num_bits_rule=sub_strings[1].trim().to_integer();
    	int IP_mask=sub_strings[0].trim().to_integer();
    	if(num_bits_rule==0){
    		low=0;
    		high=0xFFFFFFFF;
            delete[] sub_strings;
    		return true;
    		}
    	int mask=1<<num_bits_rule;
    	mask--;
    	low=(IP_mask)&(~mask);
    	high=(IP_mask)|mask;
        delete[] sub_strings;
    	return true;
    	}

    bool Ip::match_value(String val) const{
    	unsigned int value=val.to_integer();
    	if ((value<low)||(value>high)){
    		return false;
    	}
    	return true;
    }




