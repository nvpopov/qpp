#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#define SPIN_UP 2
#define SPIN_DOWN 1
#define SPIN_HOLE 0
#define SPIN_FULL 3

#define STATE_FF 0
#define STATE_FD 1
#define STATE_DD 2
#define STATE_FS 3
#define STATE_DS 4

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		if (item.size()>0) if(item.at(0)!=delim) elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
static bool is_match(const std::string& text, const std::string& pattern)
{
	return std::string::npos != text.find(pattern);
}

class NatOrbOcc
{
public:
	std::vector<float> occ;
};

/*
 *Hold ci roots information for all states
 */
class CIWaveFuncConf;
class CIWaveFunc
{
public:
	float energy;
	std::vector<CIWaveFuncConf*> conf;
};

/*
 * Hold current ci root information
 */
class CIWaveFuncConf
{
public:
	std::vector<int> conf_space;
	int _f;
	int _d;
	int _s;
	int    conf_space_size;
	int    conf_num;
	float  conf_weight;

	CIWaveFuncConf(int _conf_space_size)
	{
		conf_space_size = _conf_space_size;
		conf_space.resize(conf_space_size);
		std::fill(conf_space.begin(),conf_space.end(),SPIN_HOLE);
	}
};

float GetCIMaxmimumWeight(std::vector<CIWaveFunc*> ciroots)
{
	float maxw=-20000;
	for(int i=0; i<ciroots.size(); i++)
	{
		CIWaveFunc* wfnc = ciroots.at(i);
		for (int q=0; q<wfnc->conf.size(); q++)
		{
			if(wfnc->conf.at(q)->conf_weight>maxw)
				maxw=wfnc->conf.at(q)->conf_weight;
		}
	}
	return maxw;
}

float GetConfAverageWeight(CIWaveFunc* wfnc)
{
	float t=0.0f;
	for(int i=0; i<wfnc->conf.size(); i++)
		t+=wfnc->conf.at(i)->conf_weight;
	t = t / wfnc->conf.size();
	return t;
}

float GetConfMaximumWeight(CIWaveFunc* wfnc)
{
	float t=0.0f;
	for(int i=0; i<wfnc->conf.size(); i++)
		if(t<wfnc->conf.at(i)->conf_weight) t=wfnc->conf.at(i)->conf_weight;
	return t;
}

int GetConfSpaceType(std::vector<int> &conf_state)
{
	bool _f = false;
	bool _d = false;
	bool _s = false;
	for(int i=0; i<7; i++) if((conf_state[i]==SPIN_UP)or(conf_state[i]==SPIN_DOWN)or(conf_state[i]==SPIN_FULL)) _f=true;
	for(int i=7 ;i<11; i++) if((conf_state[i]==SPIN_UP)or(conf_state[i]==SPIN_DOWN)or(conf_state[i]==SPIN_FULL)) _d=true;
	if((conf_state[12]==SPIN_UP)or(conf_state[12]==SPIN_DOWN)or(conf_state[12]==SPIN_FULL)) _s=true;

	if(_f and _d and !_s) return STATE_FD;
	if(_f and !_d and !_s) return STATE_FF;
	if(!_f and _d and !_s) return STATE_DD;
	if(_f and _s and !_d) return STATE_FS;
	if(!_f and _s and _d) return STATE_DS;

}

std::vector<CIWaveFunc*> ParseCIRoots(std::ifstream& mfile)
{
	std::cout.precision(7);
	std::vector<CIWaveFunc*> ci_roots;
	std::string line;
	if (mfile.is_open())
	{
		while (!mfile.eof())
		{
			getline(mfile,line);

			//Found ci root
			if(is_match(line,"printout of CI-coefficients larger than"))
			{
				CIWaveFunc* ci_root = new CIWaveFunc();

				std::string _line;
				float _en;
				//Read energy ex.:"energy=   -9817.594740"
				getline(mfile,_line);
				char delm ='=';
				std::vector<std::string> en_line=split(_line,delm);
				if(en_line.size()>1) _en = atof(en_line.at(1).c_str());
				//std::cout<<_en<<std::endl;
				ci_root->energy=_en;

				//Read conf/sym ex.:"conf/sym"
				getline(mfile,_line);

				//Now read ci_conf until null string encountered
				do
				{
					getline(mfile,_line);
					if(_line.size()>2)
					{
						char dlm =' ';
						std::vector<std::string> ci_line=split(_line,dlm);
						int conf_space_size = (ci_line.at(1)).size();
						CIWaveFuncConf* wfnc=new CIWaveFuncConf(conf_space_size);
						wfnc->conf_weight=atof(ci_line.at(3).c_str());

						std::string manif = ci_line.at(1);
						for(int q=0; q<manif.size(); q++)
						{
							if(manif.at(q)=='u')
								wfnc->conf_space.at(q)=SPIN_UP;
							if(manif.at(q)=='d')
								wfnc->conf_space.at(q)=SPIN_DOWN;
							if(manif.at(q)=='2')
								wfnc->conf_space.at(q)=SPIN_FULL;
						}
						ci_root->conf.push_back(wfnc);
					}
				}
				while (_line.size()>3);
				ci_roots.push_back(ci_root);
			}
			//End Found ci root
		}
	}
	return ci_roots;
}

std::vector<NatOrbOcc*> ParseNatOrbOcc(std::ifstream& mfile)
{
	std::cout.precision(7);
	std::vector<NatOrbOcc*> natorb;
	std::string line;
	if (mfile.is_open())
	{
		while (!mfile.eof())
		{
			getline(mfile,line);

			//Found ci root
			if(is_match(line,"Natural orbitals and occupation numbers for root "))
			{
				NatOrbOcc* noc = new NatOrbOcc();
				getline(mfile,line);
				//std::cout<<line<<std::endl;
				char delm =' ';
				std::vector<std::string> occ_line=split(line,delm);
				//std::cout<<occ_line.size()<<std::endl;
				getline(mfile,line);
				std::vector<std::string> occ_line2=split(line,delm);
				//std::cout<<occ_line.at(2)<<std::endl;
				int orbsize=occ_line.size()-2+occ_line2.size();
				//std::cout<<orbsize<<std::endl;
				noc->occ.resize(orbsize);
				natorb.push_back(noc);
				int q = 0;
				for(int i=2; i<occ_line.size(); i++)
				{
					noc->occ[i-2]=atof(occ_line.at(i).c_str());
					q+=1;
				}
				for(int i=0; i<occ_line2.size(); i++)
				{
					noc->occ[i+q]=atof(occ_line2.at(i).c_str());
				}

				//				for(int i=0; i<noc->occ.size(); i++)
				//					std::cout<<noc->occ.at(i)<< " ";
				//				std::cout<<std::endl;
			}

		}

	}
	return natorb;

}

void AnalyzeOcc(std::vector<NatOrbOcc*> natorbocc, int state_num)
{
	NatOrbOcc* state = natorbocc.at(state_num);
	float f_occ = 0.0f;
	float d_occ = 0.0f;
	float s_occ = 0.0f;
	for(int i=0; i<7; i++) f_occ += state->occ.at(i);
	for(int i=7; i<12; i++) d_occ += state->occ.at(i);

	if (state->occ.size()>12) s_occ = state->occ.at(12);
	std::cout<<"f_occ="<<f_occ<<" d_occ="<<d_occ<<" s_occ="<<s_occ<<" ";
	if (f_occ>0.2) std::cout<<"f";
	if (d_occ>0.2) std::cout<<"d";
	if (s_occ>0.2) std::cout<<"s";
	std::cout<<std::endl;
}

void AnalyzeFDStates(std::vector<CIWaveFunc*>  roots, int state_num)
{
	CIWaveFunc* root=roots.at(state_num);
	//Print state
	int __ff =0;
	int __dd =0;
	int __s =0;
	int __fs =0;
	int __ds =0;
	int __fd =0;

	for(int i=0; i<root->conf.size();i++)
	{
		int c_f=0;
		int c_d=0;
		int c_s=0;
		std::cout<<(i+1)<<":" ;
		for(int q=0; q<root->conf.at(i)->conf_space.size();q++)
		{
			int state_val = root->conf.at(i)->conf_space.at(q);
			switch(state_val)
			{
			case(SPIN_UP):
				std::cout<<"u";
				break;
			case(SPIN_DOWN):
				std::cout<<"d";
				break;
			case(SPIN_FULL):
				std::cout<<"2";
				break;
			case(SPIN_HOLE):
				std::cout<<"0";
				break;
			default:
				break;
			}

			//f state
			if((q>=0)&&(q<7)&&((state_val==SPIN_DOWN)or(state_val==SPIN_UP))) c_f+=1;
			if((q>=0)&&(q<7)&&(state_val==SPIN_FULL)) c_f+=2;

			//d state
			if((q>=7)&&(q<12)&&((state_val==SPIN_DOWN)or(state_val==SPIN_UP))) c_d+=1;
			if((q>=7)&&(q<12)&&(state_val==SPIN_FULL)) c_d+=2;

			//s state
			if((q==12)&&((state_val==SPIN_DOWN)or(state_val==SPIN_UP))) c_s+=1;
			if((q==12)&&(state_val==SPIN_FULL)) c_s+=2;
			
			root->conf.at(i)->_f=c_f;
			root->conf.at(i)->_d=c_d;
			root->conf.at(i)->_s=c_s;

		}

		if((c_f>0)and(c_d>0))__fd+=1;
		if((c_f>0)and(c_d>0))__fd+=1;

		std::cout<<"  f("<<c_f<<"),d("<<c_d<<"),s("<<c_s<<")";

		std::cout<<std::endl;
	}
//
	std::cout<<std::endl;

}

int main(int argc, char *argv[])
{
	std::string line;
	std::ifstream mf("inp.log");
	std::vector<CIWaveFunc*> roots = ParseCIRoots(mf);
	//mf.seekg(mf.beg);
	std::ifstream mf2("inp.log");
	std::vector<NatOrbOcc*> occs = ParseNatOrbOcc(mf2);

	//	//std::cout<<roots.size()<<std::endl;
	//	//std::cout<<GetCIMaxmimumWeight(roots)<<std::endl;
	////	for(int q=0; q<roots.size(); q++)
	////	{
	////		float avr = GetConfAverageWeight(roots.at(q));
	////		float max = GetConfMaximumWeight(roots.at(q));

	////		CIWaveFunc* root = roots.at(q);
	////		float enr = root->energy - roots.at(0)->energy;
	////		for(int i=0; i<root->conf.size();i++)
	////		{
	////			CIWaveFuncConf* conf = root->conf.at(i);
	////			if(conf->conf_weight>max*0.75)
	////			{
	////				std::cout<<GetConfSpaceType(conf->conf_space)<<"("<<conf->conf_weight<<")";
	////			}

	////		}
	////		std::cout<<" "<<enr*220000<<std::endl;
	////	}
//		for(int i=0; i<occs.size(); i++)
//			AnalyzeOcc(occs,i);
	AnalyzeFDStates(roots,0);
}
