//---------------------------------------------------------------------------

#ifndef DefineH
#define DefineH
//---------------------------------------------------------------------------


#define UDP_SERVER_PORT	16000
#define UDP_LOCAL_PORT	16000
//#define IP_SERVER "118.223.164.124" // HM
#define IP_SERVER "112.217.45.202" // Globiz
#define IP_LOCAL "192.168.0.47"

#define UDP_SEND_BUF_SIZE 256
#define UDP_RECV_BUF_SIZE 1500
#define UDP_SEND_BUF_SIZE 1500

#define MSG_LOG_FROM_THREAD 10000

#define DEFAULT_PROTOCOL_INFO_LINE_COUNT	6
#define DEFAULT_PROTOCOL_COL_START	2

#define SEND_PROTOCOL_TYPE	1
#define RECV_PROTOCOL_TYPE	2

typedef union unData_8b {
	unsigned char BYTE_Data;
	char CHAR_Data;
	unsigned short WORD_Data;
	short SHORT_Data;
	unsigned int DWORD_Data;
	int	INT_Data;
	//double DOUBLE_Data;
} unDATA_8b;




//---------------------------------------------------------------------------
#endif
