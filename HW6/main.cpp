#include "ip.h"
#include "port.h"
#include "input.h"
#include "string.h"
#include <cstring>
#include <stdbool.h>


int main(int argc, char **argv){
	if(check_args(argc,argv)){
	 	return 1;
	}
	String rule=String(argv[1]);
	String* sub_strings;
	size_t size=0;
	rule.trim().split("=",&sub_strings,&size);
	bool one=(sub_strings[0].trim().equals(String("src-ip")));
	bool two = (sub_strings[0].trim().equals(String("dst-ip")));
	bool three = (sub_strings[0].trim().equals(String("src-port")));
	bool four = (sub_strings[0].trim().equals(String("dst-port")));
	Field* field;
	if((one)||(two)){
		field = new Ip(sub_strings[0].trim());
		field->set_value(sub_strings[1].trim());
		parse_input( *field);	
		delete field;
	}
	if(three||four){
		field = new Port(sub_strings[0].trim());
		field->set_value(sub_strings[1].trim());
		parse_input( *field);
		delete field;
	}
	delete [] sub_strings;
	return 0;
}
