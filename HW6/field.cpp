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
	//printf("Field GENERIC c'tor'\n");
    	this->pattern=pattern;
    }
    Field::~Field(){
    }
    
    bool Field::match(String packet){
        //printf("Field match'\n");
    	String* sub_strings;
        size_t size=0;
        bool tmp;
        packet.trim().split(",",&sub_strings,&size);
        if (size > PACKET_SIZE){
            //printf("return too many condition'\n");
            //packet.print();
            delete[] sub_strings;
        	return false;//illegal because we have the wrong number of fields in single packet
        }

       
        for(size_t i=0;i<size;i++){
        	String* sub_sub_strings;
        	size_t sub_size=0;
        	(sub_strings[i]).trim().split("=",&sub_sub_strings,&sub_size);
        //printf("Field match sub sub'\n");
            if(pattern.trim().equals(sub_sub_strings[0].trim())){
        //printf("Field match if'\n");
                    tmp= match_value(sub_sub_strings[1].trim());
        //printf("Field match tmp=%d'\n",tmp);
                    delete[] sub_sub_strings;
                    if(!tmp){
                        delete[] sub_strings;
                        //printf("return false'\n");
                        //packet.print();
                        return false;
                    }
                    //printf("condition %d passed\n",i);
                }
            }
            delete[] sub_strings;
            //printf("return true'\n");
            //packet.print();
            return true;
        }



