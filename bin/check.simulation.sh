#!/bin/bash

dir=`pwd`/disk19/mouse

for id in `seq 1 10`
do
	cur=$dir/$id

	base=$cur/baseline.0.20.10.ppt0
	cnf=$cur/cnf.0.35.10.ppt0

	b0=`cat $base | grep summary | grep label0 | cut -f 4,6,8,16,19 -d " " | sed 's/,//g'`
	b2=`cat $base | grep summary | grep label2 | cut -f 4,6,8,16,19 -d " " | sed 's/,//g'`
	c0=`cat $cnf | grep summary | grep label0 | cut -f 4,6,8,16,19 -d " " | sed 's/,//g'`
	c2=`cat $cnf | grep summary | grep label2 | cut -f 4,6,8,16,19 -d " " | sed 's/,//g'`

	echo "$id baseline label0 $b0"
	echo "$id baseline label2 $b2"
	echo "$id deepcnf label0 $c0"
	echo "$id deepcnf label2 $c2"
done
