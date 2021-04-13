 #!/bin/bash 

read input

number=$(echo -n $input | wc -c )
if   [[ $number != 6 ]] ; then 
 	echo "Wrong number of arguments" #&2
 	#break	
else 
	if [[ $(grep $input".txt" . &> /dev/null ) == 0 ]]; then 
		echo "Course not found" #&2
	#break
	fi
	#remove the directory if exists
	#$ find . -type d -name $input"_stat" -exec rm
		rm -rf $input"_stat" #&> /dev/null
		mkdir $input"_stat" 
 		awk '{if (NR!=1) {print $2}}' $input".txt" > ./$input"_stat"/grades.txt 

fi
