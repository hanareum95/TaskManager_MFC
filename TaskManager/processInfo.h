#ifndef PROCESSINFO_H
#define PROCESSINFO_H
#include <string>
using namespace std;

class ProcessInfo
{

public:
	ProcessInfo(string sPName, int nPID, int nParentPID, int nThreadNum, int nCPU);

	string	GetPName() const;
	int		GetPID() const;
	int		GetParentPID() const;
	int		GetThreadNum() const;
	int		GetCPU() const;
		
private:
	string	m_sPName;
	int		m_nPID;		
	int		m_nParentPID;
	int		m_nThreadNum;
	int		m_nCPU;
};

#endif