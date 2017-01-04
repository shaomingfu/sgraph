#!/bin/bash

dir=`pwd`/disk19/human
ver="V8B"
num=10

seqdir=/home/mingfus/data/repositories/scallop/data/ensembl/human/chromosomes.no
cnfdir=/home/mingfus/data/repositories/sgraph/bin/deepcnf4/

#simulate
for i in `seq 1 $num`
do
	cur=$dir/$i
	gtf=$cur/expression.gtf
	bam=$cur/hisat.sort.bam

#	./sgraph $bam $gtf $seqdir $cur/samples.$ver > $cur/index.$ver
#	ln -sf $cur/samples.$ver $cur/samples
#
#	##predict
#	./predictor $cur/samples > $cur/baseline.prob
#	
#	#for pr in `echo "0.70 0.75 0.80 0.85 0.90 0.95"`
#	for pr in `echo "0.15 0.20 0.25 0.30 0.35"`
#	do
#		for ww in `echo "10"`
#		do
#			./pinpoint $cur/samples $cur/baseline.prob $pr $ww 0 > $cur/baseline.$pr.$ww.ppt0
#			#./pinpoint $cur/samples $cur/baseline.prob $pr $ww 1 > $cur/baseline.$pr.$ww.ppt1
#			#./pinpoint $cur/samples $cur/baseline.prob $pr $ww 5 > $cur/baseline.$pr.$ww.ppt5
#		done
#	done
	
	##run deepcnf
	cnfout=$cur/cnf4
	mkdir -p $cnfout
	
	cd $cnfdir
	./oneline_command.sh $cur/samples $cnfout
	cd -
	
	rm -rf $cnfout/cnf4.prob
	rm -rf $cnfout/cnf4.abd
	for i in `cat $cnfout/samples_sample_list`
	do
		cat $cnfout/bou_pred_out/$i >> $cnfout/cnf4.prob	
		#cat $cnfout/abu_pred_val/$i >> $cnfout/cnf.abd
	done
	
	#./abdevaluate $cnfout/cnf.abd $cur/samples 0 > $cur/cnf.abd0
	#./abdevaluate $cnfout/cnf.abd $cur/samples 1 > $cur/cnf.abd1
	#./abdevaluate $cnfout/cnf.abd $cur/samples 5 > $cur/cnf.abd5
	
	for pr in `echo "0.20 0.25 0.30 0.35 0.40 0.45 0.50"`
	do
		for ww in `echo "10"`
		do
			./pinpoint $cur/samples $cnfout/cnf4.prob $pr $ww 0 > $cur/cnf4.$pr.$ww.ppt0
		done
	done

done
