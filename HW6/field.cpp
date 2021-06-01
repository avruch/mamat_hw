#include "ip.h"
#include "port.h"
#include "field.h"
#define PACKET_SIZE 4
#define EXPECTED_SIZE_FIELD 2
#define EXPECTED_SIZE_NAME 2
#define SRC_IP "src-ip"
#define DST_IP "dst-ip"
#define SRC_PORT "src-port"
#define DST_PORT "dst-port"

    Field::Field(String pattern){
    	this->pattern=pattern;
    }
    Field::~Field(){
    }
    
    bool Field::match(String packet){
        
            if(packet.trim().equals(String(""))){
            return false;  
        }
    	String* sub_strings;
        size_t size=0;
        bool tmp;
        packet.trim().split(",",&sub_strings,&size);
        if (size > PACKET_SIZE){
            delete[] sub_strings;
        	return false;//illegal because we have the wrong number of fields in single packet
        }

       
        for(size_t i=0;i<size;i++){
        	String* sub_sub_strings;
        	size_t sub_size=0;
        	(sub_strings[i]).trim().split("=",&sub_sub_strings,&sub_size);
            if(pattern.trim().equals(sub_sub_strings[0].trim())){
                    tmp= this->match_value(sub_sub_strings[1].trim());
                    delete[] sub_sub_strings;    
                    if(!tmp){
                        delete[] sub_strings;
                        return false;
                    }
                }
            }
            delete[] sub_strings;
            return true;
        }





