#include "Process.h"

int main( int argc, char ** argv ) 
{ 
	TemplateCommand cmd;
	if ( cmd.ToMain(argc, argv)==FALSE ) {		
		return -1;
	}
	if ( execute_process(cmd, EM_Login)==TRUE ) {
		return -1;
	}
	if ( execute_process(cmd, EM_Agent)==TRUE ) {
		return -1;
	}
	if ( execute_process(cmd, EM_Lobby)==TRUE ) {
		return -1;
	}
	if ( execute_process(cmd, EM_Game)==TRUE ) {
		return -1;
	}
	if ( execute_process(cmd, EM_DB)==TRUE ) {
		return -1;
	}
	return 0;
}