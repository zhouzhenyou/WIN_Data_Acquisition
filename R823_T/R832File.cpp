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

#include "R832File.h"

// Constructors
GSFile::GSFile()
{

}

GSFile::GSFile(const char* file, int Type)
{
    externalInit(file, Type);
}

GSFile::~GSFile()
{

}

void GSFile::externalInit(const char* file, int Type)
{
	mFileType = Type;
    mFp = NULL;
    mFileName = NULL;
    p_Version = NULL;
    memset(&m_file_header, 0, sizeof(m_file_header));
	setFileName(file);
}

void GSFile::setFileType(int Type)
{
	mFileType = Type;
}

void GSFile::setFileName(const char* file)
{
	if (PINVALID(file))
	{
		return;
	}
	
	if (PINVALID(mFileName))
	{
		mFileName = new char[MAX_LINE];
		memset(mFileName, 0, MAX_LINE);
	}

	strcpy(mFileName, file);
    OpenFile();
}

bool GSFile::OpenFile()
{
	if (PINVALID(mFileName))
	{
		return false;
	}

	if (PINVALID(mFp))
	{
		switch(mFileType)
		{
			case ReadOnly:
				mFp = fopen(mFileName, "rb+");
                FileReadInit();
				break;
			case Write:
				mFp = fopen(mFileName, "wb+");
                FileWriteInit();
				break;
            case Add:
                backupFile(mFileName);
                mFp = fopen(mFileName, "wb+");
                restorefile(mFileName);
                break;
			default:
				mFp = fopen(mFileName, "rb+");
				break;
		}
	}

	if (PINVALID(mFp))
	{
		printf("Open File failed error is %s\n", strerror(errno));
		return false;
	}

	return true;
}

bool GSFile::backupFile(const char *original)
{
    if (original != NULL)
    {
        char *tmpFileName = (char *)malloc(strlen(original)+2);
        memset(tmpFileName, 0, strlen(original)+2);
        memcpy(tmpFileName, original, strlen(original));
        strcat(tmpFileName, "m");
        copyTextFile(original, tmpFileName);
        free(tmpFileName);
        return true;
    }
    else
    {
        return false;
    }
}

bool GSFile::restorefile(const char *original)
{
    if (original != NULL)
    {
        char *tmpFileName = (char *)malloc(strlen(original)+2);
        memset(tmpFileName, 0, strlen(original)+2);
        memcpy(tmpFileName, original, strlen(original));
        strcat(tmpFileName, "m");
        const int MAX_LEN = 10;
        char *buffer = (char *)calloc(MAX_LEN, sizeof(char));
        int writtenlen = MAX_LEN;
        FILE *bkfile = fopen(tmpFileName, "rb+");
        fread(buffer, 10, 1, bkfile);
        if (strncmp(FILE_ID, buffer, 10) != 0)
        {
            FileWriteInit();
        }

        fseek(bkfile, 0, SEEK_SET);
        while (!feof(bkfile))
        {
            writtenlen = fread(buffer, 1, MAX_LEN, bkfile);

            if (fwrite(buffer, writtenlen, 1, mFp) != 1)
            {
                //IVT_DBG("copyTextFile %s has not been written completely", destination);
            }
        }
        fclose(bkfile);
        remove(tmpFileName);
        free(buffer);
        free(tmpFileName);
        return true;
    }
    else
    {
        return false;
    }
}

bool GSFile::copyTextFile(const char *original, const char *destination)
{
    if (original == NULL || destination == NULL)
    {
        return false;
    }

    FILE *oriFp, *desFp;

    const int MAX_LEN = 10;
    char *buffer = (char *)calloc(MAX_LEN, sizeof(char));
    int writtenlen = MAX_LEN;

    if (buffer == NULL)
    {
        return false;
    }

    if (access(original, 0) < 0)
    {
        if (buffer != NULL)
        {
            free(buffer);
            buffer = NULL;
        }

        return false;
    }

    if ((oriFp = fopen(original, "rb")) == NULL)
    {
        if (buffer != NULL)
        {
            free(buffer);
            buffer = NULL;
        }

        return false;
    }

    if ((desFp = fopen(destination, "wb")) == NULL)
    {
        if (buffer != NULL)
        {
            free(buffer);
            buffer = NULL;
        }

        fclose(oriFp);
        return false;
    }

    while (!feof(oriFp))
    {
        writtenlen = fread(buffer, 1, MAX_LEN, oriFp);

        if (fwrite(buffer, writtenlen, 1, desFp) != 1)
        {
            //IVT_DBG("copyTextFile %s has not been written completely", destination);
        }
    }

    if (buffer != NULL)
    {
        free(buffer);
        buffer = NULL;
    }

    fclose(oriFp);
    fclose(desFp);

    return true;
}

int GSFile::WriteRecordHeader(void * buffer, int bufferLen)
{
	if (PINVALID(buffer))
	{
		return 0;
	}

    int ret = fwrite(buffer, 1, bufferLen, mFp);
    m_file_header.file_len += ret;
    m_file_header.volumn_num++;
	return ret;
}

int GSFile::updateRecordHeader(void * buffer, int bufferLen)
{
	if (PINVALID(buffer))
	{
		return 0;
	}

    if (mFp != NULL)
    {
        long current_loc = ftell(mFp);
        fseek(mFp, sizeof(file_header), SEEK_SET);
        int ret = fwrite(buffer, 1, bufferLen, mFp);
        fseek(mFp, current_loc, SEEK_SET);
	    return ret;
    }
    else
    {
        return 0;
    }
}

int GSFile::ReadRecordHeader(void * buffer, int bufferLen)
{
	if (PINVALID(buffer))
	{
		return 0;
	}

    if (mFp != NULL)
    {
        //long current_loc = ftell(mFp);
        //fseek(mFp, sizeof(file_header), SEEK_SET);
        int ret = fread(buffer, 1, bufferLen, mFp);
        //fseek(mFp, current_loc, SEEK_SET);
	    return ret;
    }
    else
    {
        return 0;
    }
}

int GSFile::WriteRecord(void * buffer, int bufferLen)
{
	if (PINVALID(buffer))
	{
		return false;
	}

    int ret = fwrite(buffer, 1, bufferLen, mFp);
    m_file_header.file_len += ret;
	return ret;
}

int GSFile::updateRecord(void * buffer, int bufferLen)
{
	if (PINVALID(buffer))
	{
		return false;
	}
    long current_loc = ftell(mFp);
    fseek(mFp, current_loc - sizeof(record_item), SEEK_SET);
    int ret = fwrite(buffer, 1, bufferLen, mFp);
    fseek(mFp, current_loc, SEEK_SET);
	return ret;
}

int GSFile::ReadRecord(void * buffer, int bufferLen)
{
	if (PINVALID(buffer))
	{
		return false;
	}

	return fread(buffer, 1, bufferLen, mFp);
}

void GSFile::FileReadInit()
{
	if (mFp == NULL)
	{
        return;
	}

	fread(&m_file_header, 1, sizeof(file_header), mFp);
}

void GSFile::FileWriteInit()
{
	if (mFp == NULL)
	{
        return;
	}
    memcpy(m_file_header.file_id, FILE_ID, strlen(FILE_ID));
    m_file_header.file_header_len = sizeof(file_header);
    m_file_header.file_len += m_file_header.file_header_len;
    m_file_header.file_version = FILE_SOURCE_TYPE;
	fwrite(&m_file_header, 1, sizeof(file_header), mFp);
}

void GSFile::Done()
{
    if (mFileType == Write)
    {
        fseek(mFp, 0, SEEK_SET);
        fwrite(&m_file_header, 1, sizeof(file_header), mFp);
    }

	if (!PINVALID(mFileName))
	{
		delete mFileName;
	}

	if (p_Version != NULL)
	{
		free(p_Version);
		p_Version = NULL;
	}

	if (!PINVALID(mFp))
	{
		fclose(mFp);
	}
}

uint32 GSFile::GetPosition()
{
	return ftell(mFp);
}

uint32 GSFile::GetLength()
{
    return m_file_header.file_len;
}

uint32 GSFile::GetContentLength()
{
    return m_file_header.file_len - m_file_header.file_header_len;
}

char* GSFile::GerVersion()
{
    return (char *)m_file_header.file_desc;
}

void GSFile::Reset()
{
    fseek(mFp, sizeof(file_header), SEEK_SET);
}

int GSFile::GetFileVersion()
{
    return m_file_header.file_version;
}