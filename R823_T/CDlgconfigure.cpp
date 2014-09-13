#include "CDlgconfigure.h"


/*

CString - float float.Format("%f",float);
float - CString float = _tstof(CString)


*/


CDlgconfigure::CDlgconfigure()
{
    m_velocity = 0.0;
    m_frequence = 0.0;
    
    current_subvol = -1;

    m_projectName = _T("");
    m_material = _T("");
    m_tiny_deficiency = 0;
    m_tiny_deficiency_B = 0;
    m_tiny_deficiency_C = 0;
    m_mid_deficiency = 0;
    m_mid_deficiency_B = 0;
    m_mid_deficiency_C = 0;
    m_huge_deficiency = 0;
    m_huge_deficiency_B = 0;
    m_huge_deficiency_C = 0;
    m_iron_tramp = 0;
    m_iron_tramp_B = 0;
    m_iron_tramp_C = 0;
    m_distance = 0;
}

void CDlgconfigure::setFilter(CString arg)
{
    m_filter = arg;
}

CString CDlgconfigure::getFilter()
{
    return m_filter;
}

void CDlgconfigure::setFrequency(float arg)
{
    m_frequence = arg;
}

float CDlgconfigure::getFrequency()
{
    return m_frequence;
}

void CDlgconfigure::setProjectName(CString arg)
{
    m_projectName = arg;
}

CString CDlgconfigure::getProjectName()
{
    return m_projectName;
}

void CDlgconfigure::setVelocity(float arg)
{
    m_velocity = arg;
}

float CDlgconfigure::getVelocity()
{
    return m_velocity;
}

void CDlgconfigure::setSize(CString arg)
{
    m_size = arg;
}

CString CDlgconfigure::getSize()
{
    return m_size;
}

void CDlgconfigure::setSensior(CString arg)
{
    m_sensior = arg;
}

CString CDlgconfigure::getSensior()
{
    return m_sensior;
}

void CDlgconfigure::setMaterial(CString arg)
{
    m_material = arg;
}

CString CDlgconfigure::getMaterial()
{
    return m_material;
}

int CDlgconfigure::getTinyDeficiency()
{
    return m_tiny_deficiency;
}

void CDlgconfigure::setTinyDeficiency(int arg)
{
    m_tiny_deficiency = arg;
}

int CDlgconfigure::getMidDeficiency()
{
    return m_mid_deficiency;
}

void CDlgconfigure::setMidDeficiency(int arg)
{
    m_mid_deficiency = arg;
}

int CDlgconfigure::getHugeDeficiency()
{
    return m_huge_deficiency;
}

void CDlgconfigure::setHugeDeficiency(int arg)
{
    m_huge_deficiency = arg;
}

int CDlgconfigure::getTinyDeficiencyB()
{
    return m_tiny_deficiency_B;
}

void CDlgconfigure::setTinyDeficiencyB(int arg)
{
    m_tiny_deficiency_B = arg;
}

int CDlgconfigure::getMidDeficiencyB()
{
    return m_mid_deficiency_B;
}

void CDlgconfigure::setMidDeficiencyB(int arg)
{
    m_mid_deficiency_B = arg;
}

int CDlgconfigure::getHugeDeficiencyB()
{
    return m_huge_deficiency_B;
}

void CDlgconfigure::setHugeDeficiencyB(int arg)
{
    m_huge_deficiency_B = arg;
}

int CDlgconfigure::getTinyDeficiencyC()
{
    return m_tiny_deficiency_C;
}

void CDlgconfigure::setTinyDeficiencyC(int arg)
{
    m_tiny_deficiency_C = arg;
}

int CDlgconfigure::getMidDeficiencyC()
{
    return m_mid_deficiency_C;
}

void CDlgconfigure::setMidDeficiencyC(int arg)
{
    m_mid_deficiency_C = arg;
}

int CDlgconfigure::getHugeDeficiencyC()
{
    return m_huge_deficiency_C;
}

void CDlgconfigure::setHugeDeficiencyC(int arg)
{
    m_huge_deficiency_C = arg;
}

int CDlgconfigure::getIronTramp()
{
    return m_iron_tramp;
}

void CDlgconfigure::setIronTramp(int arg)
{
    m_iron_tramp = arg;
}

int CDlgconfigure::getIronTrampB()
{
    return m_iron_tramp_B;
}

void CDlgconfigure::setIronTrampB(int arg)
{
    m_iron_tramp_B = arg;
}

int CDlgconfigure::getIronTrampC()
{
    return m_iron_tramp_C;
}

void CDlgconfigure::setIronTrampC(int arg)
{
    m_iron_tramp_C = arg;
}

int CDlgconfigure::getDistance()
{
    return m_distance;
}

void CDlgconfigure::setDistance(int arg)
{
    m_distance = arg;
}