
#include "happyml/happytools.h"

#include <fstream>
#include <sstream>
#include <iomanip>  // std::setprecision


namespace happyml
{
    namespace tools
    {

        /**
         * This string is a template for a DOT file. In this template you can
         * substitute 3 variables:
         * 
         * title: Title of the graph.
         * nodes: x_1 x_2 ... x_d
         * edges: x_1 -> output; x_2 -> output ... or see edgeTemplate. 
         * 
         * @see edgeTemplate
         */
        string linearModelTemplate =
            "digraph LinearModel {"
            "   label=\"{{title}}\";"
            "	rankdir=LR;"
            "	splines=line;"
            "   nodesep=0.1;"
            "	ranksep=1.0;"
            "	center=true;"
            "   node ["
            "       shape=circle,"
            "   	fixedsize=true,"
            "		style=solid,"
            "		color=black"
            "   ];"
            "	edge ["
            "   	color=black,"
            "	];"
            ""
            "	subgraph {"
            "		rank=same;"
            "		x0;"
            "	    node [color=green];"
            "		{{nodes}};"
            //x0 -> x1 -> x2 [style=invis];
            "	}"
            "	subgraph {"
            "       node [color=red];"
            "		output [label=\"h(x)\"];"
            "	}"
            ""
            "   {{edges}}"
            "}";

        string edgeTemplate = "x{{i}} -> output [label=\"{{weight}}\","
            "color=\"0 0 {{color}}\", fontcolor=\"0 0 {{color}}\"];";

        void modelToDot(const LinearModel& lm, const string& filename,
                bool latex)
        {
            ofstream file;
            file.open(filename.c_str());
            
            modelToDot(lm, file, latex);
            
            file.close();
        }

        void modelToDot(const LinearModel& lm, ostream& out, bool latex)
        {
            dictionary dic;
            dic["title"] = "Linear Model";
            
            vec w = lm.getWeights();
            unsigned size = w.size();
            double max = w.max();
            
            stringstream ss;
            for (unsigned i = 1; i < size; ++i)
                ss << "x" << i << " ";
            dic["nodes"] = ss.str();
            
            ss.str("");
            for (unsigned i = 0; i < size; ++i)
            {
                stringstream sss;
                
                double color = 1 - (w[i] / max) / 2 - 0.5;
                sss << setprecision(4) << color;
                string colorStr = sss.str();
                sss.str("");
                
                sss << setprecision(4) << w[i];
                string weightStr = sss.str();
                sss.str("");
                
                sss << i;
                string iStr = sss.str();
                sss.str("");
                
                dictionary dicEdge;
                dicEdge["i"] = iStr;
                dicEdge["weight"] = weightStr;
                dicEdge["color"] = colorStr;
                
                ss << substitute(edgeTemplate, dicEdge);
            }
            dic["edges"] = ss.str();
            
            out << substitute(linearModelTemplate, dic);
        }

        string substitute(const string& in, const dictionary& subst)
        {
            ostringstream out;
            size_t pos = 0;
            for (;;)
            {
                size_t subst_pos = in.find("{{", pos);
                size_t end_pos = in.find("}}", subst_pos);
                if (end_pos == string::npos) break;
        
                out.write(&* in.begin() + pos, subst_pos - pos);
        
                subst_pos += strlen("{{");
                dictionary::const_iterator subst_it
                    = subst.find(in.substr(subst_pos, end_pos - subst_pos));
                if (subst_it == subst.end())
                    throw runtime_error("undefined substitution");
        
                out << subst_it->second;
                pos = end_pos + strlen("}}");
            }
            out << in.substr(pos, string::npos);
            return out.str();
        }
    }
}
