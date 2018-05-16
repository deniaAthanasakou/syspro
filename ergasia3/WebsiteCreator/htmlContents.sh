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
	#echo m $m
	let f=(p/2)+1			#number of internal links
	
	let q=(w/2)+1			#number of external links
	
	#echo "we are in file $fileForAppending" internal $f external $q

	#adding links into array
	source ./links.sh 
	createLinks $fileForAppending $f $q
	
	#for item in ${arrayOfLinks[@]} ; do
	#	echo link is $item
	#done	



	let lastElement=${#arrayOfLinks[@]}-1
	randomPositions=`shuf -i 0-$lastElement`
	#echo $randomPositions


	IFS=$'\n'
	randomLinkArray=()
	for position in ${randomPositions[@]}
	do
		randomLinkArray+=(${arrayOfLinks[$position]})
	done
	unset IFS	

	#for myLink in ${randomLinkArray[@]}
	#do
	#	echo myLink $myLink
	#done



	header="<!DOCTYPE html>
<html>
<body>"
	echo $header >> $fileForAppending			#adding header
	
	#middle part steps 6-7
	startingPoint=$k
	#echo $fileForAppending $startingPoint
	let "readNumOfLines=m/($f+$q)"
	let readUpToHere=startingPoint+readNumOfLines
	linkCounter=1
	echo "#   Creating page $fileForAppending with $m lines starting at line $k"
	while [ "$startingPoint" -le "$lines" ] 		#do this until all lines of text_file have been inserted into fileForAppending
	do
		
		if [ "${#randomLinkArray[@]}" -eq "0" ]; then
			break

		fi	
		
		if [ "$readUpToHere" -gt "$lines" ]; then
			readUpToHere=$lines
		fi
		sed -n "${startingPoint},${readUpToHere}p" $text_file >> $fileForAppending				#get lines from text_file and add them to html	
			
		linkText="link${linkCounter}_text"
		link="<a href="${randomLinkArray[0]}">$linkText</a>"
		
	
		echo "#     Adding link to ${randomLinkArray[0]}"
		echo $link >> $fileForAppending			#adding link
	
		let linkCounter=linkCounter+1

		unset randomLinkArray[0]              ## remove element
		randomLinkArray=( "${randomLinkArray[@]}" )     ## pack array
		
		let startingPoint=(readUpToHere+1)
		let readUpToHere=startingPoint+readNumOfLines
		
		echo "<br>" >> $fileForAppending			#adding new line
		
		
	done	
	footer="</body>
</html>"
	echo $footer >> $fileForAppending			#adding footer
}
