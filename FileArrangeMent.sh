#!/bin/bash

set -e
set -u

if [ $# -ne 2 ]; then
    echo "USAGE: $0 <times_to_check_files> <need_to_creat_files>"
    exit 1
fi

TIME_TO_CHECK_FIELS=$1
NEED_TO_CREAT_FILES=$2

#ArrangeMentArray=(4 16)
#ArrangeMentArray=(4 8 64 512)
ArrangeMentArray=(4 8 16 64 256 4096)


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
	gcc TestFilesArrangement.c -o test-files-arrangement.exe -lm -Wall
fi

# create all the folders if needed
if [ $NEED_TO_CREAT_FILES -eq 1 ]; then
	if [ $EXIST_CREAT_FILE -eq 0 ]; then
		echo -e "Please transder the file CreatedFolders.c if you need to create files"
		exit -1
	fi
	if [ $EXIST_CREAT_TEST -eq 0 ]; then
		gcc CreatedFolders.c -o creat-folders.exe -lm -Wall
	fi
	for i in ${ArrangeMentArray[@]}
	do	
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
for i in ${ArrangeMentArray[@]}
do	
	if [ $EXIST_OUTPUT_FILE -ne 1 ]; then
		touch FileArrangeMent.log
		chmod 777 FileArrangeMent.log
	fi
	echo "Checking the dirctory with the number of files in one layer: $i"
	cp -f test-files-arrangement.exe $i
	cd $i
	./test-files-arrangement.exe $i $TIME_TO_CHECK_FIELS
	cd ..
done
