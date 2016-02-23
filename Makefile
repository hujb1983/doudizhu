CC = g++
CFLAGS = -g -fPIC -D_FILELINE -Wno-deprecated 
#HOME = /mnt/Shared/moche 
HOME = /usr/cnpoker/doudizhu

MYSQLINC = /usr/include/mysql
MYSQLLIB = -L /usr/lib64/mysql -l mysqlclient -lz -lm

base_INC = 	-I$(HOME)/Public/Include \
			-I$(HOME)/Handler \
			-I$(HOME)/Modules \
			-I$(HOME)/Packet \
			-I$(HOME)/Servers \
			-I$(MYSQLINC)

HomeObjects	=   $(HOME)/Public/Objects
HomeHandler	=   $(HOME)/Handler
HomeModules	=   $(HOME)/Modules
HomePacket	=   $(HOME)/Packet
HomeServers	=   $(HOME)/Servers

LibarayObj  =   $(HomeObjects)/UtilityLogger.o \
				$(HomeObjects)/UtilityDrng.o \
				$(HomeObjects)/UtilityIni.o \
				$(HomeObjects)/UtilityMD5.o \
				$(HomeObjects)/UtilityJson.o \
				$(HomeObjects)/UtilityTimer.o \
				$(HomeObjects)/UtilityMutex.o \
				$(HomeObjects)/UtilityString.o \
				$(HomeObjects)/UtilityThread.o \
				$(HomeObjects)/UtilityThreadPool.o \
				$(HomeObjects)/UtilityKeyGenerator.o \
				$(HomeObjects)/UtilityBuffer.o \
				$(HomeObjects)/UtilityParserJson.o \
				$(HomeObjects)/UtilityServerInfo.o \
				$(HomeObjects)/UtilityCommand.o \
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
				$(HomeObjects)/NetworkServer.o \
				$(HomeObjects)/TemplateServerSession.o \
				$(HomeObjects)/TemplateTempSession.o \
				$(HomeObjects)/TemplateLoginSession.o \
				$(HomeObjects)/TemplateAgentSession.o \
				$(HomeObjects)/TemplateLobbySession.o \
				$(HomeObjects)/TemplateGameSession.o \
				$(HomeObjects)/TemplateDBSession.o \
				$(HomeObjects)/TemplateUserSession.o \
				$(HomeObjects)/TemplatePacketHandler.o \
				$(HomeObjects)/TemplateSessionFactory.o \
				$(HomeObjects)/TemplateServerConfig.o \
				$(HomeObjects)/TemplateCommand.o \
				$(HomeObjects)/TemplatePacket.o \
				$(HomeObjects)/TemplateSeasoning.o \
				$(HomeObjects)/TemplateMainServer.o \

ModulesObjs =   $(HomeModules)/LobbyUpdate.o \
				$(HomeModules)/ServerExtern.o \
				$(HomeModules)/PacketHandler.o

PacketObjs	=   $(HomePacket)/PacketLogin.o \
				$(HomePacket)/PacketUser.o \
				$(HomePacket)/PacketFields.o \
				$(HomePacket)/PacketRooms.o \
				$(HomePacket)/PacketRank.o \

HandlerObjs	=   $(HomeHandler)/Handler_PreLogin.o \
				$(HomeHandler)/Handler_Login.o \
				$(HomeHandler)/Handler_FieldsInfo.o \
				$(HomeHandler)/Handler_RoomsInfo.o \
				$(HomeHandler)/Handler_DayRanks.o \
				$(HomeHandler)/Handler_WeekRanks.o

LoginObjs 	=   $(HomeServers)/LoginServer.o
AgentObjs 	=   $(HomeServers)/AgentServer.o
LobbyObjs 	=   $(HomeServers)/LobbyServer.o
GameObjs 	=   $(HomeServers)/GameServer.o
DBObjs 		=   $(HomeServers)/DBServer.o

BINDIR = Bin

all: CheckBin \
	$(BINDIR)/LoginServer \
	$(BINDIR)/AgentServer \
	$(BINDIR)/LobbyServer \
	$(BINDIR)/GameServer \
	$(BINDIR)/DBServer
	
$(BINDIR)/LoginServer: $(ModulesObjs) $(PacketObjs) $(HandlerObjs) $(LoginObjs)
	$(CC) -g $(MYSQLLIB) $^ $(LibarayObj) -o  $@ -pthread

$(BINDIR)/AgentServer: $(ModulesObjs) $(PacketObjs) $(HandlerObjs) $(AgentObjs)
	$(CC) -g $(MYSQLLIB) $^ $(LibarayObj) -o  $@ -pthread

$(BINDIR)/LobbyServer: $(ModulesObjs) $(PacketObjs) $(HandlerObjs) $(LobbyObjs)
	$(CC) -g $(MYSQLLIB) $^ $(LibarayObj) -o  $@ -pthread

$(BINDIR)/GameServer: $(ModulesObjs) $(PacketObjs) $(HandlerObjs) $(GameObjs)
	$(CC) -g $(MYSQLLIB) $^ $(LibarayObj) -o  $@ -pthread
	
$(BINDIR)/DBServer: $(ModulesObjs) $(PacketObjs) $(HandlerObjs) $(DBObjs)
	$(CC) -g $(MYSQLLIB) $^ $(LibarayObj) -o  $@ -pthread

	
	
.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CFLAGS) $(base_INC) -o $@ -c $<

.PHONY: Servers
CheckBin:
	test -d "${BINDIR}" || mkdir $(BINDIR)

.PHONY:	clean cleanGame
clean:
	rm -f $(BINDIR)/LoginServer
	rm -f $(BINDIR)/AgentServer
	rm -f $(BINDIR)/LobbyServer
	rm -f $(BINDIR)/GameServer
	rm -f $(BINDIR)/DBServer
	rm -f $(BINDIR)/core.*
	rm -f $(HOME)/Handler/*.o
	rm -f $(HOME)/Modules/*.o
	rm -f $(HOME)/Packet/*.o
	rm -f $(HOME)/Servers/*.o