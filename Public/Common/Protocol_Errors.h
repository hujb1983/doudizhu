#ifndef _PROTOCOLCA_ERRORS_H_INCLUDED_
#define _PROTOCOLCA_ERRORS_H_INCLUDED_

#include "Protocol.h"

/***** Client -> Login *****/
enum eERRORS_PROTOCOL
{
    Correct_NAK		    =      0,      // ��ȷ֪ͨ
	ClientLogin_NAK		= 0xFFFF,      // ��½ʧ��
};

#endif // _PROTOCOLCA_H_INCLUDED_
