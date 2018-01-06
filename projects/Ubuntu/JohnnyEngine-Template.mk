##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=JohnnyEngine-Template
ConfigurationName      :=Debug
WorkspacePath          :=/media/johnny/Daten/git_repositories/JohnnyEngine/projects/Ubuntu
ProjectPath            :=/media/johnny/Daten/git_repositories/JohnnyEngine/projects/Ubuntu
IntermediateDirectory  :=$(ProjectPath)/$(ConfigurationName)/obj
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Jonas Pucher
Date                   :=06/01/18
CodeLitePath           :=/home/johnny/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
OutputFile             :=$(ProjectPath)/$(ConfigurationName)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="JohnnyEngine-Template.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)/media/johnny/Daten/git_repositories/JohnnyEngine/include $(IncludeSwitch)/media/johnny/Daten/git_repositories/JohnnyEngine/include/TMX $(IncludeSwitch)/media/johnny/Daten/git_repositories/JohnnyEngine/include/TMX/base64 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)JohnnyEngine_d $(LibrarySwitch)Box2D $(LibrarySwitch)assimp $(LibrarySwitch)z $(LibrarySwitch)tinyxml2 $(LibrarySwitch)glfw3 $(LibrarySwitch)SDL2_ttf $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2main $(LibrarySwitch)GLEW $(LibrarySwitch)GL $(LibrarySwitch)dl $(LibrarySwitch)X11 $(LibrarySwitch)pthread 
ArLibs                 :=  "libJohnnyEngine_d" "libBox2D" "libassimp" "libz" "libtinyxml2" "libglfw3" "libSDL2_ttf" "libSDL2" "libSDL2main" "libGLEW" "GL" "dl" "X11" "pthread" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/media/johnny/Daten/git_repositories/JohnnyEngine/projects/Ubuntu/Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -W -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -W -std=c++11 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Game.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d ".build-debug/JohnnyEngine" $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

".build-debug/JohnnyEngine":
	@$(MakeDirCommand) ".build-debug"
	@echo stam > ".build-debug/JohnnyEngine"




MakeIntermediateDirs:
	@test -d $(ProjectPath)/$(ConfigurationName)/obj || $(MakeDirCommand) $(ProjectPath)/$(ConfigurationName)/obj


$(IntermediateDirectory)/.d:
	@test -d $(ProjectPath)/$(ConfigurationName)/obj || $(MakeDirCommand) $(ProjectPath)/$(ConfigurationName)/obj

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/projects/Ubuntu/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/Game.cpp$(ObjectSuffix): Game.cpp $(IntermediateDirectory)/Game.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/projects/Ubuntu/Game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Game.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Game.cpp$(DependSuffix): Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Game.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Game.cpp$(DependSuffix) -MM Game.cpp

$(IntermediateDirectory)/Game.cpp$(PreprocessSuffix): Game.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Game.cpp$(PreprocessSuffix) Game.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ProjectPath)/$(ConfigurationName)/obj/


