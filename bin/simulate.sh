#!/bin/bash

#run these two lines before 
#./purify.gtf.pl $dir/p0.gtf > $dir/p1.gtf
#./fix.gtf.sh $dir/p1.gtf > $dir/p2.gtf

dir=simulation6
num=2

#genome=/home/mingfus/data/transcriptomics/iGenomes/Homo.sapiens/GRCh38/Sequence/Chromosomes/
#gtfdir=/home/mingfus/data/transcriptomics/iGenomes/Homo.sapiens/GRCh38/Annotation/Genes/
genome=/home/mingfus/data/repositories/scallop/data/ensembl/human/chromosomes/
gtfdir=/home/mingfus/data/repositories/scallop/data/ensembl/human/gtf/
gtf1=$gtfdir/p2.gtf
gtf2=$gtfdir/p2_sorted.gtf

mkdir -p $dir

for i in `seq 1 $num`
do
	cur=$dir/$i
	mkdir -p $cur
	ln -sf $gtf1 $cur/
	ln -sf $gtf2 $cur/

	params=$cur/params

#echo "REF_FILE_NAME	$name.gtf" > $params
#echo "NB_MOLECULES	10000000" >> $params
#echo "EXPRESSION_K	-0.1" >> $params
#echo "GEN_DIR			." >> $params
#echo "LOAD_CODING		true" >> $params
#echo "LOAD_NONCODING	false" >> $params
#echo "PRO_FILE_NAME	profile" >> $params
#echo "LIB_FILE_NAME	libfile" >> $params

	echo "REF_FILE_NAME   p2.gtf" > $params
	echo "GEN_DIR         $genome" >> $params
	echo "NB_MOLECULES    5000000" >> $params
	echo "TSS_MEAN	50" >> $params
	echo "POLYA_SCALE     100" >> $params
	echo "POLYA_SHAPE     1.5" >> $params
	echo "FRAG_SUBSTRATE	RNA" >> $params
	echo "FRAG_METHOD	UR" >> $params
	echo "FRAG_UR_ETA     350" >> $params
	echo "RTRANSCRIPTION	YES" >> $params
	echo "RT_MOTIF	default" >> $params
	echo "PCR_DISTRIBUTION default" >> $params
	echo "GC_MEAN 	 NaN" >> $params
	echo "PCR_PROBABILITY  0.05" >> $params
	echo "FILTERING 	NO" >> $params
	echo "READ_NUMBER	150000000" >> $params
	echo "READ_LENGTH	75" >> $params
	echo "PAIRED_END	YES" >> $params
	echo "UNIQUE_IDS	YES" >> $params
	echo "FASTA	YES" >> $params

	flux-simulator -p $params -x -l -s
#./merge.sim.exp.pl $gtf $cur/profile > $cur/expression.gtf
done
