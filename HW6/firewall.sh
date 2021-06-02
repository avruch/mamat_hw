#!/bin/bash

result=""
packet=$(cat)
	while read line
	do
		filterd_list=""
	#create rule that matches expected format
		line=`echo "$line" | tr -d ' ' | sed -e 's/#.*//'`
		if [[ "$line" == "" ]];then
			continue
		fi
		readarray -d , -t rule_array <<<"$line" 
		temp=$packet
		for ((n=0;n<${#rule_array[*]};n++))
			do 
				temp=`echo -e "$temp" |./firewall.exe "${rule_array[n]}"`				
			done

				filterd_list=$(echo "$filterd_list"; echo $'\n'; echo "$temp")
				
				
			result=$(echo "$result"; echo $'\n'; echo "$filterd_list")
	done < "$1"
echo -e "${result}"|sort|sed '/^$/d' | tr -d ' '
