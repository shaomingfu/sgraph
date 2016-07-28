bin_PROGRAMS=sgraph

GTFDIR = ../../lib/gtf/src
UTILDIR = ../../lib/util/src
GRAPHDIR = ../../lib/graph/src

sgraph_CPPFLAGS = -pg -std=c++11 -I$(HTSLIB) -I$(GTFDIR) -I$(GRAPHDIR) -I$(UTILDIR)
sgraph_LDFLAGS = -pg -L$(HTSLIB) -L$(GTFDIR) -L$(GRAPHDIR) -L$(UTILDIR) -pthread
sgraph_LDADD = -lhts -lz -lgtf -lgraph -lutil

sgraph_SOURCES = splice_graph.h splice_graph.cc \
				  vertex_info.h vertex_info.cc \
				  edge_info.h edge_info.cc \
				  interval_map.h interval_map.cc \
				  binomial.h binomial.cc \
				  fibonacci_heap.h fibonacci_heap.cc \
				  config.h config.cc \
				  hit.h hit.cc \
				  boundary.h boundary.cc \
				  partial_exon.h partial_exon.cc \
				  region.h region.cc \
				  block.h block.cc \
				  slope.h slope.cc \
				  junction.h junction.cc \
				  bundle_base.h bundle_base.cc \
				  bundle.h bundle.cc \
				  gtf.h gtf.cc \
				  assembler.h assembler.cc \
				  main.cc
