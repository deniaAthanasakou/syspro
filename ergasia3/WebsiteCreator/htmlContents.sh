#!/bin/bash

writeContents ()
{
	fileName=$1
	lines=$2
	k=$(( ( RANDOM % ($lines-2000) )  + 1 ))
	echo k $k
	m=$(( ( RANDOM % 2000 )  + 1000 ))
	m=$(( RANDOM % (2000 - 1000) + 1000 ))
	echo m $m
	header="<!DOCTYPE html>
<html>
<body>
word1 word2 … <a href=”link1”>link1_text</a>
wordn wordn+1 … <a href=”link2”>link2_text</a> wordm wordm+1 ...
</body>
</html>"
	echo $header >> $fileName
}
