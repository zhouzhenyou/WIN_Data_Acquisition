/**
 *
 *                 CopyRight (c) 2012 IVTCorporation
 *                       All rights reserved
 *
 * FileName: INIReader.h
 *
 * Abstract: To read information from the configure INI file
 *
 *
 * Author:  zhou zhenyou
 *
 * Modification history:
 *   1.1	2012/15/6 File created
 *
 * */

#ifndef INIREADER_H
#define INIREADER_H

#include "stdafx.h"

#define PINVALID(A)       (A == NULL)
#define INI_SPLIT "="
#define MAX_LINE          100

typedef struct _value
{
    DWORD id;
    DWORD len;
} value;

typedef struct _value_index
{
    DWORD id;
    DWORD mid;
} value_index;

class INIReader
{
	public:
		INIReader(char* argFileName);
		~INIReader();
		
		void read(char* arg, char* argValue);
        void write(char *arg, char* argValue);
		
	private:
		char *mFileName;
		char* pEntry;
		char* pEntryValue;
		char* pEntryName;
};


#endif 
