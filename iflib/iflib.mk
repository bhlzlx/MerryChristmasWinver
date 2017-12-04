##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=iflib
ConfigurationName      :=Debug
WorkspacePath          :=E:/Github/MerryChristmasWinver
ProjectPath            :=E:/Github/MerryChristmasWinver/iflib
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=phantom
Date                   :=04/12/2017
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
ObjectsFileList        :="iflib.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=D:/app/tdmgcc/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../3rdinc 
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
CXXFLAGS :=  -g -std=gnu++11 $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := D:/app/tdmgcc/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=D:\app\CodeLite
Objects0=$(IntermediateDirectory)/utils_JsonBlob.cpp$(ObjectSuffix) $(IntermediateDirectory)/string_uistring.cpp$(ObjectSuffix) $(IntermediateDirectory)/openal_buffer.cpp$(ObjectSuffix) $(IntermediateDirectory)/openal_AudioStream.cpp$(ObjectSuffix) $(IntermediateDirectory)/openal_device.cpp$(ObjectSuffix) $(IntermediateDirectory)/Archive.cpp$(ObjectSuffix) $(IntermediateDirectory)/openal_FFTIndicator.cpp$(ObjectSuffix) $(IntermediateDirectory)/openal_mp3AudioStream.cpp$(ObjectSuffix) $(IntermediateDirectory)/openal_oggAudioStream.cpp$(ObjectSuffix) $(IntermediateDirectory)/utils_JsonStructImp.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/openal_streamAudioSource.cpp$(ObjectSuffix) $(IntermediateDirectory)/openal_source.cpp$(ObjectSuffix) 



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
	@$(MakeDirCommand) "E:\Github\MerryChristmasWinver/.build-debug"
	@echo rebuilt > "E:\Github\MerryChristmasWinver/.build-debug/iflib"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


./Debug:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/utils_JsonBlob.cpp$(ObjectSuffix): utils/JsonBlob.cpp $(IntermediateDirectory)/utils_JsonBlob.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/utils/JsonBlob.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utils_JsonBlob.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utils_JsonBlob.cpp$(DependSuffix): utils/JsonBlob.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utils_JsonBlob.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utils_JsonBlob.cpp$(DependSuffix) -MM utils/JsonBlob.cpp

$(IntermediateDirectory)/utils_JsonBlob.cpp$(PreprocessSuffix): utils/JsonBlob.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utils_JsonBlob.cpp$(PreprocessSuffix) utils/JsonBlob.cpp

$(IntermediateDirectory)/string_uistring.cpp$(ObjectSuffix): string/uistring.cpp $(IntermediateDirectory)/string_uistring.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/string/uistring.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/string_uistring.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/string_uistring.cpp$(DependSuffix): string/uistring.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/string_uistring.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/string_uistring.cpp$(DependSuffix) -MM string/uistring.cpp

$(IntermediateDirectory)/string_uistring.cpp$(PreprocessSuffix): string/uistring.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/string_uistring.cpp$(PreprocessSuffix) string/uistring.cpp

$(IntermediateDirectory)/openal_buffer.cpp$(ObjectSuffix): openal/buffer.cpp $(IntermediateDirectory)/openal_buffer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/openal/buffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/openal_buffer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/openal_buffer.cpp$(DependSuffix): openal/buffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/openal_buffer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/openal_buffer.cpp$(DependSuffix) -MM openal/buffer.cpp

$(IntermediateDirectory)/openal_buffer.cpp$(PreprocessSuffix): openal/buffer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/openal_buffer.cpp$(PreprocessSuffix) openal/buffer.cpp

$(IntermediateDirectory)/openal_AudioStream.cpp$(ObjectSuffix): openal/AudioStream.cpp $(IntermediateDirectory)/openal_AudioStream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/openal/AudioStream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/openal_AudioStream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/openal_AudioStream.cpp$(DependSuffix): openal/AudioStream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/openal_AudioStream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/openal_AudioStream.cpp$(DependSuffix) -MM openal/AudioStream.cpp

$(IntermediateDirectory)/openal_AudioStream.cpp$(PreprocessSuffix): openal/AudioStream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/openal_AudioStream.cpp$(PreprocessSuffix) openal/AudioStream.cpp

$(IntermediateDirectory)/openal_device.cpp$(ObjectSuffix): openal/device.cpp $(IntermediateDirectory)/openal_device.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/openal/device.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/openal_device.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/openal_device.cpp$(DependSuffix): openal/device.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/openal_device.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/openal_device.cpp$(DependSuffix) -MM openal/device.cpp

$(IntermediateDirectory)/openal_device.cpp$(PreprocessSuffix): openal/device.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/openal_device.cpp$(PreprocessSuffix) openal/device.cpp

$(IntermediateDirectory)/Archive.cpp$(ObjectSuffix): Archive.cpp $(IntermediateDirectory)/Archive.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/Archive.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Archive.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Archive.cpp$(DependSuffix): Archive.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Archive.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Archive.cpp$(DependSuffix) -MM Archive.cpp

$(IntermediateDirectory)/Archive.cpp$(PreprocessSuffix): Archive.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Archive.cpp$(PreprocessSuffix) Archive.cpp

$(IntermediateDirectory)/openal_FFTIndicator.cpp$(ObjectSuffix): openal/FFTIndicator.cpp $(IntermediateDirectory)/openal_FFTIndicator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/openal/FFTIndicator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/openal_FFTIndicator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/openal_FFTIndicator.cpp$(DependSuffix): openal/FFTIndicator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/openal_FFTIndicator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/openal_FFTIndicator.cpp$(DependSuffix) -MM openal/FFTIndicator.cpp

$(IntermediateDirectory)/openal_FFTIndicator.cpp$(PreprocessSuffix): openal/FFTIndicator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/openal_FFTIndicator.cpp$(PreprocessSuffix) openal/FFTIndicator.cpp

$(IntermediateDirectory)/openal_mp3AudioStream.cpp$(ObjectSuffix): openal/mp3AudioStream.cpp $(IntermediateDirectory)/openal_mp3AudioStream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/openal/mp3AudioStream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/openal_mp3AudioStream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/openal_mp3AudioStream.cpp$(DependSuffix): openal/mp3AudioStream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/openal_mp3AudioStream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/openal_mp3AudioStream.cpp$(DependSuffix) -MM openal/mp3AudioStream.cpp

$(IntermediateDirectory)/openal_mp3AudioStream.cpp$(PreprocessSuffix): openal/mp3AudioStream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/openal_mp3AudioStream.cpp$(PreprocessSuffix) openal/mp3AudioStream.cpp

$(IntermediateDirectory)/openal_oggAudioStream.cpp$(ObjectSuffix): openal/oggAudioStream.cpp $(IntermediateDirectory)/openal_oggAudioStream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/openal/oggAudioStream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/openal_oggAudioStream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/openal_oggAudioStream.cpp$(DependSuffix): openal/oggAudioStream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/openal_oggAudioStream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/openal_oggAudioStream.cpp$(DependSuffix) -MM openal/oggAudioStream.cpp

$(IntermediateDirectory)/openal_oggAudioStream.cpp$(PreprocessSuffix): openal/oggAudioStream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/openal_oggAudioStream.cpp$(PreprocessSuffix) openal/oggAudioStream.cpp

$(IntermediateDirectory)/utils_JsonStructImp.cpp$(ObjectSuffix): utils/JsonStructImp.cpp $(IntermediateDirectory)/utils_JsonStructImp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/utils/JsonStructImp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utils_JsonStructImp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utils_JsonStructImp.cpp$(DependSuffix): utils/JsonStructImp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utils_JsonStructImp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utils_JsonStructImp.cpp$(DependSuffix) -MM utils/JsonStructImp.cpp

$(IntermediateDirectory)/utils_JsonStructImp.cpp$(PreprocessSuffix): utils/JsonStructImp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utils_JsonStructImp.cpp$(PreprocessSuffix) utils/JsonStructImp.cpp

$(IntermediateDirectory)/openal_streamAudioSource.cpp$(ObjectSuffix): openal/streamAudioSource.cpp $(IntermediateDirectory)/openal_streamAudioSource.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/openal/streamAudioSource.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/openal_streamAudioSource.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/openal_streamAudioSource.cpp$(DependSuffix): openal/streamAudioSource.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/openal_streamAudioSource.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/openal_streamAudioSource.cpp$(DependSuffix) -MM openal/streamAudioSource.cpp

$(IntermediateDirectory)/openal_streamAudioSource.cpp$(PreprocessSuffix): openal/streamAudioSource.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/openal_streamAudioSource.cpp$(PreprocessSuffix) openal/streamAudioSource.cpp

$(IntermediateDirectory)/openal_source.cpp$(ObjectSuffix): openal/source.cpp $(IntermediateDirectory)/openal_source.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Github/MerryChristmasWinver/iflib/openal/source.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/openal_source.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/openal_source.cpp$(DependSuffix): openal/source.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/openal_source.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/openal_source.cpp$(DependSuffix) -MM openal/source.cpp

$(IntermediateDirectory)/openal_source.cpp$(PreprocessSuffix): openal/source.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/openal_source.cpp$(PreprocessSuffix) openal/source.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


