#!/bin/bash

createLinks (){
	fileForAppending=$1
	internalLinks=$2
	externalLinks=$3

	IFS=$'/'
	pathOfFileForAppending=()
	for item in $fileForAppending; do
		pathOfFileForAppending+=($item)
	done
	unset IFS			# reset back to default value
	
	let lastElement=${#arrayOfFileNames[@]}-1
	randomPositions=`shuf -i 0-$lastElement`
	for position in $randomPositions ; do		
		if [ "${arrayOfFileNames[$position]}" == "$fileForAppending" ]; then			#ignore same page
			continue
		fi

		pathOfOtherPage=()


		IFS=$'/'
		for item in ${arrayOfFileNames[$position]}; do
			pathOfOtherPage+=($item)
		done

		# reset back to default value
		unset IFS

		#check if link is internal
		let posOfSiteX=${#pathOfOtherPage[@]}-2

		if [ "${pathOfFileForAppending[$posOfSiteX]}" == "${pathOfOtherPage[$posOfSiteX]}" ]; then		#siteX
			#internal Link
			if [ "$internalLinks" -gt "0" ]; then
				for ((incCounter=0; incCounter < ${#arrayOfIncomingLinks[@]}; incCounter++)); do
					if [ "${arrayOfFileNames[$position]}" == "${arrayOfIncomingLinks[$incCounter]}" ]; then
						arrayOfIncomingLinks[$incCounter]=true
					fi	
				done


				#linkToBeInserted="./${pathOfOtherPage[5]}"
				arrayOfLinks+=(${arrayOfFileNames[$position]})	#insert link into array


				let internalLinks=internalLinks-1
			fi	

		
		else
			#external Link
			if [ "$externalLinks" -gt "0" ]; then
				#linkToBeInserted="../${pathOfOtherPage[4]}/${pathOfOtherPage[5]}"
				arrayOfLinks+=(${arrayOfFileNames[$position]})	#insert link into array
				let externalLinks=externalLinks-1
			fi	
		fi	
	done	

	if [ "$internalLinks" -gt "0" ]; then
		#linkToBeInserted="./${pathOfFileForAppending[5]}"
		arrayOfLinks+=($fileForAppending)	#must insert same page
		let internalLinks=internalLinks-1
	fi	

}
