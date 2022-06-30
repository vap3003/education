#!/bin/bash

NUM_OF_STRING=$(wc -l files.log | cut -d ' ' -f 8)
UNIQ_FILES=$(cat files.log | cut -d ' ' -f 1 | uniq | wc -l | cut -d ' ' -f 8)
UNIQ_SHA=$(cat files.log | cut -d ' ' -f 8 | uniq | wc -l | cut -d ' ' -f 8)
echo ''"$NUM_OF_STRING"' '"$UNIQ_FILES"' '"$UNIQ_SHA"''
