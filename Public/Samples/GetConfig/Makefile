CC = g++
CFLAGS = -g -fPIC -D_FILELINE -Wno-deprecated 
#HOME = /mnt/Shared/moche 
HOME = /usr/cnpoker/doudizhu/Public

MYSQLINC = /usr/include/mysql
MYSQLLIB = -L /usr/lib64/mysql -l mysqlclient -lz -lm

base_INC = 	-I $(HOME)/Include -I $(MYSQLINC)
	  
HomeObjects	=   $(HOME)/Objects
LibarayObj  =   $(HomeObjects)/UtilityLogger.o \
				$(HomeObjects)/UtilityDrng.o \
				$(HomeObjects)/UtilityIni.o \
				$(HomeObjects)/UtilityMD5.o \
				$(HomeObjects)/UtilityJson.o \
				$(HomeObjects)/UtilityMutex.o \
				$(HomeObjects)/UtilityString.o \
				$(HomeObjects)/UtilityThread.o \
				$(HomeObjects)/UtilityThreadPool.o \
				$(HomeObjects)/UtilityKeyGenerator.o \
				$(HomeObjects)/UtilityBuffer.o \
				$(HomeObjects)/UtilityParserJson.o \
				$(HomeObjects)/UtilityServerInfo.o \
				$(HomeObjects)/MydbcQueryExecuteProcessor.o \
				$(HomeObjects)/MydbcQueryResult.o \
				$(HomeObjects)/MydbcInterface.o \
				$(HomeObjects)/MydbcMysql.o \
				$(HomeObjects)/MydbcDatabase.o \
				$(HomeObjects)/NetworkSocketOption.o \
				$(HomeObjects)/NetworkObject.o \
				$(HomeObjects)/NetworkSession.o \
				$(HomeObjects)/NetworkSessionList.o \
				$(HomeObjects)/NetworkSessionPool.o \
				$(HomeObjects)/NetworkConnector.o \
				$(HomeObjects)/NetworkAcceptor.o \
				$(HomeObjects)/NetworkSyncHandler.o \
				$(HomeObjects)/NetworkServer.o
				
BinObject  	=   main.o		  
			
all: GetConfig

GetConfig: $(BinObject)
	$(CC) -g $(MYSQLLIB) $^ $(LibarayObj) -o  $@ -pthread
	
.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CFLAGS) $(base_INC) -o $@ -c $<

.PHONY:	clean cleanGame
clean:
	rm -f GetConfig