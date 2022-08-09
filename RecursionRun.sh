#!/bin/bash

#ArrangeMentArray=(4 16)
ArrangeMentArray=(4 8 64 512 262144)
#ArrangeMentArray=(4 8 16 64 256 4096)

./TestFilesArrangement.sh 10000 1 1
for i in {2..1001}; do
	./TestFilesArrangement.sh 10000 0 $i
done

mkdir DataDetecting

for i in ${ArrangeMentArray[@]}; do
	cd $i
	rm *.exe
	mv FileArrangeMent.log /home/sec/test/RemoteTestFile_262144/DataDetecting/FileArrangeMent_262144_${i}layer_10000.log
	cd ..
done

tar -cf DataDetecting.tar DataDetecting