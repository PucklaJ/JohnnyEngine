##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=JohnnyEngine
ConfigurationName      :=Debug
WorkspacePath          :=/media/johnny/Daten/Meine_Projekte/CodeLiteProjects/Linux/JohnnyEngine
ProjectPath            :=/media/johnny/Daten/git_repositories/JohnnyEngine/projects/Ubuntu
IntermediateDirectory  :=$(ProjectPath)/$(ConfigurationName)/obj
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Jonas Pucher
Date                   :=07/01/18
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
OutputFile             :=$(ProjectPath)/$(ConfigurationName)/lib$(ProjectName)_d.a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="JohnnyEngine.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)$(JOHNNY_DEPS_INCLUDE) $(IncludeSwitch)$(JOHNNY_DEPS_INCLUDE)/TMX $(IncludeSwitch)$(JOHNNY_DEPS_INCLUDE)/TMX/base64 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -W -std=c++11 -Wall -Wno-ignored-qualifiers -Wno-unused-parameter $(Preprocessors)
CFLAGS   :=  -g -O0 -w $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/up_up_src_Actor.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Camera2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Camera3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Colors.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_ContactListener.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_CubeMap3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_DebugMovement2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_DebugMovement3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Entity3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_FrameBuffer.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_src_Framework.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Geometry.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_GLFWFramework.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Physics2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_PhysicsSprite2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_RenderBuffer.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_RenderManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_RenderTexture.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_RenderUtil.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_ResourceManager.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_src_SDL2_framerate.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_SDL2_gfxPrimitives.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_SDL2_imageFilter.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_SDL2_rotozoom.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_SDLFramework.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Settings.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Shader.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_ShaderUpdater.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_ShadowMap3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Skybox.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_src_Sprite2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_TextActor2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Texture.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_TiledMap.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Timer.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Transform2D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Transform3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Tween.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Vector2.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Vector3.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_src_Vector4.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Vertex3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Window.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_JoystickListener.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_JoystickManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Light3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_LogManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_MainClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_mathematics.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Matrix3.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_up_src_Matrix4.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Mesh3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_Model3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_OBJLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_InputManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_operators.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_up_src_stb_image.c$(ObjectSuffix) 



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
	@$(MakeDirCommand) "/media/johnny/Daten/Meine_Projekte/CodeLiteProjects/Linux/JohnnyEngine/.build-debug"
	@echo rebuilt > "/media/johnny/Daten/Meine_Projekte/CodeLiteProjects/Linux/JohnnyEngine/.build-debug/JohnnyEngine"

MakeIntermediateDirs:
	@test -d $(ProjectPath)/$(ConfigurationName)/obj || $(MakeDirCommand) $(ProjectPath)/$(ConfigurationName)/obj


$(ProjectPath)/$(ConfigurationName)/obj:
	@test -d $(ProjectPath)/$(ConfigurationName)/obj || $(MakeDirCommand) $(ProjectPath)/$(ConfigurationName)/obj

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/up_up_src_Actor.cpp$(ObjectSuffix): ../../src/Actor.cpp $(IntermediateDirectory)/up_up_src_Actor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Actor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Actor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Actor.cpp$(DependSuffix): ../../src/Actor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Actor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Actor.cpp$(DependSuffix) -MM ../../src/Actor.cpp

$(IntermediateDirectory)/up_up_src_Actor.cpp$(PreprocessSuffix): ../../src/Actor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Actor.cpp$(PreprocessSuffix) ../../src/Actor.cpp

$(IntermediateDirectory)/up_up_src_Camera2D.cpp$(ObjectSuffix): ../../src/Camera2D.cpp $(IntermediateDirectory)/up_up_src_Camera2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Camera2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Camera2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Camera2D.cpp$(DependSuffix): ../../src/Camera2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Camera2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Camera2D.cpp$(DependSuffix) -MM ../../src/Camera2D.cpp

$(IntermediateDirectory)/up_up_src_Camera2D.cpp$(PreprocessSuffix): ../../src/Camera2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Camera2D.cpp$(PreprocessSuffix) ../../src/Camera2D.cpp

$(IntermediateDirectory)/up_up_src_Camera3D.cpp$(ObjectSuffix): ../../src/Camera3D.cpp $(IntermediateDirectory)/up_up_src_Camera3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Camera3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Camera3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Camera3D.cpp$(DependSuffix): ../../src/Camera3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Camera3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Camera3D.cpp$(DependSuffix) -MM ../../src/Camera3D.cpp

$(IntermediateDirectory)/up_up_src_Camera3D.cpp$(PreprocessSuffix): ../../src/Camera3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Camera3D.cpp$(PreprocessSuffix) ../../src/Camera3D.cpp

$(IntermediateDirectory)/up_up_src_Colors.cpp$(ObjectSuffix): ../../src/Colors.cpp $(IntermediateDirectory)/up_up_src_Colors.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Colors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Colors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Colors.cpp$(DependSuffix): ../../src/Colors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Colors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Colors.cpp$(DependSuffix) -MM ../../src/Colors.cpp

$(IntermediateDirectory)/up_up_src_Colors.cpp$(PreprocessSuffix): ../../src/Colors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Colors.cpp$(PreprocessSuffix) ../../src/Colors.cpp

$(IntermediateDirectory)/up_up_src_ContactListener.cpp$(ObjectSuffix): ../../src/ContactListener.cpp $(IntermediateDirectory)/up_up_src_ContactListener.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/ContactListener.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_ContactListener.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_ContactListener.cpp$(DependSuffix): ../../src/ContactListener.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_ContactListener.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_ContactListener.cpp$(DependSuffix) -MM ../../src/ContactListener.cpp

$(IntermediateDirectory)/up_up_src_ContactListener.cpp$(PreprocessSuffix): ../../src/ContactListener.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_ContactListener.cpp$(PreprocessSuffix) ../../src/ContactListener.cpp

$(IntermediateDirectory)/up_up_src_CubeMap3D.cpp$(ObjectSuffix): ../../src/CubeMap3D.cpp $(IntermediateDirectory)/up_up_src_CubeMap3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/CubeMap3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_CubeMap3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_CubeMap3D.cpp$(DependSuffix): ../../src/CubeMap3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_CubeMap3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_CubeMap3D.cpp$(DependSuffix) -MM ../../src/CubeMap3D.cpp

$(IntermediateDirectory)/up_up_src_CubeMap3D.cpp$(PreprocessSuffix): ../../src/CubeMap3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_CubeMap3D.cpp$(PreprocessSuffix) ../../src/CubeMap3D.cpp

$(IntermediateDirectory)/up_up_src_DebugMovement2D.cpp$(ObjectSuffix): ../../src/DebugMovement2D.cpp $(IntermediateDirectory)/up_up_src_DebugMovement2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/DebugMovement2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_DebugMovement2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_DebugMovement2D.cpp$(DependSuffix): ../../src/DebugMovement2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_DebugMovement2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_DebugMovement2D.cpp$(DependSuffix) -MM ../../src/DebugMovement2D.cpp

$(IntermediateDirectory)/up_up_src_DebugMovement2D.cpp$(PreprocessSuffix): ../../src/DebugMovement2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_DebugMovement2D.cpp$(PreprocessSuffix) ../../src/DebugMovement2D.cpp

$(IntermediateDirectory)/up_up_src_DebugMovement3D.cpp$(ObjectSuffix): ../../src/DebugMovement3D.cpp $(IntermediateDirectory)/up_up_src_DebugMovement3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/DebugMovement3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_DebugMovement3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_DebugMovement3D.cpp$(DependSuffix): ../../src/DebugMovement3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_DebugMovement3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_DebugMovement3D.cpp$(DependSuffix) -MM ../../src/DebugMovement3D.cpp

$(IntermediateDirectory)/up_up_src_DebugMovement3D.cpp$(PreprocessSuffix): ../../src/DebugMovement3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_DebugMovement3D.cpp$(PreprocessSuffix) ../../src/DebugMovement3D.cpp

$(IntermediateDirectory)/up_up_src_Entity3D.cpp$(ObjectSuffix): ../../src/Entity3D.cpp $(IntermediateDirectory)/up_up_src_Entity3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Entity3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Entity3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Entity3D.cpp$(DependSuffix): ../../src/Entity3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Entity3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Entity3D.cpp$(DependSuffix) -MM ../../src/Entity3D.cpp

$(IntermediateDirectory)/up_up_src_Entity3D.cpp$(PreprocessSuffix): ../../src/Entity3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Entity3D.cpp$(PreprocessSuffix) ../../src/Entity3D.cpp

$(IntermediateDirectory)/up_up_src_FrameBuffer.cpp$(ObjectSuffix): ../../src/FrameBuffer.cpp $(IntermediateDirectory)/up_up_src_FrameBuffer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/FrameBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_FrameBuffer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_FrameBuffer.cpp$(DependSuffix): ../../src/FrameBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_FrameBuffer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_FrameBuffer.cpp$(DependSuffix) -MM ../../src/FrameBuffer.cpp

$(IntermediateDirectory)/up_up_src_FrameBuffer.cpp$(PreprocessSuffix): ../../src/FrameBuffer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_FrameBuffer.cpp$(PreprocessSuffix) ../../src/FrameBuffer.cpp

$(IntermediateDirectory)/up_up_src_Framework.cpp$(ObjectSuffix): ../../src/Framework.cpp $(IntermediateDirectory)/up_up_src_Framework.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Framework.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Framework.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Framework.cpp$(DependSuffix): ../../src/Framework.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Framework.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Framework.cpp$(DependSuffix) -MM ../../src/Framework.cpp

$(IntermediateDirectory)/up_up_src_Framework.cpp$(PreprocessSuffix): ../../src/Framework.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Framework.cpp$(PreprocessSuffix) ../../src/Framework.cpp

$(IntermediateDirectory)/up_up_src_Geometry.cpp$(ObjectSuffix): ../../src/Geometry.cpp $(IntermediateDirectory)/up_up_src_Geometry.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Geometry.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Geometry.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Geometry.cpp$(DependSuffix): ../../src/Geometry.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Geometry.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Geometry.cpp$(DependSuffix) -MM ../../src/Geometry.cpp

$(IntermediateDirectory)/up_up_src_Geometry.cpp$(PreprocessSuffix): ../../src/Geometry.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Geometry.cpp$(PreprocessSuffix) ../../src/Geometry.cpp

$(IntermediateDirectory)/up_up_src_GLFWFramework.cpp$(ObjectSuffix): ../../src/GLFWFramework.cpp $(IntermediateDirectory)/up_up_src_GLFWFramework.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/GLFWFramework.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_GLFWFramework.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_GLFWFramework.cpp$(DependSuffix): ../../src/GLFWFramework.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_GLFWFramework.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_GLFWFramework.cpp$(DependSuffix) -MM ../../src/GLFWFramework.cpp

$(IntermediateDirectory)/up_up_src_GLFWFramework.cpp$(PreprocessSuffix): ../../src/GLFWFramework.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_GLFWFramework.cpp$(PreprocessSuffix) ../../src/GLFWFramework.cpp

$(IntermediateDirectory)/up_up_src_Physics2D.cpp$(ObjectSuffix): ../../src/Physics2D.cpp $(IntermediateDirectory)/up_up_src_Physics2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Physics2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Physics2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Physics2D.cpp$(DependSuffix): ../../src/Physics2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Physics2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Physics2D.cpp$(DependSuffix) -MM ../../src/Physics2D.cpp

$(IntermediateDirectory)/up_up_src_Physics2D.cpp$(PreprocessSuffix): ../../src/Physics2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Physics2D.cpp$(PreprocessSuffix) ../../src/Physics2D.cpp

$(IntermediateDirectory)/up_up_src_PhysicsSprite2D.cpp$(ObjectSuffix): ../../src/PhysicsSprite2D.cpp $(IntermediateDirectory)/up_up_src_PhysicsSprite2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/PhysicsSprite2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_PhysicsSprite2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_PhysicsSprite2D.cpp$(DependSuffix): ../../src/PhysicsSprite2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_PhysicsSprite2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_PhysicsSprite2D.cpp$(DependSuffix) -MM ../../src/PhysicsSprite2D.cpp

$(IntermediateDirectory)/up_up_src_PhysicsSprite2D.cpp$(PreprocessSuffix): ../../src/PhysicsSprite2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_PhysicsSprite2D.cpp$(PreprocessSuffix) ../../src/PhysicsSprite2D.cpp

$(IntermediateDirectory)/up_up_src_RenderBuffer.cpp$(ObjectSuffix): ../../src/RenderBuffer.cpp $(IntermediateDirectory)/up_up_src_RenderBuffer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/RenderBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_RenderBuffer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_RenderBuffer.cpp$(DependSuffix): ../../src/RenderBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_RenderBuffer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_RenderBuffer.cpp$(DependSuffix) -MM ../../src/RenderBuffer.cpp

$(IntermediateDirectory)/up_up_src_RenderBuffer.cpp$(PreprocessSuffix): ../../src/RenderBuffer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_RenderBuffer.cpp$(PreprocessSuffix) ../../src/RenderBuffer.cpp

$(IntermediateDirectory)/up_up_src_RenderManager.cpp$(ObjectSuffix): ../../src/RenderManager.cpp $(IntermediateDirectory)/up_up_src_RenderManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/RenderManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_RenderManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_RenderManager.cpp$(DependSuffix): ../../src/RenderManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_RenderManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_RenderManager.cpp$(DependSuffix) -MM ../../src/RenderManager.cpp

$(IntermediateDirectory)/up_up_src_RenderManager.cpp$(PreprocessSuffix): ../../src/RenderManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_RenderManager.cpp$(PreprocessSuffix) ../../src/RenderManager.cpp

$(IntermediateDirectory)/up_up_src_RenderTexture.cpp$(ObjectSuffix): ../../src/RenderTexture.cpp $(IntermediateDirectory)/up_up_src_RenderTexture.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/RenderTexture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_RenderTexture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_RenderTexture.cpp$(DependSuffix): ../../src/RenderTexture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_RenderTexture.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_RenderTexture.cpp$(DependSuffix) -MM ../../src/RenderTexture.cpp

$(IntermediateDirectory)/up_up_src_RenderTexture.cpp$(PreprocessSuffix): ../../src/RenderTexture.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_RenderTexture.cpp$(PreprocessSuffix) ../../src/RenderTexture.cpp

$(IntermediateDirectory)/up_up_src_RenderUtil.cpp$(ObjectSuffix): ../../src/RenderUtil.cpp $(IntermediateDirectory)/up_up_src_RenderUtil.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/RenderUtil.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_RenderUtil.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_RenderUtil.cpp$(DependSuffix): ../../src/RenderUtil.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_RenderUtil.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_RenderUtil.cpp$(DependSuffix) -MM ../../src/RenderUtil.cpp

$(IntermediateDirectory)/up_up_src_RenderUtil.cpp$(PreprocessSuffix): ../../src/RenderUtil.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_RenderUtil.cpp$(PreprocessSuffix) ../../src/RenderUtil.cpp

$(IntermediateDirectory)/up_up_src_ResourceManager.cpp$(ObjectSuffix): ../../src/ResourceManager.cpp $(IntermediateDirectory)/up_up_src_ResourceManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/ResourceManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_ResourceManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_ResourceManager.cpp$(DependSuffix): ../../src/ResourceManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_ResourceManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_ResourceManager.cpp$(DependSuffix) -MM ../../src/ResourceManager.cpp

$(IntermediateDirectory)/up_up_src_ResourceManager.cpp$(PreprocessSuffix): ../../src/ResourceManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_ResourceManager.cpp$(PreprocessSuffix) ../../src/ResourceManager.cpp

$(IntermediateDirectory)/up_up_src_SDL2_framerate.c$(ObjectSuffix): ../../src/SDL2_framerate.c $(IntermediateDirectory)/up_up_src_SDL2_framerate.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/SDL2_framerate.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_SDL2_framerate.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_SDL2_framerate.c$(DependSuffix): ../../src/SDL2_framerate.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_SDL2_framerate.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_SDL2_framerate.c$(DependSuffix) -MM ../../src/SDL2_framerate.c

$(IntermediateDirectory)/up_up_src_SDL2_framerate.c$(PreprocessSuffix): ../../src/SDL2_framerate.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_SDL2_framerate.c$(PreprocessSuffix) ../../src/SDL2_framerate.c

$(IntermediateDirectory)/up_up_src_SDL2_gfxPrimitives.c$(ObjectSuffix): ../../src/SDL2_gfxPrimitives.c $(IntermediateDirectory)/up_up_src_SDL2_gfxPrimitives.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/SDL2_gfxPrimitives.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_SDL2_gfxPrimitives.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_SDL2_gfxPrimitives.c$(DependSuffix): ../../src/SDL2_gfxPrimitives.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_SDL2_gfxPrimitives.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_SDL2_gfxPrimitives.c$(DependSuffix) -MM ../../src/SDL2_gfxPrimitives.c

$(IntermediateDirectory)/up_up_src_SDL2_gfxPrimitives.c$(PreprocessSuffix): ../../src/SDL2_gfxPrimitives.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_SDL2_gfxPrimitives.c$(PreprocessSuffix) ../../src/SDL2_gfxPrimitives.c

$(IntermediateDirectory)/up_up_src_SDL2_imageFilter.c$(ObjectSuffix): ../../src/SDL2_imageFilter.c $(IntermediateDirectory)/up_up_src_SDL2_imageFilter.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/SDL2_imageFilter.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_SDL2_imageFilter.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_SDL2_imageFilter.c$(DependSuffix): ../../src/SDL2_imageFilter.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_SDL2_imageFilter.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_SDL2_imageFilter.c$(DependSuffix) -MM ../../src/SDL2_imageFilter.c

$(IntermediateDirectory)/up_up_src_SDL2_imageFilter.c$(PreprocessSuffix): ../../src/SDL2_imageFilter.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_SDL2_imageFilter.c$(PreprocessSuffix) ../../src/SDL2_imageFilter.c

$(IntermediateDirectory)/up_up_src_SDL2_rotozoom.c$(ObjectSuffix): ../../src/SDL2_rotozoom.c $(IntermediateDirectory)/up_up_src_SDL2_rotozoom.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/SDL2_rotozoom.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_SDL2_rotozoom.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_SDL2_rotozoom.c$(DependSuffix): ../../src/SDL2_rotozoom.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_SDL2_rotozoom.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_SDL2_rotozoom.c$(DependSuffix) -MM ../../src/SDL2_rotozoom.c

$(IntermediateDirectory)/up_up_src_SDL2_rotozoom.c$(PreprocessSuffix): ../../src/SDL2_rotozoom.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_SDL2_rotozoom.c$(PreprocessSuffix) ../../src/SDL2_rotozoom.c

$(IntermediateDirectory)/up_up_src_SDLFramework.cpp$(ObjectSuffix): ../../src/SDLFramework.cpp $(IntermediateDirectory)/up_up_src_SDLFramework.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/SDLFramework.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_SDLFramework.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_SDLFramework.cpp$(DependSuffix): ../../src/SDLFramework.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_SDLFramework.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_SDLFramework.cpp$(DependSuffix) -MM ../../src/SDLFramework.cpp

$(IntermediateDirectory)/up_up_src_SDLFramework.cpp$(PreprocessSuffix): ../../src/SDLFramework.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_SDLFramework.cpp$(PreprocessSuffix) ../../src/SDLFramework.cpp

$(IntermediateDirectory)/up_up_src_Settings.cpp$(ObjectSuffix): ../../src/Settings.cpp $(IntermediateDirectory)/up_up_src_Settings.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Settings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Settings.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Settings.cpp$(DependSuffix): ../../src/Settings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Settings.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Settings.cpp$(DependSuffix) -MM ../../src/Settings.cpp

$(IntermediateDirectory)/up_up_src_Settings.cpp$(PreprocessSuffix): ../../src/Settings.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Settings.cpp$(PreprocessSuffix) ../../src/Settings.cpp

$(IntermediateDirectory)/up_up_src_Shader.cpp$(ObjectSuffix): ../../src/Shader.cpp $(IntermediateDirectory)/up_up_src_Shader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Shader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Shader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Shader.cpp$(DependSuffix): ../../src/Shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Shader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Shader.cpp$(DependSuffix) -MM ../../src/Shader.cpp

$(IntermediateDirectory)/up_up_src_Shader.cpp$(PreprocessSuffix): ../../src/Shader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Shader.cpp$(PreprocessSuffix) ../../src/Shader.cpp

$(IntermediateDirectory)/up_up_src_ShaderUpdater.cpp$(ObjectSuffix): ../../src/ShaderUpdater.cpp $(IntermediateDirectory)/up_up_src_ShaderUpdater.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/ShaderUpdater.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_ShaderUpdater.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_ShaderUpdater.cpp$(DependSuffix): ../../src/ShaderUpdater.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_ShaderUpdater.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_ShaderUpdater.cpp$(DependSuffix) -MM ../../src/ShaderUpdater.cpp

$(IntermediateDirectory)/up_up_src_ShaderUpdater.cpp$(PreprocessSuffix): ../../src/ShaderUpdater.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_ShaderUpdater.cpp$(PreprocessSuffix) ../../src/ShaderUpdater.cpp

$(IntermediateDirectory)/up_up_src_ShadowMap3D.cpp$(ObjectSuffix): ../../src/ShadowMap3D.cpp $(IntermediateDirectory)/up_up_src_ShadowMap3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/ShadowMap3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_ShadowMap3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_ShadowMap3D.cpp$(DependSuffix): ../../src/ShadowMap3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_ShadowMap3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_ShadowMap3D.cpp$(DependSuffix) -MM ../../src/ShadowMap3D.cpp

$(IntermediateDirectory)/up_up_src_ShadowMap3D.cpp$(PreprocessSuffix): ../../src/ShadowMap3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_ShadowMap3D.cpp$(PreprocessSuffix) ../../src/ShadowMap3D.cpp

$(IntermediateDirectory)/up_up_src_Skybox.cpp$(ObjectSuffix): ../../src/Skybox.cpp $(IntermediateDirectory)/up_up_src_Skybox.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Skybox.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Skybox.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Skybox.cpp$(DependSuffix): ../../src/Skybox.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Skybox.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Skybox.cpp$(DependSuffix) -MM ../../src/Skybox.cpp

$(IntermediateDirectory)/up_up_src_Skybox.cpp$(PreprocessSuffix): ../../src/Skybox.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Skybox.cpp$(PreprocessSuffix) ../../src/Skybox.cpp

$(IntermediateDirectory)/up_up_src_Sprite2D.cpp$(ObjectSuffix): ../../src/Sprite2D.cpp $(IntermediateDirectory)/up_up_src_Sprite2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Sprite2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Sprite2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Sprite2D.cpp$(DependSuffix): ../../src/Sprite2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Sprite2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Sprite2D.cpp$(DependSuffix) -MM ../../src/Sprite2D.cpp

$(IntermediateDirectory)/up_up_src_Sprite2D.cpp$(PreprocessSuffix): ../../src/Sprite2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Sprite2D.cpp$(PreprocessSuffix) ../../src/Sprite2D.cpp

$(IntermediateDirectory)/up_up_src_TextActor2D.cpp$(ObjectSuffix): ../../src/TextActor2D.cpp $(IntermediateDirectory)/up_up_src_TextActor2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/TextActor2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_TextActor2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_TextActor2D.cpp$(DependSuffix): ../../src/TextActor2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_TextActor2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_TextActor2D.cpp$(DependSuffix) -MM ../../src/TextActor2D.cpp

$(IntermediateDirectory)/up_up_src_TextActor2D.cpp$(PreprocessSuffix): ../../src/TextActor2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_TextActor2D.cpp$(PreprocessSuffix) ../../src/TextActor2D.cpp

$(IntermediateDirectory)/up_up_src_Texture.cpp$(ObjectSuffix): ../../src/Texture.cpp $(IntermediateDirectory)/up_up_src_Texture.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Texture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Texture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Texture.cpp$(DependSuffix): ../../src/Texture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Texture.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Texture.cpp$(DependSuffix) -MM ../../src/Texture.cpp

$(IntermediateDirectory)/up_up_src_Texture.cpp$(PreprocessSuffix): ../../src/Texture.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Texture.cpp$(PreprocessSuffix) ../../src/Texture.cpp

$(IntermediateDirectory)/up_up_src_TiledMap.cpp$(ObjectSuffix): ../../src/TiledMap.cpp $(IntermediateDirectory)/up_up_src_TiledMap.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/TiledMap.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_TiledMap.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_TiledMap.cpp$(DependSuffix): ../../src/TiledMap.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_TiledMap.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_TiledMap.cpp$(DependSuffix) -MM ../../src/TiledMap.cpp

$(IntermediateDirectory)/up_up_src_TiledMap.cpp$(PreprocessSuffix): ../../src/TiledMap.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_TiledMap.cpp$(PreprocessSuffix) ../../src/TiledMap.cpp

$(IntermediateDirectory)/up_up_src_Timer.cpp$(ObjectSuffix): ../../src/Timer.cpp $(IntermediateDirectory)/up_up_src_Timer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Timer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Timer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Timer.cpp$(DependSuffix): ../../src/Timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Timer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Timer.cpp$(DependSuffix) -MM ../../src/Timer.cpp

$(IntermediateDirectory)/up_up_src_Timer.cpp$(PreprocessSuffix): ../../src/Timer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Timer.cpp$(PreprocessSuffix) ../../src/Timer.cpp

$(IntermediateDirectory)/up_up_src_Transform2D.cpp$(ObjectSuffix): ../../src/Transform2D.cpp $(IntermediateDirectory)/up_up_src_Transform2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Transform2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Transform2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Transform2D.cpp$(DependSuffix): ../../src/Transform2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Transform2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Transform2D.cpp$(DependSuffix) -MM ../../src/Transform2D.cpp

$(IntermediateDirectory)/up_up_src_Transform2D.cpp$(PreprocessSuffix): ../../src/Transform2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Transform2D.cpp$(PreprocessSuffix) ../../src/Transform2D.cpp

$(IntermediateDirectory)/up_up_src_Transform3D.cpp$(ObjectSuffix): ../../src/Transform3D.cpp $(IntermediateDirectory)/up_up_src_Transform3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Transform3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Transform3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Transform3D.cpp$(DependSuffix): ../../src/Transform3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Transform3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Transform3D.cpp$(DependSuffix) -MM ../../src/Transform3D.cpp

$(IntermediateDirectory)/up_up_src_Transform3D.cpp$(PreprocessSuffix): ../../src/Transform3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Transform3D.cpp$(PreprocessSuffix) ../../src/Transform3D.cpp

$(IntermediateDirectory)/up_up_src_Tween.cpp$(ObjectSuffix): ../../src/Tween.cpp $(IntermediateDirectory)/up_up_src_Tween.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Tween.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Tween.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Tween.cpp$(DependSuffix): ../../src/Tween.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Tween.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Tween.cpp$(DependSuffix) -MM ../../src/Tween.cpp

$(IntermediateDirectory)/up_up_src_Tween.cpp$(PreprocessSuffix): ../../src/Tween.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Tween.cpp$(PreprocessSuffix) ../../src/Tween.cpp

$(IntermediateDirectory)/up_up_src_Vector2.cpp$(ObjectSuffix): ../../src/Vector2.cpp $(IntermediateDirectory)/up_up_src_Vector2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Vector2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Vector2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Vector2.cpp$(DependSuffix): ../../src/Vector2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Vector2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Vector2.cpp$(DependSuffix) -MM ../../src/Vector2.cpp

$(IntermediateDirectory)/up_up_src_Vector2.cpp$(PreprocessSuffix): ../../src/Vector2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Vector2.cpp$(PreprocessSuffix) ../../src/Vector2.cpp

$(IntermediateDirectory)/up_up_src_Vector3.cpp$(ObjectSuffix): ../../src/Vector3.cpp $(IntermediateDirectory)/up_up_src_Vector3.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Vector3.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Vector3.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Vector3.cpp$(DependSuffix): ../../src/Vector3.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Vector3.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Vector3.cpp$(DependSuffix) -MM ../../src/Vector3.cpp

$(IntermediateDirectory)/up_up_src_Vector3.cpp$(PreprocessSuffix): ../../src/Vector3.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Vector3.cpp$(PreprocessSuffix) ../../src/Vector3.cpp

$(IntermediateDirectory)/up_up_src_Vector4.cpp$(ObjectSuffix): ../../src/Vector4.cpp $(IntermediateDirectory)/up_up_src_Vector4.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Vector4.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Vector4.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Vector4.cpp$(DependSuffix): ../../src/Vector4.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Vector4.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Vector4.cpp$(DependSuffix) -MM ../../src/Vector4.cpp

$(IntermediateDirectory)/up_up_src_Vector4.cpp$(PreprocessSuffix): ../../src/Vector4.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Vector4.cpp$(PreprocessSuffix) ../../src/Vector4.cpp

$(IntermediateDirectory)/up_up_src_Vertex3D.cpp$(ObjectSuffix): ../../src/Vertex3D.cpp $(IntermediateDirectory)/up_up_src_Vertex3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Vertex3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Vertex3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Vertex3D.cpp$(DependSuffix): ../../src/Vertex3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Vertex3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Vertex3D.cpp$(DependSuffix) -MM ../../src/Vertex3D.cpp

$(IntermediateDirectory)/up_up_src_Vertex3D.cpp$(PreprocessSuffix): ../../src/Vertex3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Vertex3D.cpp$(PreprocessSuffix) ../../src/Vertex3D.cpp

$(IntermediateDirectory)/up_up_src_Window.cpp$(ObjectSuffix): ../../src/Window.cpp $(IntermediateDirectory)/up_up_src_Window.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Window.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Window.cpp$(DependSuffix): ../../src/Window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Window.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Window.cpp$(DependSuffix) -MM ../../src/Window.cpp

$(IntermediateDirectory)/up_up_src_Window.cpp$(PreprocessSuffix): ../../src/Window.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Window.cpp$(PreprocessSuffix) ../../src/Window.cpp

$(IntermediateDirectory)/up_up_src_JoystickListener.cpp$(ObjectSuffix): ../../src/JoystickListener.cpp $(IntermediateDirectory)/up_up_src_JoystickListener.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/JoystickListener.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_JoystickListener.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_JoystickListener.cpp$(DependSuffix): ../../src/JoystickListener.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_JoystickListener.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_JoystickListener.cpp$(DependSuffix) -MM ../../src/JoystickListener.cpp

$(IntermediateDirectory)/up_up_src_JoystickListener.cpp$(PreprocessSuffix): ../../src/JoystickListener.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_JoystickListener.cpp$(PreprocessSuffix) ../../src/JoystickListener.cpp

$(IntermediateDirectory)/up_up_src_JoystickManager.cpp$(ObjectSuffix): ../../src/JoystickManager.cpp $(IntermediateDirectory)/up_up_src_JoystickManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/JoystickManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_JoystickManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_JoystickManager.cpp$(DependSuffix): ../../src/JoystickManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_JoystickManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_JoystickManager.cpp$(DependSuffix) -MM ../../src/JoystickManager.cpp

$(IntermediateDirectory)/up_up_src_JoystickManager.cpp$(PreprocessSuffix): ../../src/JoystickManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_JoystickManager.cpp$(PreprocessSuffix) ../../src/JoystickManager.cpp

$(IntermediateDirectory)/up_up_src_Light3D.cpp$(ObjectSuffix): ../../src/Light3D.cpp $(IntermediateDirectory)/up_up_src_Light3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Light3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Light3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Light3D.cpp$(DependSuffix): ../../src/Light3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Light3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Light3D.cpp$(DependSuffix) -MM ../../src/Light3D.cpp

$(IntermediateDirectory)/up_up_src_Light3D.cpp$(PreprocessSuffix): ../../src/Light3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Light3D.cpp$(PreprocessSuffix) ../../src/Light3D.cpp

$(IntermediateDirectory)/up_up_src_LogManager.cpp$(ObjectSuffix): ../../src/LogManager.cpp $(IntermediateDirectory)/up_up_src_LogManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/LogManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_LogManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_LogManager.cpp$(DependSuffix): ../../src/LogManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_LogManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_LogManager.cpp$(DependSuffix) -MM ../../src/LogManager.cpp

$(IntermediateDirectory)/up_up_src_LogManager.cpp$(PreprocessSuffix): ../../src/LogManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_LogManager.cpp$(PreprocessSuffix) ../../src/LogManager.cpp

$(IntermediateDirectory)/up_up_src_MainClass.cpp$(ObjectSuffix): ../../src/MainClass.cpp $(IntermediateDirectory)/up_up_src_MainClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/MainClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_MainClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_MainClass.cpp$(DependSuffix): ../../src/MainClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_MainClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_MainClass.cpp$(DependSuffix) -MM ../../src/MainClass.cpp

$(IntermediateDirectory)/up_up_src_MainClass.cpp$(PreprocessSuffix): ../../src/MainClass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_MainClass.cpp$(PreprocessSuffix) ../../src/MainClass.cpp

$(IntermediateDirectory)/up_up_src_mathematics.cpp$(ObjectSuffix): ../../src/mathematics.cpp $(IntermediateDirectory)/up_up_src_mathematics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/mathematics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_mathematics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_mathematics.cpp$(DependSuffix): ../../src/mathematics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_mathematics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_mathematics.cpp$(DependSuffix) -MM ../../src/mathematics.cpp

$(IntermediateDirectory)/up_up_src_mathematics.cpp$(PreprocessSuffix): ../../src/mathematics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_mathematics.cpp$(PreprocessSuffix) ../../src/mathematics.cpp

$(IntermediateDirectory)/up_up_src_Matrix3.cpp$(ObjectSuffix): ../../src/Matrix3.cpp $(IntermediateDirectory)/up_up_src_Matrix3.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Matrix3.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Matrix3.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Matrix3.cpp$(DependSuffix): ../../src/Matrix3.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Matrix3.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Matrix3.cpp$(DependSuffix) -MM ../../src/Matrix3.cpp

$(IntermediateDirectory)/up_up_src_Matrix3.cpp$(PreprocessSuffix): ../../src/Matrix3.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Matrix3.cpp$(PreprocessSuffix) ../../src/Matrix3.cpp

$(IntermediateDirectory)/up_up_src_Matrix4.cpp$(ObjectSuffix): ../../src/Matrix4.cpp $(IntermediateDirectory)/up_up_src_Matrix4.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Matrix4.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Matrix4.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Matrix4.cpp$(DependSuffix): ../../src/Matrix4.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Matrix4.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Matrix4.cpp$(DependSuffix) -MM ../../src/Matrix4.cpp

$(IntermediateDirectory)/up_up_src_Matrix4.cpp$(PreprocessSuffix): ../../src/Matrix4.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Matrix4.cpp$(PreprocessSuffix) ../../src/Matrix4.cpp

$(IntermediateDirectory)/up_up_src_Mesh3D.cpp$(ObjectSuffix): ../../src/Mesh3D.cpp $(IntermediateDirectory)/up_up_src_Mesh3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Mesh3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Mesh3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Mesh3D.cpp$(DependSuffix): ../../src/Mesh3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Mesh3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Mesh3D.cpp$(DependSuffix) -MM ../../src/Mesh3D.cpp

$(IntermediateDirectory)/up_up_src_Mesh3D.cpp$(PreprocessSuffix): ../../src/Mesh3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Mesh3D.cpp$(PreprocessSuffix) ../../src/Mesh3D.cpp

$(IntermediateDirectory)/up_up_src_Model3D.cpp$(ObjectSuffix): ../../src/Model3D.cpp $(IntermediateDirectory)/up_up_src_Model3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/Model3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_Model3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_Model3D.cpp$(DependSuffix): ../../src/Model3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_Model3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_Model3D.cpp$(DependSuffix) -MM ../../src/Model3D.cpp

$(IntermediateDirectory)/up_up_src_Model3D.cpp$(PreprocessSuffix): ../../src/Model3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_Model3D.cpp$(PreprocessSuffix) ../../src/Model3D.cpp

$(IntermediateDirectory)/up_up_src_OBJLoader.cpp$(ObjectSuffix): ../../src/OBJLoader.cpp $(IntermediateDirectory)/up_up_src_OBJLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/OBJLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_OBJLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_OBJLoader.cpp$(DependSuffix): ../../src/OBJLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_OBJLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_OBJLoader.cpp$(DependSuffix) -MM ../../src/OBJLoader.cpp

$(IntermediateDirectory)/up_up_src_OBJLoader.cpp$(PreprocessSuffix): ../../src/OBJLoader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_OBJLoader.cpp$(PreprocessSuffix) ../../src/OBJLoader.cpp

$(IntermediateDirectory)/up_up_src_InputManager.cpp$(ObjectSuffix): ../../src/InputManager.cpp $(IntermediateDirectory)/up_up_src_InputManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/InputManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_InputManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_InputManager.cpp$(DependSuffix): ../../src/InputManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_InputManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_InputManager.cpp$(DependSuffix) -MM ../../src/InputManager.cpp

$(IntermediateDirectory)/up_up_src_InputManager.cpp$(PreprocessSuffix): ../../src/InputManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_InputManager.cpp$(PreprocessSuffix) ../../src/InputManager.cpp

$(IntermediateDirectory)/up_up_src_operators.cpp$(ObjectSuffix): ../../src/operators.cpp $(IntermediateDirectory)/up_up_src_operators.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/operators.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_operators.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_operators.cpp$(DependSuffix): ../../src/operators.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_operators.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_operators.cpp$(DependSuffix) -MM ../../src/operators.cpp

$(IntermediateDirectory)/up_up_src_operators.cpp$(PreprocessSuffix): ../../src/operators.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_operators.cpp$(PreprocessSuffix) ../../src/operators.cpp

$(IntermediateDirectory)/up_up_src_stb_image.c$(ObjectSuffix): ../../src/stb_image.c $(IntermediateDirectory)/up_up_src_stb_image.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/johnny/Daten/git_repositories/JohnnyEngine/src/stb_image.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_up_src_stb_image.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_up_src_stb_image.c$(DependSuffix): ../../src/stb_image.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_up_src_stb_image.c$(ObjectSuffix) -MF$(IntermediateDirectory)/up_up_src_stb_image.c$(DependSuffix) -MM ../../src/stb_image.c

$(IntermediateDirectory)/up_up_src_stb_image.c$(PreprocessSuffix): ../../src/stb_image.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_up_src_stb_image.c$(PreprocessSuffix) ../../src/stb_image.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ProjectPath)/$(ConfigurationName)/obj/


