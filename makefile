#################################
##### Linux Makefile for SDL2 use
#################################

##### Compiler
COMPILER = g++
##### Remove directories
RMDIR = rm -rdf
##### Remove files
RM = rm -f

##### Automatic dependency creation
DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@
##### Linked libraries
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
##### Include path
INC_PATHS = -I$(INC_PATH) $(addprefix -I,$(SDL_INC_PATH))

##### Compile directives
FLAGS = -std=c++11 -Wall -pedantic -Wextra -Werror=init-self -g
##### Extra debugging directives
DFLAGS = -ggdb -O0 -DDEBUG
##### Extra release directives
RFLAGS = -O3 -mtune=native

INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

##### File list by type
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES = $(wildcard $(INC_PATH)/*.h)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d,$(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

##### Executable name
EXEC = LUCITYDOSCARAI

###################################
##### Windows Makefile for SDL2 use
###################################
ifeq ($(OS),Windows_NT)

##### Recursive directory removal command
RMDIR = rd /s /q

##### File delete command
RM = del /q

##### Possible SDL paths. If there's more than one path, add spaces between them
##### Example: SDL_PATHs = C:/SDL2 D:/Tools/SDL2 C:/dev-tools/SDL2
SDL_PATHS = C:/SDL2/x86_64-w64-mingw32 C:/Tools/msys64/mingw64

SDL_INC_PATH += $(addsuffix /include,$(SDL_PATH))
LINK_PATH = $(addprefix -L,$(addsuffix /lib,$(SDL_PATH)))
FLAGS += -mwindows
DFLAGS += -mconsole
LIBS := -lmingw32 -lSDL2main $(LIBS)

##### Executable name
EXEC := $(EXEC).exe

else

UNAME_S := $(shell uname -s)

###############################
##### Mac Makefile for SDL2 use
###############################

ifeq ($(UNAME_S), Darwin)

LIBS = -lm -framework SDL2 -framework SDL_image -framework SDL2_mixer -framework SDL2_ttf

endif
endif

#################################

.PRECIOUS: $(DEP_FILES)
.PHONY: release debug cppcheck valgrind clean folders help

##### General rule
all: $(EXEC)

##### Generates executable
$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

##### Generates object files
$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INC_PATHS) $(addprefix $(SRC_PATH)/,$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

##### Generates dependency files
$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)

clean:
	-$(RMDIR) $(DEP_PATH)
	-$(RMDIR) $(BIN_PATH)
	-$(RM) $(EXEC)

##### Call for cppcheck
cppcheck:
	cppcheck --enable=all . -I./include --suppress=missingIncludeSystem

##### Call for valgrind coverage
valgrind:
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --dsymutil=yes ./$(EXEC)

release: FLAGS += $(RFLAGS)
release: $(EXEC)

debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

folders:
ifeq ($(OS), Windows_NT)
	@if NOT exist $(DEP_PATH) ( mkdir $(DEP_PATH) )
	@if NOT exist $(BIN_PATH) ( mkdir $(BIN_PATH) )
	@if NOT exist $(INC_PATH) ( mkdir $(INC_PATH) )
	@if NOT exist $(SRC_PATH) ( mkdir $(SRC_PATH) )
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
endif

##### Debugging rules
print-% : ; @echo $* = $($*)

help:
ifeq ($(OS), Windows_NT)
	@echo.
endif
	@echo Available commands
	@echo - release:  Builds release version
	@echo - debug:    Builds debug version
	@echo - clean:    Cleans generated files
	@echo - cppcheck: Uses cppcheck on compiled objects
	@echo - valgrind: Uses valgrind on compiled executable
	@echo - help:     Shows help
	@echo - folders:  Generates project directories
ifeq ($(OS), Windows_NT)
	@echo.
endif

.SECONDEXPANSION:
-include $$(DEP_FILES)
