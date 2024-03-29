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

	#  BINARY  #

BIN_PATH = ../Bin/

EXEC_PATH = ../

BIN_NAME = $(PROJECT)

BIN = $(addprefix $(BIN_PATH),$(BIN_NAME))
EXEC = $(addprefix $(EXEC_PATH),$(BIN_NAME))

	#  INCLUDES  #

INC_PATH = Includes

INC_FLAGS = -I $(INC_PATH)

	#  SOURCES  #

SRC_PATH = Sources/

SRC_NAME = $(notdir $(wildcard Sources/*.cpp))

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

	#  OBJECTS  #

OBJ_PATH = $(BIN_PATH)Objects/

OBJ_NAME = $(SRC_NAME:.cpp=.o)

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
	
	#  FLAGS  #

CC = c++

CC_FLAGS = -pedantic -std=c++98 -Wall -Wextra -Werror -g

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

$(BIN): title directory $(OBJ)
		@$(CC) $(OBJ) $(INC_FLAGS) -o $(EXEC)
		@echo $(BLUE) $(notdir $(BIN)) is created !!

run: all
		@./$(BIN)

#HTTP = http://127.0.0.1:8081/
#curl: curl --http1.1 -v $(HTTP)

title:
		@echo $(GREEN)******************$(PROJECT)******************

directory: 	
		@mkdir -p $(OBJ_PATH) > /dev/null 2>&1 || true
		@echo $(BLUE) Binary $(PROJECT) directory created !!


clean: 
		@$(CL) $(OBJ)
		@echo $(RED) Object $(notdir $(OBJ)) is delete !

fclean: clean 
		@$(CL) $(BIN)
		@echo $(RED) Binary $(notdir $(BIN)) is delete !

finish:
		@$(CL) $(BIN_PATH)
		@echo $(RED) All $(PROJECT) is delete !

re:	fclean all

.PHONY :	all clean fclean finish re directory title
