/**
 *
 *                 CopyRight (c) 2012 IVTCorporation
 *                       All rights reserved
 *
 * FileName: DFUFile.h
 *
 * Abstract:
 *
 *
 * Author:  zhou zhenyou
 *
 * Modification history:
 *   1.1	2012/18/6 File created
 *
 * */

#ifndef DFUFILE_H_
#define DFUFILE_H_

#include "R832File.h"

typedef struct _img_file_header
{
	uint8 file_id[10];
	uint16 file_version;
    uint32 file_len;
	uint16 file_header_len;
    uint8 file_desc[100];
    uint16 volumn_num;
} img_file_header;

typedef struct _img_record_item
{
    uint16 img_id;
    uint32 record_len;
    uint32 record_sum_count;
} img_record_item;

class ImgFile : public GSFile
{
	public:
        ImgFile(const char* file, int Type = GSFile::ReadOnly);
		virtual ~ImgFile();

        void SetRecordHeader(img_record_item arg);
        int GetFileVersion();

    private:
		void FileReadInit();
        void FileWriteInit();

        img_file_header m_img_header;
        img_record_item m_img_record_header;
};

#endif
