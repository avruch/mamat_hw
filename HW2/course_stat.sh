 #!/bin/bash 
number=$(echo -n $1 | wc -c )
if   [[ $number != 6 ]] ; then 
 	echo "Wrong number of arguments" >&2
 	
elif [[ !(-f $1".txt") ]];then
		echo "Course not found" >&2
	else 
		#remove the directory if exists 
		rm -rf $1"_stat" 
		mkdir $1"_stat" 
 		awk '{if (NR!=1) {print $2}}' $1".txt"> ./$1"_stat"/grades.txt 
 		gcc -g -Wall calc_statistics.c -o prog.exe
 		./prog.exe "./$1"_stat"/grades.txt" > ./$1"_stat"/course_statistics.txt 
 fi
