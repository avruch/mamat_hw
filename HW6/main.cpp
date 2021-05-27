#include "ip.h"
#include "port.h"
#include "input.h"
#include "string.h"
#include <cstring>
#include <stdbool.h>


int main(int argc, char **argv){

	if(check_args(argc,argv)){
		printf("check args init\n");
	 	return 1;
	}

	//printf("argv[1]= %s\n",argv[1]);
	String rule=String(argv[1]);
	String* sub_strings;
	size_t size=0;
	rule.trim().split("=",&sub_strings,&size);
	//printf("size=%ld\n",size);
	//printf("sub_strings [0],[1] \n");
	//sub_strings[0].print();
	//sub_strings[1].print();

	bool one=(sub_strings[0].trim().equals(String("src-ip")));
	bool two = (sub_strings[0].trim().equals(String("dst-ip")));
	bool three = (sub_strings[0].trim().equals(String("src-port")));
	bool four = (sub_strings[0].trim().equals(String("dst-port")));
	//printf("one=%d,two=%d,three=%d,four=%d\n",one,two,three,four);
	Field* field;
	if((one)||(two)){
		//	printf("ip chosen\n");
		field = new Ip(sub_strings[0].trim());
		field->set_value(sub_strings[1].trim());
			//printf("after set value\n");
		parse_input( *field);
			//printf("after parse-input\n");
	}
	if(three||four){
		//	printf("port chosen\n");
		field = new Port(sub_strings[0].trim());
		field->set_value(sub_strings[1].trim());
		parse_input( *field);
	}
	delete field;
	delete [] sub_strings;
	return 0;
}
