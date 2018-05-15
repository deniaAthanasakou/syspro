#!/bin/bash

createLinks (){
	fileForAppending=$1
	internalLinks=$2
	externalLinks=$3
	
	let lastElement=${#arrayOfFileNames[@]}-1
	randomPositions=`shuf -i 0-$lastElement`
	for position in $randomPositions ; do		
		if [ "${arrayOfFileNames[$position]}" == "$fileForAppending" ]; then			#ignore same page
			continue
		fi

		pathOfFileForAppending=()
		pathOfOtherPage=()


		IFS=$'/'
		for item in ${arrayOfFileNames[$position]}; do
			pathOfOtherPage+=($item)
		done

		for item in $fileForAppending; do
			pathOfFileForAppending+=($item)
		done

		# reset back to default value
		unset IFS

		#check if link is internal
		if [ "${pathOfFileForAppending[2]}" == "${pathOfOtherPage[2]}" ]; then
			#internal Link
			if [ "$internalLinks" -gt "0" ]; then
				arrayOfLinks+=(${arrayOfFileNames[$position]})	#insert link into array
				let internalLinks=internalLinks-1
			fi	

		
		else
			#external Link
			if [ "$externalLinks" -gt "0" ]; then
				arrayOfLinks+=(${arrayOfFileNames[$position]})	#insert link into array
				let externalLinks=externalLinks-1
			fi	
		fi	
	done	

	if [ "$internalLinks" -gt "0" ]; then
		arrayOfLinks+=($fileForAppending)	#must insert same page
		let internalLinks=internalLinks-1
	fi	

}
