#include "processInfo.h"
#include <iostream>
#include <iomanip>
using namespace std;

ProcessInfo::ProcessInfo(string sPName, int nPID, int nParentPID, int nThreadNum, int nCPU)
{
	this->m_sPName = sPName;
	this->m_nPID = nPID;
	this->m_nParentPID = nParentPID;
	this->m_nThreadNum = nThreadNum;
	this->m_nCPU = nCPU;
}

string	ProcessInfo::GetPName() const
{ 
	return m_sPName; 
}

int	ProcessInfo::GetPID() const
{ 
	return m_nPID; 
}

int	ProcessInfo::GetParentPID() const
{ 
	return m_nParentPID; 
}

int	ProcessInfo::GetThreadNum() const
{ 
	return m_nThreadNum; 
}

int	ProcessInfo::GetCPU() const
{ 
	return m_nCPU; 
}