#include <algorithm>
#include "gtf.h"
#include "util.h"

gtf::gtf(const gene &g)
	:gene(g)
{
}

int gtf::build_splice_graph(splice_graph &gr)
{
	build_split_interval_map();
	add_vertices(gr);
	add_edges(gr);
	return 0;
}

int gtf::build_split_interval_map()
{
	imap.clear();
	for(int i = 0; i < transcripts.size(); i++)
	{
		transcript &t = transcripts[i];
		for(int j = 0; j < t.exons.size(); j++)
		{
			PI32 p = t.exons[j];
			imap += make_pair(ROI(p.first, p.second), t.expression);
		}
	}
	return 0;
}

int gtf::add_vertices(splice_graph &gr)
{
	double sum = compute_sum_expression();
	gr.add_vertex();
	gr.set_vertex_string(0, "");
	gr.set_vertex_weight(0, sum);
	gr.set_vertex_info(0, vertex_info());

	SIMI it;
	for(it = imap.begin(); it != imap.end(); it++)
	{
		gr.add_vertex();
		string l = tostring(lower(it->first) % 100000);
		string r = tostring((upper(it->first) - 1) % 100000);
		string s = l + "-" + r;
		gr.set_vertex_string(gr.num_vertices() - 1, s);
		gr.set_vertex_weight(gr.num_vertices() - 1, it->second);
		int length = upper(it->first) - lower(it->first);
		gr.set_vertex_info(gr.num_vertices() - 1, vertex_info(length));
	}

	gr.add_vertex();
	gr.set_vertex_string(gr.num_vertices() - 1, "");
	gr.set_vertex_weight(gr.num_vertices() - 1, sum);
	gr.set_vertex_info(gr.num_vertices() - 1, vertex_info());
	return 0;
}

int gtf::add_edges(splice_graph &gr)
{
	for(int i = 0; i < transcripts.size(); i++)
	{
		transcript &tt = transcripts[i];
		assert(tt.exons.size() >= 1);
		int32_t expr = tt.expression;
		int u = 0;
		for(int k = 0; k < tt.exons.size(); k++)
		{
			PI32 &ge = tt.exons[k];
			SIMI it = imap.find(ge.first);
			assert(it != imap.end());		// make sure all input transcripts with >= 1 expression
			while(true)
			{
				int uu = distance((SIMI)(imap.begin()), it) + 1;
				add_single_edge(u, uu, expr, gr);
				u = uu;
				if(upper(it->first) >= ge.second) break;
				it++;
			}
		}
		add_single_edge(u, gr.num_vertices() -1, expr, gr);
	}
	return 0;
}

int gtf::add_single_edge(int s, int t, double w, splice_graph &gr)
{
	PEB p = gr.edge(s, t);
	if(p.second == true)
	{
		double w0 = gr.get_edge_weight(p.first);	
		gr.set_edge_weight(p.first, w + w0);
	}
	else
	{
		edge_descriptor p = gr.add_edge(s, t);
		gr.set_edge_weight(p, w);
		gr.set_edge_info(p, edge_info());
	}
	return 0;
}

double gtf::compute_sum_expression()
{
	double s = 0;
	for(int i = 0; i < transcripts.size(); i++)
	{
		s += transcripts[i].expression;
	}
	return s;
}

int gtf::output_gtf(ofstream &fout) const
{
	write(fout);
	return 0;
}
