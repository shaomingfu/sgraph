bin_PROGRAMS=sgraph

GTFDIR = ../../lib/gtf/src
UTILDIR = ../../lib/util/src
GRAPHDIR = ../../lib/graph/src

sgraph_CPPFLAGS = -pg -std=c++11 -I$(HTSLIB) -I$(GTFDIR) -I$(GRAPHDIR) -I$(UTILDIR) -I$(BOOST_HOME) 
sgraph_LDFLAGS = -pg -L$(HTSLIB) -L$(GTFDIR) -L$(GRAPHDIR) -L$(UTILDIR) -pthread
sgraph_LDADD = -lhts -lz -lgtf -lgraph -lutil

sgraph_SOURCES = interval_map.h interval_map.cc \
				 fscore.h fscore.cc \
				 binomial.h binomial.cc \
				 config.h config.cc \
				 hit.h hit.cc \
				 boundary.h boundary.cc \
				 region.h region.cc \
				 block.h block.cc \
				 junction.h junction.cc \
				 bundle_base.h bundle_base.cc \
				 bundle.h bundle.cc \
				 assembler.h assembler.cc \
				 gtf.h gtf.cc \
				 main.cc

