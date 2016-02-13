#include <UtilityInclude.h>
#include <UtilityKeyGenerator.h>

int main( int argc, char ** argv ) 
{
	UtilityKeyGenerator objKey;
	objKey.Create(1, 0xff);
	
	WORD wKey1 = objKey.GetKey();
	DEBUG_MSG( LVL_DEBUG, "objKey = %d", wKey1);
	objKey.RestoreKey(wKey1);
	
	wKey1 = objKey.GetKey();
	DEBUG_MSG( LVL_DEBUG, "objKey = %d", wKey1);
	
	WORD wKey2 = objKey.GetKey();
	DEBUG_MSG( LVL_DEBUG, "objKey = %d", wKey2);
	objKey.RestoreKey(wKey1);
	
	wKey1 = objKey.GetKey();
	DEBUG_MSG( LVL_DEBUG, "objKey = %d", wKey1);
	return 0;
}