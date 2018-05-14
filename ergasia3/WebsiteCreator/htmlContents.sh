#!/bin/bash

arrayOfLinks=()


writeContents ()
{
	#get parameters
	fileForAppending=$1
	lines=$2
	p=$3					#pages
	text_file=$4
	
	
	k=$(( ( RANDOM % ($lines-2000) )  + 1 ))		#start reading from file from line k
	m=$(( RANDOM % (2000 - 1000) + 1000 ))
	let f=(p/2)+1			#number of internal links
	
	let q=(w/2)+1			#number of external links
	
	#adding links into array
	source ./links.sh 
	createLinks $fileForAppending $f $q $arrayOfLinks
	
	for item in ${arrayOfLinks[@]}
	do
		echo $item
	done	
	
	
	header="<!DOCTYPE html>
<html>
<body>"
	echo $header >> $fileForAppending			#adding header
	
	#middle part steps 6-7
	startingPoint=$k
	echo $fileForAppending $startingPoint
	let "readNumOfLines=m/($f+$q)"
	let readUpToHere=startingPoint+readNumOfLines
	linkCounter=1
	
	
	while [ "$startingPoint" -le "$lines" ] 		#do this until all lines of text_file have been inserted into fileForAppending
	do
		if [ "$readUpToHere" -gt "$lines" ]; then
			readUpToHere=$lines
		fi
		sed -n "${startingPoint},${readUpToHere}p" $text_file >> $fileForAppending				#get lines from text_file
		#echo "$lines" >> $fileForAppending			#adding lines
	
		
		linkName="#"
	
		linkText="link${linkCounter}_text"
		link="<a href=${linkName}>${linkText}</a>"
	
		echo $link >> $fileForAppending			#adding link
	
		let linkCounter=linkCounter+1
		let startingPoint=(readUpToHere+1)
		let readUpToHere=startingPoint+readNumOfLines
		
		echo "<br>" >> $fileForAppending			#adding new line
		
		
	done
	
	footer="</body>
</html>"
	echo $footer >> $fileForAppending			#adding footer

}
