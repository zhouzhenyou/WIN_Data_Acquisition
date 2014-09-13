#ifndef CDLGCONFIGURE_H_
#define CDLGCONFIGURE_H_

#include "stdafx.h"

class CDlgconfigure
{
public:
    CDlgconfigure();
    void setVelocity(float arg);
    float getVelocity();
    void setFrequency(float arg);
    float getFrequency();
    void setProjectName(CString arg);
    CString getProjectName();
    void setFilter(CString arg);
    CString getFilter();
    void setSize(CString arg);
    CString getSize();
    void setSensior(CString arg);
    CString getSensior();
    void setMaterial(CString arg);
    CString getMaterial();
    int getTinyDeficiency();
    void setTinyDeficiency(int arg);
    int getMidDeficiency();
    void setMidDeficiency(int arg);
    int getHugeDeficiency();
    void setHugeDeficiency(int arg);
    int getIronTramp();
    void setIronTramp(int arg);
    int getTinyDeficiencyB();
    void setTinyDeficiencyB(int arg);
    int getMidDeficiencyB();
    void setMidDeficiencyB(int arg);
    int getHugeDeficiencyB();
    void setHugeDeficiencyB(int arg);
    int getIronTrampB();
    void setIronTrampB(int arg);
    int getTinyDeficiencyC();
    void setTinyDeficiencyC(int arg);
    int getMidDeficiencyC();
    void setMidDeficiencyC(int arg);
    int getHugeDeficiencyC();
    void setHugeDeficiencyC(int arg);
    int getIronTrampC();
    void setIronTrampC(int arg);
    int getDistance();
    void setDistance(int arg);
public:
    int current_subvol;
private:
    float m_velocity;
    CString m_projectName;
    float m_frequence;
    CString m_size;
    CString m_sensior;
    CString m_filter;
    CString m_material;
    int m_tiny_deficiency;
    int m_tiny_deficiency_B;
    int m_tiny_deficiency_C;
    int m_mid_deficiency;
    int m_mid_deficiency_B;
    int m_mid_deficiency_C;
    int m_huge_deficiency;
    int m_huge_deficiency_B;
    int m_huge_deficiency_C;
    int m_iron_tramp;
    int m_iron_tramp_B;
    int m_iron_tramp_C;
    int m_distance;
};

#endif
