/* FreeEMS-Loader- the open source s19 loader with special features for FreeEMS
 *
 * Copyright (C) 2008-2011 by Sean Keys <skeys@powerefi.com>
 *
 * This file is part of the FreeEMS-Loader project.
 *
 * FreeEMS-Loader software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS-Loader software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS-Loader software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at info(at)powerefi(dot)com or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS-Loader to load your firmware!
 *
 */

#ifndef SRECORD_H
#define SRECORD_H

#include <string>
#include <stdio.h>
#include <memory>
#include <string.h>
#include <iostream>
#include <vector>
#include <string>
#include <QString>
#include <QObject>
#include <QDebug>

#include <parsing.h>
#include <loaderTypes.h>

using namespace std;

#define START_OF_ADDRESS_OFFSET  0x04 //the first character of our address in hex ascii
#define BITS_PER_BYTE           0x08 // bits in a byte
#define CHECKSUM_BYTE           0x01 // checksum is 1 byte
#define TWO_BYTES               0x02 // two in hex
#define ONE_BYTE                0x01 // one byte in hex
#define TYPE_ID_BYTES           0x02 // num of bytes in type header
#define ONE_KB                  0x0400 // one kilo byte
#define CH_PAIR_COUNT_BYTE      0x01
#define ASCII_PAIR              0x02
#define LINE_RETURN_CHAR_SIZE	 0x01

/* record status codes */
enum recordStatus{
	LOADABLE = 0,
	RECORD_NULL,
	RECORD_UNHANDLED,
	SKIP_SM_RANGE,
    SKIP_UNLOADABLE,
    VENDOR_RECORD,
	UNLOADABLE_BAD_CSUM = 50,
	UNLOADABLE_BAD_LENGTH,
	UNLOADABLE_BAD_LENGTH_TOO_SHORT,
	UNLOADABLE_BAD_LENGTH_TOO_LONG,
    UNLOADABLE_INVALID_START_CHAR
};

/* GP struct for counting statistics */
typedef struct recordStats{
    int numLoadable;
    int numNull;
    int numUnhandled;
    int numSMRange;
    int numBadCSum;
    int numCorrupt;
    int numUnLoadable;  //eg S0xxxxxx valid but not loadable
    int numBadLength;
    int numLengthShort;
    int numInvalidStartChar; //must always start with 'S'
    int numVendorData;
}recordStatistics;

class FreeEMS_LoaderSREC {

public:
	FreeEMS_LoaderSREC(int type);
	FreeEMS_LoaderSREC();
	FreeEMS_LoaderSREC(char *input, int numBytes, int type, unsigned int recordAddress);
	virtual ~FreeEMS_LoaderSREC();
	int	fillRecord(std::vector<unsigned char> binaryChars);
	void setPayloadStatus(int);
	int getPayloadStatus();
	bool verifyRecord();
    unsigned int getRecordAddress();
	char getNextByte();
	int getRecordTypeIndex();
	void buildRecord();
	void printRecord();
	int createFromString(string* lineIn);
	std::string	retRecordString();
	QString getAllVendorData();
	bool isRecordNull();
	bool mismatchedCheckSum;
	bool correctLineLength;
	void calculateCheckSum();
	int putNextByte(char byte);
	int setRecordAddress(unsigned int address);
	int setRecordAddress(char* address);
	int setRecordType(int type);
	int	setTypeIndex(int type);
	void setNumPairsInRecord();
	void initVariables();
    bool lineIsLoadable(string* line);
	unsigned char getCalculatedSum();
	bool areCharactersValid();
	char recordPayload[512]; //ascii pair representaion of the payload
	unsigned int payloadAddress;
	int recordPayloadBytes;
	char recordBytes[256]; //char string representaion of the payload  according to the s-rec specs 256 is the max TODO maybe vector this

private:
	string record;
	char recordAddressChars[12]; //ascii pair representation of the address
	char recordTypeIdChars[TWO_BYTES];
	char recordPayloadPairCountChars[TWO_BYTES];
	char recordCheckSumChars[TWO_BYTES];
	unsigned char recordChkSum;
	unsigned char recordLoadedChkSum;
	int charsInAddress;
	int recordIndex;
	int bytePairCount; //These characters when paired and interpreted as a hexadecimal value, display the count of remaining character pairs in the record.
	int typeIndex;
	int numHexValues;
	bool writeAccess;
	bool addressIsSet;
	bool typeIsSet;
	bool numPairsSet;
	bool recordIsNull;
	int m_payloadStatus;
};

#else
/* let us know if we are being untidy with headers */
#warning "Header file SRECORD_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
