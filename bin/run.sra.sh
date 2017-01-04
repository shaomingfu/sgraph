#!/bin/bash

dir=`pwd`/
ver=V8B
gtf=$dir/p2_sorted.gtf

sradir=/home/mingfus/data/transcriptomics/SRA

seqdir=/home/mingfus/data/repositories/scallop/data/ensembl/human/chromosomes
seqdir0=/home/mingfus/data/repositories/scallop/data/ensembl/human/chromosomes.no
cnfdir=/home/mingfus/data/repositories/sgraph/bin/deepcnf4/

#list="GSM981256 GSM981244 GSM984609 SRR387661 SRR307911 SRR545723 SRR315323 SRR307903 SRR315334 SRR534307"
list="SRR387661 SRR307911 SRR545723 SRR315323 SRR307903 SRR315334 SRR534307"

for id in `echo $list`
do
	bam=$sradir/$id/hisat/hisat.sort.bam
	out=$dir/$id.hisat
	cur=$out/$ver

	echo $cur

#	mkdir -p $cur
#	./sgraph $bam $gtf $seqdir0 $cur/samples > $cur/index
#	./predictor $cur/samples > $cur/baseline.prob
#
#	for pr in `echo "0.20 0.25 0.30 0.35"`
#	do
#		for ww in `echo "10"`
#		do
#			./pinpoint $cur/samples $cur/baseline.prob $pr $ww 0 > $cur/baseline.$pr.$ww.ppt0
#		done
#	done

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
	
	for pr in `echo "0.20 0.25 0.30 0.35 0.40 0.45 0.50"`
	do
		for ww in `echo "10"`
		do
			./pinpoint $cur/samples $cnfout/cnf4.prob $pr $ww 0 > $cur/cnf4.$pr.$ww.ppt0
		done
	done
done
