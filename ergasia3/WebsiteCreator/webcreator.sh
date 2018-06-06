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

arrayOfFileNames=()							#will be used for links

#check if root_directory is empty
if [ "$(ls -A $root_directory)" ]; then
   echo "# Warning: directory is full, purging..."
   rm -rf $root_directory/*					#delete existing directories
fi


#create w folders for sites inside root_directory
for ((i=0; i < w; i++)); do		#pages will be inserted into arrayOfFileNames
	echo "# Creating web site $i"
	mkdir $root_directory/site$i		#create new ones
	for ((j=0; j < p; j++)); do
		
		randomNum=$RANDOM
			
		while [ true ]; do
			flag=0
			tempPage="$root_directory/site$i/page$i\_$randomNum.html"
			for page in ${arrayOfFileNames[@]}			#check if fileName exists in array
			do
				if [ "$page" == "$tempPage" ]; then
					flag=1
					break
				fi
			done
			if [ "$flag" -eq "0" ]; then
				break
			fi
			randomNum=$RANDOM
		done
		fileName=$root_directory/site$i/page$i\_$randomNum.html
		arrayOfFileNames+=($fileName)
		
	done
done

arrayOfIncomingLinks=("${arrayOfFileNames[@]}")   	

for page in ${arrayOfFileNames[@]}			
do
	touch $page		#create file
	#get contents of file
	source ./htmlContents.sh 
	writeContents $page $numOfLines $p $text_file 
	
done	

flagForIncoming=1		#all pages have at least one incoming link
for item in ${arrayOfIncomingLinks[@]}; do
	if [ "$item" != "true" ]; then
		flagForIncoming=0
		break
	fi	
done

if [ "$flagForIncoming" -eq "1" ]; then
	echo "# All pages have at least one incoming link"
else
	echo "# Not all pages have at least one incoming link"	
fi	

echo "# Done"
