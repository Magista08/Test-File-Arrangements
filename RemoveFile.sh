#!/bin/bash

for i in {0..4}; do
	cd $i/
	for j in {0..4}; do 
		cd $j/
			for k in {0..4}; do
				cd $k/
				for l in {0..4}; do
					cd $l/
					for m in {0..4}; do
						cd $m/
						for n in {0..4}; do
							rm -rf $n
						done
						cd ..
					done
					cd ..
				done
				cd ..
			done
		cd ..
	done
	cd ..
done
