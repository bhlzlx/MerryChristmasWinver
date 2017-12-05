##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=MerryChristmasOldver
ConfigurationName      :=Release
WorkspacePath          :=D:/personalproject/github/MerryChristmasWinver
ProjectPath            :=D:/personalproject/github/MerryChristmasWinver/MerryChristmasOldver
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Administrator
Date                   :=2017/12/5
CodeLitePath           :=E:/application/CodeLite
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="MerryChristmasOldver.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  -lgdiplus -lgdi32 -lwinmm -lOle32 -mwindows
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
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -O2 -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=E:\application\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/CPhantomWnd.cpp$(ObjectSuffix) $(IntermediateDirectory)/CRandGen.cpp$(ObjectSuffix) $(IntermediateDirectory)/MerryChristmas.rc$(ObjectSuffix) $(IntermediateDirectory)/TrayIcon.cpp$(ObjectSuffix) $(IntermediateDirectory)/CTimer.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Release"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/personalproject/github/MerryChristmasWinver/MerryChristmasOldver/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/CPhantomWnd.cpp$(ObjectSuffix): CPhantomWnd.cpp $(IntermediateDirectory)/CPhantomWnd.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/personalproject/github/MerryChristmasWinver/MerryChristmasOldver/CPhantomWnd.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPhantomWnd.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPhantomWnd.cpp$(DependSuffix): CPhantomWnd.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPhantomWnd.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CPhantomWnd.cpp$(DependSuffix) -MM CPhantomWnd.cpp

$(IntermediateDirectory)/CPhantomWnd.cpp$(PreprocessSuffix): CPhantomWnd.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPhantomWnd.cpp$(PreprocessSuffix) CPhantomWnd.cpp

$(IntermediateDirectory)/CRandGen.cpp$(ObjectSuffix): CRandGen.cpp $(IntermediateDirectory)/CRandGen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/personalproject/github/MerryChristmasWinver/MerryChristmasOldver/CRandGen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CRandGen.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CRandGen.cpp$(DependSuffix): CRandGen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CRandGen.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CRandGen.cpp$(DependSuffix) -MM CRandGen.cpp

$(IntermediateDirectory)/CRandGen.cpp$(PreprocessSuffix): CRandGen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CRandGen.cpp$(PreprocessSuffix) CRandGen.cpp

$(IntermediateDirectory)/MerryChristmas.rc$(ObjectSuffix): MerryChristmas.rc
	$(RcCompilerName) -i "D:/personalproject/github/MerryChristmasWinver/MerryChristmasOldver/MerryChristmas.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/MerryChristmas.rc$(ObjectSuffix) $(RcIncludePath)
$(IntermediateDirectory)/TrayIcon.cpp$(ObjectSuffix): TrayIcon.cpp $(IntermediateDirectory)/TrayIcon.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/personalproject/github/MerryChristmasWinver/MerryChristmasOldver/TrayIcon.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TrayIcon.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TrayIcon.cpp$(DependSuffix): TrayIcon.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TrayIcon.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TrayIcon.cpp$(DependSuffix) -MM TrayIcon.cpp

$(IntermediateDirectory)/TrayIcon.cpp$(PreprocessSuffix): TrayIcon.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TrayIcon.cpp$(PreprocessSuffix) TrayIcon.cpp

$(IntermediateDirectory)/CTimer.cpp$(ObjectSuffix): CTimer.cpp $(IntermediateDirectory)/CTimer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/personalproject/github/MerryChristmasWinver/MerryChristmasOldver/CTimer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CTimer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CTimer.cpp$(DependSuffix): CTimer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CTimer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CTimer.cpp$(DependSuffix) -MM CTimer.cpp

$(IntermediateDirectory)/CTimer.cpp$(PreprocessSuffix): CTimer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CTimer.cpp$(PreprocessSuffix) CTimer.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


