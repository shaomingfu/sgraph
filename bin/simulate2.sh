#!/bin/bash

#run these two lines before 
#./purify.gtf.pl $dir/p0.gtf > $dir/p1.gtf
#./fix.gtf.sh $dir/p1.gtf > $dir/p2.gtf

dir=`pwd`/disk19/mouse
mkdir -p $dir
echo "V8B" > $dir/version

num=9

#genome=/home/mingfus/data/transcriptomics/iGenomes/Homo.sapiens/GRCh38/Sequence/Chromosomes/
#gtfdir=/home/mingfus/data/transcriptomics/iGenomes/Homo.sapiens/GRCh38/Annotation/Genes/
genome=/home/mingfus/data/repositories/scallop/data/ensembl/mouse/chromosomes/
gtfdir=/home/mingfus/data/repositories/scallop/data/ensembl/mouse/gtf
gtf1=$gtfdir/p2.gtf
gtf2=$gtfdir/p2_sorted.gtf
index=/home/mingfus/data/transcriptomics/HISAT2/indexes/grcm38/genome

tmpdir=/home/mingfus/data/repositories/sgraph/bin/disk19/flux.tmp/
mkdir -p $tmpdir

for i in `seq 1 $num`
do
	cur=$dir/$i
	mkdir -p $cur
	ln -sf $gtf1 $cur/
	ln -sf $gtf2 $cur/

	params=$cur/params

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
	echo "TMP_DIR	$tmpdir" >> $params

	cd $cur
	flux-simulator -p ./params -x -l -s
	cd -

	cat $cur/params.fasta | awk '((NR % 4) == 1) || ((NR % 4) == 2)' > $cur/read1.fa
	cat $cur/params.fasta | awk '((NR % 4) == 3) || ((NR % 4) == 0)' > $cur/read2.fa
	hisat2 -p 8 -x $index -f -1 $cur/read1.fa -2 $cur/read2.fa -S $cur/hisat.sam
	samtools view -b $cur/hisat.sam > $cur/hisat.bam
	samtools sort $cur/hisat.bam > $cur/hisat.sort.bam
	./merge.expression.pl $gtf2 $cur/params.pro > $cur/expression.gtf
done
