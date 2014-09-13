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

#pragma once

#include "stdafx.h"

#define PINVALID(A)                             (A == NULL)
#define FILE_ID                                 "R832_FILE"
#define FILE_SOURCE_TYPE                        0x01
#define FILE_IMG_TYPE                           0x02
#define MAX_LINE                                100
#define FILE_MAX_BYTE                           1000

#define FILE_HEADER_STRUCT_COUNT				16
#define PSKEY_USER13							0x0297

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned long int uint32;
typedef signed long int int32;

typedef struct _file_header
{
	uint8 file_id[10];
	uint16 file_version;
    uint32 file_len;
	uint16 file_header_len;
    uint8 file_desc[100];
    uint16 volumn_num;
} file_header;

typedef struct _record_item
{
    uint16 record_len;
    uint16 serial;
    uint32 tiny_deficency;
    uint32 mid_deficency;
    uint32 huge_deficency;
    uint32 iron_tramp;
    uint8 volume[MAX_LINE];
    uint16 subVolum;
    uint16 volum_len;
    uint16 range;
    uint32 line;
} record_item;

typedef struct _record_item_header
{
    uint32 sum_count;
    uint8 volume[MAX_LINE];
    uint32 sum_tiny;
    uint32 sum_mid;
    uint32 sum_huge;
    uint32 sum_iron;
    uint32 sum_subvol;
} record_item_header;

typedef struct _record_preference_header
{
    uint32 count;
    uint8 volume[MAX_LINE];
    uint32 sum_tiny;
    uint32 sum_mid;
    uint32 sum_huge;
    uint32 sum_iron;
    uint32 sum_subvol;
} record_preference_header;

typedef struct _record_preference_item
{
    uint32 id;
    uint8 buffer[MAX_LINE];
} record_preference_item;

class GSFile
{
	public:
        GSFile();
		GSFile(const char* file, int Type = ReadOnly);
		virtual ~GSFile();

		enum
		{
			ReadOnly,
			Write,
            Add,
		};

        void externalInit(const char* file, int Type = ReadOnly);

		void setFileName(const char* file);
		void setFileType(int Type);

		int WriteRecordHeader(void * buffer, int bufferLen);
        int updateRecordHeader(void * buffer, int bufferLen);
		int ReadRecordHeader(void * buffer, int bufferLen);

		int WriteRecord(void * buffer, int bufferLen);
        int updateRecord(void * buffer, int bufferLen);
		int ReadRecord(void * buffer, int bufferLen);

        void Reset();

		//It should be invoked When the upload is done
		void Done();

		uint32 GetLength();
		uint32 GetPosition();

		// Exclude the CRC which is consist of the Prefix
		uint32 GetContentLength();
		char* GerVersion();
        int GetFileVersion();

    protected:
		FILE *mFp;

	private:
		bool OpenFile();   

		virtual void FileReadInit();
        virtual void FileWriteInit();

        bool copyTextFile(const char *original, const char *destination);
        bool backupFile(const char *original);
        bool restorefile(const char *original);
		file_header m_file_header;
		int mFileType;
		char *mFileName;
		char *p_Version;
};
