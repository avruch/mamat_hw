 #!/bin/bash 
# first we access the website to gather the relevent players
wget https://www.premierleague.com/players &> /dev/null

grep -o -E '(\/players\/)([0-9])+\/(([a-z]|[A-Z])+-)+([a-z]|[A-Z])+\/overview' players | sort -u > urls.txt

sed -i 's/\/players/https:\/\/www\.premierleague\.com\/players/' urls.txt


 > results.csv
echo Total players: `wc -l urls.txt | sed s/urls.txt// ` > results.csv

while read line 
do
	wget -O temp.txt $line &> /dev/null

	midfielder_count=$(grep -i 'midfielder' temp.txt | wc -l)

	if   [[ "$midfielder_count" != 0 ]]  ; then

	 	 echo "${line}," Midfielder", ${midfielder_count}" >> results.csv
	fi
 
done < urls.txt

#after program is done we remove the unncessary files created along the way
rm players temp.txt urls.txt	
