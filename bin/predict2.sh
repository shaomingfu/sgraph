#!/bin/bash

dir=dataset5
#bam=./true_alignment.bam
bam=star_without_gene_models.bam
gtf=./expression.gtf

mkdir -p $dir

./sgraph $bam $gtf > $dir/predicts
