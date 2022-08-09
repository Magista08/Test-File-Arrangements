#!/bin/bash

set -e
set -u

if [ $# -ne 3 ]; then
    echo "USAGE: $0 <need_to_creat_files>"
    exit 1
fi

NEED_TO_CREAT_FILES=$2


#ArrangeMentArray=(4 16)
ArrangeMentArray=(4 8 64 512 262144)
#ArrangeMentArray=(4 8 16 64 256 4096)

FileType=("ext4" "btrfs" "vfat" "ntfs" "exfat")

for fs in ${FileType[@]}; do
	umount /home/sec/test/test2
	mkfs.${fs} /dev/sda2
	mount /home/sec/test/test2/
	
	cd /home/sec/test
	cp RemoteTestFile_262144.tar /home/sec/test/test2
	tar -xf RemoteTestFile_262144.tar
	
	EXIST_FILE=`ls -l | grep TestFilesArrangement.c | wc -l`
	EXIST_TEST=`ls -l | grep test-files-arrangement | wc -l`
	EXIST_CREAT_FILE=`ls -l | grep CreatedFolders.c | wc -l`
	EXIST_CREAT_TEST=`ls -l | grep creat-folders.exe | wc -l`
	EXIST_OUTPUT_FILE=`ls -l | grep FileArrangeMent.log | wc -l`

	# gcc the test file .c
	if [ $EXIST_TEST -eq 0 ]; then
		if [ $EXIST_FILE -eq 0 ]; then
			echo -e "Please transfer the file TestFilesArrangement.c into the folder"
			exit 1
		fi
		gcc TestFilesArrangement.c -O0 -o test-files-arrangement.exe -lm -Wall
	fi

	# create all the folders if needed
	if [ $NEED_TO_CREAT_FILES -eq 1 ]; then
		if [ $EXIST_CREAT_FILE -eq 0 ]; then
			echo -e "Please transder the file CreatedFolders.c if you need to create files"
			exit -1
		fi
		if [ $EXIST_CREAT_TEST -eq 0 ]; then
			gcc CreatedFolders.c -O0 -o creat-folders.exe -lm -Wall
		fi
		for i in ${ArrangeMentArray[@]}; do	
			echo "Begin to build the folder with the number of the files in one layer: $i"
			mkdir $i;
			cp -f creat-folders.exe $i
			cd $i
			./creat-folders.exe $i
			cd ..
			echo "Finished"
		done
	fi

	#report back when making the dirctory is finished

	echo "All folders have been built!"

	#run the test files

	for j in {0..101} do
		for i in ${ArrangeMentArray[@]}; do	
			if [ $EXIST_OUTPUT_FILE -ne 1 ]; then
				touch FileArrangeMent.log
				chmod 777 FileArrangeMent.log
			fi
			echo "Checking the dirctory with the number of files in one layer: $i"
			cp -f test-files-arrangement.exe $i
			cd $i
			./test-files-arrangement.exe $i 10000 $j
			cd ..
		done
	done 

	mkdir DataDetecting
		
	for i in ${ArrangeMentArray[@]}; do
		cd $i
		rm *.exe
		mv FileArrangeMent.log /home/sec/test/test2/DataDetecting/FileArrangeMent_262144_${i}layer_10000.log
		cd ..
	done
		
	cd DataDetecting
	tar -cf DataDetecting_${fs}.tar *
	mv DataDetecting_${fs}.tar /home/sec/test
	cd /home/sec
done
