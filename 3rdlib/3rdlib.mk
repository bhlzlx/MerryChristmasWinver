##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=3rdlib
ConfigurationName      :=Debug
WorkspacePath          :=D:/personalproject/github/MerryChristmasWinver
ProjectPath            :=D:/personalproject/github/MerryChristmasWinver/3rdlib
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Administrator
Date                   :=05/12/2017
CodeLitePath           :=E:/application/CodeLite
LinkerName             :=C:/TDM-GCC-32/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-32/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../bin/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="3rdlib.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-32/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-32/bin/ar.exe rcu
CXX      := C:/TDM-GCC-32/bin/g++.exe
CC       := C:/TDM-GCC-32/bin/gcc.exe
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-32/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=E:\application\CodeLite
Objects0=$(IntermediateDirectory)/cjson_cJSON.c$(ObjectSuffix) $(IntermediateDirectory)/cjson_cJSON_Utils.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "D:\personalproject\github\MerryChristmasWinver/.build-debug"
	@echo rebuilt > "D:\personalproject\github\MerryChristmasWinver/.build-debug/3rdlib"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


./Debug:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/cjson_cJSON.c$(ObjectSuffix): cjson/cJSON.c $(IntermediateDirectory)/cjson_cJSON.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/personalproject/github/MerryChristmasWinver/3rdlib/cjson/cJSON.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cjson_cJSON.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cjson_cJSON.c$(DependSuffix): cjson/cJSON.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cjson_cJSON.c$(ObjectSuffix) -MF$(IntermediateDirectory)/cjson_cJSON.c$(DependSuffix) -MM cjson/cJSON.c

$(IntermediateDirectory)/cjson_cJSON.c$(PreprocessSuffix): cjson/cJSON.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cjson_cJSON.c$(PreprocessSuffix) cjson/cJSON.c

$(IntermediateDirectory)/cjson_cJSON_Utils.c$(ObjectSuffix): cjson/cJSON_Utils.c $(IntermediateDirectory)/cjson_cJSON_Utils.c$(DependSuffix)
	$(CC) $(SourceSwitch) "D:/personalproject/github/MerryChristmasWinver/3rdlib/cjson/cJSON_Utils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cjson_cJSON_Utils.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cjson_cJSON_Utils.c$(DependSuffix): cjson/cJSON_Utils.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cjson_cJSON_Utils.c$(ObjectSuffix) -MF$(IntermediateDirectory)/cjson_cJSON_Utils.c$(DependSuffix) -MM cjson/cJSON_Utils.c

$(IntermediateDirectory)/cjson_cJSON_Utils.c$(PreprocessSuffix): cjson/cJSON_Utils.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cjson_cJSON_Utils.c$(PreprocessSuffix) cjson/cJSON_Utils.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


