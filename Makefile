# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 16:20:03 by mdoquocb          #+#    #+#              #
#    Updated: 2023/03/29 16:20:19 by mdoquocb         ###   ########.ca        #
#                                                                              #
# **************************************************************************** #

PROJECT = webserv

PATH_SOURCE_CODE = Source_code/

	#  BINARY  #

BIN_PATH = $(PATH_SOURCE_CODE)Bin/

BIN_NAME = $(PROJECT)

BIN = $(BIN_NAME)

	#  INCLUDES  #

INC_PATH = $(PATH_SOURCE_CODE)

INC_FLAGS += -I $(INC_PATH)

	#  SOURCES  #

SRC_PATH = $(PATH_SOURCE_CODE)/

SRC_NAME = main.cpp

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

	#  LIB  #

LIB_INC_PATH = Includes/

LIB_BIN_PATH = $(PATH_SOURCE_CODE)Lib/

	#  0-CLI  #

LIB_CLI_NAME = cli

LIB_CLI_PATH = $(PATH_SOURCE_CODE)0-Cli/

INC_FLAGS += -I $(LIB_CLI_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_CLI_NAME)

	#  1-Code #

LIB_CODE_NAME = code

LIB_CODE_PATH = $(PATH_SOURCE_CODE)1-Code/

INC_FLAGS += -I $(LIB_CODE_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_CODE_NAME)

	#  2-Type #

LIB_TYPE_NAME = type

LIB_TYPE_PATH = $(PATH_SOURCE_CODE)2-Type/

INC_FLAGS += -I $(LIB_TYPE_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_TYPE_NAME)

	#  3-Listen #

LIB_LISTEN_NAME = listen

LIB_LISTEN_PATH = $(PATH_SOURCE_CODE)3-Listen/

INC_FLAGS += -I $(LIB_LISTEN_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_LISTEN_NAME)

	#  4-Config #

LIB_CONFIG_NAME = config

LIB_CONFIG_PATH = $(PATH_SOURCE_CODE)4-Config/

INC_FLAGS += -I $(LIB_CONFIG_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_CONFIG_NAME)

	#  5-Socket #

LIB_SOCKET_NAME = socket

LIB_SOCKET_PATH = $(PATH_SOURCE_CODE)5-Socket/

INC_FLAGS += -I $(LIB_SOCKET_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_SOCKET_NAME)

	#  6-Token #

LIB_TOKEN_NAME = token

LIB_TOKEN_PATH = $(PATH_SOURCE_CODE)6-Token/

INC_FLAGS += -I $(LIB_TOKEN_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_TOKEN_NAME)

	#  10-Exception #

LIB_EXCEPTION_NAME = exception

LIB_EXCEPTION_PATH = $(PATH_SOURCE_CODE)10-Exception/

INC_FLAGS += -I $(LIB_EXCEPTION_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_EXCEPTION_NAME)

	#  12-utils  #

LIB_UTILS_NAME = utils

LIB_UTILS_PATH = $(PATH_SOURCE_CODE)12-Utils/

INC_FLAGS += -I $(LIB_UTILS_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_UTILS_NAME)

	#  13-log  #

LIB_LOG_NAME = log

LIB_LOG_PATH = $(PATH_SOURCE_CODE)13-Log/

INC_FLAGS += -I $(LIB_LOG_PATH)$(LIB_INC_PATH)

LIB_FLAGS += -L $(LIB_BIN_PATH) -l $(LIB_LOG_NAME)

	#  OBJECTS  #

OBJ_PATH = $(BIN_PATH)Objects/

OBJ_NAME = $(SRC_NAME:.cpp=.o)

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
	
	#  FLAGS  #

CC = c++

CC_FLAGS = -pedantic -std=c++98  -Wall -Wextra -Werror

CL = rm -rf

LEAK = leaks -atExit --

LEAKS = valgrind --leak-check=full


	#  COLORS STR #

GREEN = "\x1b[32m""\x1b[M"

RED= "\x1b[31m""\x1b[M"

BLUE = "\x1b[34m""\x1b[M"

	#  COLORS  #

ENDCOL = \033[0m

REDS = \033[1;31m

YEL = \033[1;33m

ORG = \033[0;33m

GRN = \033[1;32m

DGRAY = \033[1;30m

BLU = \033[1;34m

	#  COMPILATION  #

all: $(BIN)
		@echo $(GREEN) Compilation $(PROJECT) is completed !!

$(OBJ_PATH)%.o:$(SRC_PATH)%.cpp
		@$(CC) $(CC_FLAGS) $(INC_FLAGS) -c $< -o $@
		@echo $(BLUE) $(notdir $@) is created !!

$(BIN): lib title directory $(OBJ)
		@$(CC) $(OBJ) $(INC_FLAGS) $(LIB_FLAGS) -o $(BIN_NAME)
		@echo $(BLUE) $(notdir $(BIN)) is created !!

run: all
		@./$(BIN)

test_filer: all
		@./$(BIN) -t

#HTTP = http://127.0.0.1:8081/
#curl: curl --http1.1 -v $(HTTP)

lib: utils log code type listen socket token exception config cli

cli:
		@$(MAKE) -C $(LIB_CLI_PATH)

code:
		@$(MAKE) -C $(LIB_CODE_PATH)

type:
		@$(MAKE) -C $(LIB_TYPE_PATH)

listen:
		@$(MAKE) -C $(LIB_LISTEN_PATH)

config:
		@$(MAKE) -C $(LIB_CONFIG_PATH)

socket:
		@$(MAKE) -C $(LIB_SOCKET_PATH)

exception:
		@$(MAKE) -C $(LIB_EXCEPTION_PATH)

token:
		@$(MAKE) -C $(LIB_TOKEN_PATH)

utils:
		@$(MAKE) -C $(LIB_UTILS_PATH)

log:
		@$(MAKE) -C $(LIB_LOG_PATH)

title:
		@echo $(GREEN)******************$(PROJECT)******************

directory: 	
		@mkdir -p $(OBJ_PATH) > /dev/null 2>&1 || true
		@echo $(BLUE) Binary $(PROJECT) directory created !!


clean: 
		@$(CL) $(OBJ)
		@$(MAKE) clean -C $(LIB_CLI_PATH)
		@$(MAKE) clean -C $(LIB_CODE_PATH)
		@$(MAKE) clean -C $(LIB_TYPE_PATH)
		@$(MAKE) clean -C $(LIB_LISTEN_PATH)
		@$(MAKE) clean -C $(LIB_CONFIG_PATH)
		@$(MAKE) clean -C $(LIB_SOCKET_PATH)
		@$(MAKE) clean -C $(LIB_UTILS_PATH)
		@$(MAKE) clean -C $(LIB_LOG_PATH)
		@echo $(RED) Object $(notdir $(OBJ)) is delete !

fclean: clean 
		@$(CL) $(BIN)
		@$(MAKE) fclean -C $(LIB_CLI_PATH)
		@$(MAKE) fclean -C $(LIB_CODE_PATH)
		@$(MAKE) fclean -C $(LIB_TYPE_PATH)
		@$(MAKE) fclean -C $(LIB_LISTEN_PATH)
		@$(MAKE) fclean -C $(LIB_CONFIG_PATH)
		@$(MAKE) fclean -C $(LIB_SOCKET_PATH)
		@$(MAKE) fclean -C $(LIB_UTILS_PATH)
		@$(MAKE) fclean -C $(LIB_LOG_PATH)
		@echo $(RED) Binary $(notdir $(BIN)) is delete !

finish:
		@$(CL) $(BIN_PATH)
		@$(CL) $(LIB_BIN_PATH)
		@echo $(RED) All $(PROJECT) is delete !

re:	fclean all

.PHONY :	all clean fclean finish re directory title
