#!/bin/bash

#checking input
numOfParameters=$#
if [ "$numOfParameters" -ne 4 ]; then			#check for number of parameters
	echo "Error! Wrong number of parameters."
	exit
fi	

root_directory=$1
text_file=$2
w=$3
p=$4
echo $root_directory $text_file $w $p 

if [ ! -d "$root_directory" ]; then		#directory does not exist
	echo "Error! Directory '$root_directory' does not exist."
	exit
fi

if [ ! -f "$text_file" ]; then			#file does not exist
    echo "Error! File '$text_file' does not exist."
    exit
fi

numOfLines=$(wc -l < $text_file)	
if [ "$numOfLines" -lt 10000 ]; then	#checking that file is not too small
	echo "Error! File '$text_file' should have at least 10000 lines."
	exit
fi

if ! [ "$w" -eq "$w" ] 2>/dev/null; then	#is not integer
	echo "Error! Incorrect type of argument 3."
	exit
fi

if ! [ "$p" -eq "$p" ] 2>/dev/null; then	#is not integer
	echo "Error! Incorrect type of argument 4."
	exit
fi


rm -rf ./$root_directory/*					#delete existing directories
#create w folders for sites inside root_directory
for ((i=0; i < w; i++))
do
	mkdir ./$root_directory/site$i		#create new ones
	for ((j=0; j < p; j++))
	do
		randomNum=$RANDOM
		while [ -e ./$root_directory/site$i/page$i\_$randomNum.html ]
		do
			randomNum=$RANDOM
		done
		fileName=./$root_directory/site$i/page$i\_$randomNum.html
		touch $fileName		#create file
		#get contents of file
		source ./htmlContents.sh 
		writeContents $fileName $numOfLines $p $text_file
		
		
		
		
	done
done	

: <<'END'		
block comments
END

