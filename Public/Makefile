CC = g++
CFLAGS = -g -fPIC -D_FILELINE -Wno-deprecated 
#HOME = /mnt/Shared/moche 
HOME = /usr/cnpoker/doudizhu/Public

MYSQLINC = /usr/include/mysql
MYSQLLIB = -L /usr/lib64/mysql -l mysqlclient -lz -lm

base_INC = 	-I $(HOME)/Utility \
			-I $(HOME)/Mydbc \
			-I $(HOME)/Network \
			-I $(MYSQLINC)
	  
UtilityObjs     = Utility/UtilityLogger.o \
				Utility/UtilityDrng.o \
				Utility/UtilityIni.o \
				Utility/UtilityMD5.o \
				Utility/UtilityJson.o \
				Utility/UtilityMutex.o \
				Utility/UtilityString.o \
				Utility/UtilityThread.o \
				Utility/UtilityThreadPool.o \
				Utility/UtilityKeyGenerator.o \
				Utility/UtilityBuffer.o \
				Utility/UtilityParserJson.o \
				Utility/UtilityServerInfo.o 
  
MydbcObjs       =  Mydbc/MydbcQueryExecuteProcessor.o \
				Mydbc/MydbcQueryResult.o \
				Mydbc/MydbcInterface.o \
				Mydbc/MydbcMysql.o \
				Mydbc/MydbcDatabase.o

				  
TextObject		= main.o		  
				  
BINDIR = Bin
INCDIR = Include
OBJDIR = Objects

all: CheckDir \
	$(BINDIR)/testMakefile

$(BINDIR)/testMakefile: $(UtilityObjs) $(NetworkObjs) $(MydbcObjs) $(TextObject)
	$(CC) -g $(MYSQLLIB) $^ -o $@ -pthread
	-mv -f Mydbc/*.o $(OBJDIR)/
	-mv -f Network/*.o $(OBJDIR)/
	-mv -f Utility/*.o $(OBJDIR)/
	-cp -f Mydbc/*.h $(INCDIR)/
	-cp -f Network/*.h $(INCDIR)/
	-cp -f Utility/*.h $(INCDIR)/
	
.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CFLAGS) $(base_INC) -o $@ -c $<

.PHONY: CheckDir
CheckDir:
	test -d "${BINDIR}" || mkdir $(BINDIR)
	test -d "${INCDIR}" || mkdir $(INCDIR)
	test -d "${OBJDIR}" || mkdir $(OBJDIR)

.PHONY:	clean cleanGame
clean:
	rm -f Mydbc/*.o
	rm -f Network/*.o
	rm -f Utility/*.o
	rm -f $(BINDIR)/*
	rm -f $(INCDIR)/*
	rm -f $(OBJDIR)/*