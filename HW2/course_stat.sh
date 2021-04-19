 #!/bin/bash 

read input

number=$(echo -n $input | wc -c )
if   [[ $number != 6 ]] ; then 
 	echo "Wrong number of arguments" >&2
 	
elif [[ !(-f $input".txt") ]];then
		echo "Course not found" >&2
	else 
		#remove the directory if exists 
		rm -rf $input"_stat" #&> /dev/null
		mkdir $input"_stat" 
 		awk '{if (NR!=1) {print $2}}' $input".txt"> ./$input"_stat"/grades.txt 
 		gcc -g -Wall calc_statistics.c -o prog.exe
 		./prog.exe "./$input"_stat"/grades.txt" > ./$input"_stat"/course_statistics.txt 2> /dev/null
 fi



#&> /dev/null