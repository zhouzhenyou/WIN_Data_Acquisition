/**
 *
 *                 CopyRight (c) 2012 IVTCorporation
 *                       All rights reserved
 *
 * FileName: DFUFile.cpp
 *
 * Abstract:
 *
 *
 * Author:  zhou zhenyou
 *
 * Modification history:
 *   1.1	2012/18/6 File created
 *	 1.2	2012/7/26 Remold this class
 * */

#include "R832ImgFile.h"

// Constructors
ImgFile::ImgFile(const char* file, int Type)
    :GSFile(file, Type)
{
    memset(&m_img_header, 0, sizeof(img_file_header));
}

ImgFile::~ImgFile()
{

}

void ImgFile::FileReadInit()
{
	if (mFp == NULL)
	{
        return;
	}
	
    //fseek(mFp, 0, SEEK_SET);
	fread(&m_img_header, 1, sizeof(img_file_header), mFp);
}

void ImgFile::FileWriteInit()
{
	if (mFp == NULL)
	{
        return;
	}
	
    m_img_header.file_version = FILE_IMG_TYPE;
	fwrite(&m_img_header, 1, sizeof(img_file_header), mFp);
}

void ImgFile::SetRecordHeader(img_record_item arg)
{
    m_img_record_header = arg;
}

int ImgFile::GetFileVersion()
{
    return m_img_header.file_version;
}