###############################################################################
########################### Parametros de Projeto #############################
###############################################################################

# TODO: altere a extensão dos arquivos (c ou cpp)
EXT = cpp
# TODO: altere a lista de forma que contenha todos os arquivos .cpp
#       do seu projeto (sem a extensão), que deve estar no diretório 
#       src/montador
SRCS_MONTADOR = $(patsubst %,%.$(EXT),main montador)
OBJS_MONTADOR = $(patsubst %,build/montador/%.o,$(basename $(SRCS_MONTADOR)))
# TODO: altere a lista de forma que contenha todos os arquivos .cpp
#       do seu projeto (sem a extensão), que deve estar no diretório 
#       src/ligador
SRCS_LIGADOR = $(patsubst %,%.$(EXT),main ligador)
OBJS_LIGADOR = $(patsubst %,build/ligador/%.o,$(basename $(SRCS_LIGADOR)))

###############################################################################
########################### Parametros de Ambiente ############################
###############################################################################

CC = gcc
CXX = g++
CCFLAGS = -Wall
CXXFLAGS = -Wall -g
CPPFLAGS = -Iinclude/

###############################################################################
################################ Executáveis ##################################
###############################################################################

all: bin/montador bin/ligador

ifeq ($(EXT), c)
bin/montador: $(OBJS_MONTADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CCFLAGS) $(OBJS_MONTADOR) -o bin/montador
else
bin/montador: $(OBJS_MONTADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CXX) $(CXXFLAGS) $(OBJS_MONTADOR) -o bin/montador
endif

ifeq ($(EXT), c)
bin/ligador: $(OBJS_LIGADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CC) $(CCFLAGS) $(OBJS_LIGADOR) -o bin/ligador
else
bin/ligador: $(OBJS_LIGADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CXX) $(CXXFLAGS) $(OBJS_LIGADOR) -o bin/ligador
endif

###############################################################################
################################## Objetos ####################################
###############################################################################

ifeq ($(EXT), c)
build/montador/%.o: src/montador/%.c
	@echo "- Compilando objeto \"$@\""
	@$(CC) $(CPPFLAGS) $(CCFLAGS) -c $< -o $@
else
build/montador/%.o: src/montador/%.cpp
	@echo "- Compilando objeto \"$@\""
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
endif

ifeq ($(EXT), c)
build/ligador/%.o: src/ligador/%.c
	@echo "- Compilando objeto \"$@\""
	@$(CC) $(CPPFLAGS) $(CCFLAGS) -c $< -o $@
else
build/ligador/%.o: src/ligador/%.cpp
	@echo "- Compilando objeto \"$@\""
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
endif

###############################################################################
################################# Auxiliares ##################################
###############################################################################

clean:
	rm -f bin/* $(OBJS_MONTADOR)
	rm -f bin/* $(OBJS_LIGADOR)
