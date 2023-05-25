BIN = server

CXX = g++
CXXFLAGS = -std=gnu++17 -Wall -Wextra

#Каталог с *.o файлами
objects_dir := obj

#Каталоги с исходными текстами
source_dirs := .
source_dirs += Network/
source_dirs += Network/Exceptions
source_dirs += DataBase/
source_dirs += Message/
source_dirs += User/
source_dirs += SHA_1/
source_dirs += Handler/


search_wildcards := $(addsuffix /*.cpp,$(source_dirs))

#Список объектных файлов для сборки программы
objectsFile := $(notdir $(patsubst %.cpp,obj/%.o,$(wildcard $(search_wildcards))))

#Список объектных файлов вместе с директорией в которую их помещать
objectsPath := $(addprefix $(objects_dir)/,$(objectsFile))


all: $(BIN)

VPATH := $(source_dirs)

$(BIN): $(objectsPath)
	$(CXX) $^ $(CXXFLAGS) -o $@

$(objects_dir)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -MD $(addprefix -I,$(source_dirs)) $< -o $@

include $(wildcard *.d)

clean:
	rm *.o *.d