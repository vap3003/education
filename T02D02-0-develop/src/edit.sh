#!/bin/bash

WORKDIR=$1
if [[ -f "$WORKDIR" ]]; then
	TO_REPLACE=$2 
	NEW_STRING=$3
	if [[ -n "$TO_REPLACE" ]]; then
		if [[ "$(grep $TO_REPLACE $WORKDIR)" ]]; then
			sed -i " " "s/$TO_REPLACE/$NEW_STRING/" $WORKDIR
			SHA=$(shasum -a 256 $WORKDIR | cut -d ' ' -f 1)
			DATA=$(date "+%Y-%m-%d %H:%M")
			SIZE=$(wc -c $WORKDIR | cut -d ' ' -f 5)
			echo ''"$WORKDIR"' - '"$SIZE"' - '"$DATA"' - '"$SHA"' - sha256' >> files.log
		else
			echo ''"$TO_REPLACE"' is not in file'
		fi  
	else
		echo "Empty string"
	fi
else
  echo "No such file or directory"
fi

