##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=3rdlib
ConfigurationName      :=Debug
WorkspacePath          :=E:/Github/MerryChristmas
ProjectPath            :=E:/Github/MerryChristmas/3rdlib
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=phantom
Date                   :=02/12/2017
CodeLitePath           :=D:/app/CodeLite
LinkerName             :=D:/app/tdmgcc/bin/g++.exe
SharedObjectLinkerName :=D:/app/tdmgcc/bin/g++.exe -shared -fPIC
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
RcCompilerName         :=D:/app/tdmgcc/bin/windres.exe
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
AR       := D:/app/tdmgcc/bin/ar.exe rcu
CXX      := D:/app/tdmgcc/bin/g++.exe
CC       := D:/app/tdmgcc/bin/gcc.exe
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := D:/app/tdmgcc/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=D:\app\CodeLite
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
	@$(MakeDirCommand) "E:\Github\MerryChristmas/.build-debug"
	@echo rebuilt > "E:\Github\MerryChristmas/.build-debug/3rdlib"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


./Debug:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/cjson_cJSON.c$(ObjectSuffix): cjson/cJSON.c $(IntermediateDirectory)/cjson_cJSON.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Github/MerryChristmas/3rdlib/cjson/cJSON.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cjson_cJSON.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cjson_cJSON.c$(DependSuffix): cjson/cJSON.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cjson_cJSON.c$(ObjectSuffix) -MF$(IntermediateDirectory)/cjson_cJSON.c$(DependSuffix) -MM cjson/cJSON.c

$(IntermediateDirectory)/cjson_cJSON.c$(PreprocessSuffix): cjson/cJSON.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cjson_cJSON.c$(PreprocessSuffix) cjson/cJSON.c

$(IntermediateDirectory)/cjson_cJSON_Utils.c$(ObjectSuffix): cjson/cJSON_Utils.c $(IntermediateDirectory)/cjson_cJSON_Utils.c$(DependSuffix)
	$(CC) $(SourceSwitch) "E:/Github/MerryChristmas/3rdlib/cjson/cJSON_Utils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cjson_cJSON_Utils.c$(ObjectSuffix) $(IncludePath)
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


