/**
 *
 *                 CopyRight (c) 2012 IVTCorporation
 *                       All rights reserved
 *
 * FileName: INIReader.cpp
 *
 * Abstract:
 *
 *
 * Author:  zhou zhenyou
 *
 * Modification history:
 *   1.1	2012/15/6 File created
 *
 * */

#include "INIReader.h"


INIReader::INIReader(char* argFileName)
{
	pEntry = new char[MAX_LINE];
	pEntryValue = new char[MAX_LINE];
	pEntryName = new char[MAX_LINE];
	
	if (PINVALID(argFileName))
	{
		AfxMessageBox(_T("INI File name is null"));
		return;
	}
	
	mFileName = argFileName;
    if (access(mFileName, 0) != 0)
    {
        FILE* fp = fopen(mFileName, "w+");
        fclose(fp);
    }
}

INIReader::~INIReader()
{
	if (pEntry != NULL)
	{
		delete pEntry;
	}
	
	if (pEntryValue != NULL)
	{
		delete pEntryValue;
	}
	
	if (pEntryName != NULL)
	{
		delete pEntryName;
	}
}

void INIReader::read(char* arg, char* argValue)
{
	if (PINVALID(arg) || PINVALID(argValue))
	{
		return ;
	}
	
	if (PINVALID(pEntry) || PINVALID(pEntryValue))
	{
		return ;
	}
	
	if (PINVALID(mFileName))
	{
		return ;
	}
	
	FILE *fp = fopen(mFileName, "r+");
	
	if (PINVALID(fp))
	{
		return ;
	}

	while (!feof(fp))
	{

		if (PINVALID(pEntry))
		{
			break;
		}
		
		memset(pEntry, 0, MAX_LINE);
		memset(pEntryValue, 0, MAX_LINE);
		memset(pEntryName, 0, MAX_LINE);
		
		fgets(pEntry, MAX_LINE, fp);
		char* tmp = strstr(pEntry, INI_SPLIT);
		
		if (PINVALID(tmp))
		{
			continue;
		}
		
		//printf("origin tmp len is %d\n", strlen(tmp));
		memset(tmp + strlen(tmp) -1, 0, 1);
		//printf("tmp is %s , present tmp len is %d\n", tmp, strlen(tmp));
		//printf("pEntry is %s,and copy count is %d", pEntry, abs(pEntry - tmp));
		strncpy(pEntryName, pEntry, abs(pEntry - tmp));
		
		if (PINVALID(pEntryName))
		{
			continue;
		}
		//printf("pEntryName is %s\n", pEntryName);
		//printf("arg is %s\n", arg);		
		if (!strcmp(arg, pEntryName))
		{

			strcpy(pEntryValue, tmp + strlen(INI_SPLIT));
			break;
		}
		
	}
	
	fclose(fp);
	
	strcpy(argValue, pEntryValue);
	
	//printf("argValue is %s\n", argValue);
}

void INIReader::write(char* arg, char* argValue)
{
	if (PINVALID(arg) || PINVALID(argValue))
	{
		return ;
	}
	
	if (PINVALID(pEntry) || PINVALID(pEntryValue))
	{
		return ;
	}
	
	if (PINVALID(mFileName))
	{
		return ;
	}

    FILE *fp = fopen(mFileName, "r+");

    fflush(fp);
    fclose(fp);

}
