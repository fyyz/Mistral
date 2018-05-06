CXX                            = g++ -std=c++11
CXXFLAGS                       = -Wall -I./src -I./third_party
LDFLAGS                        = -lboost_system

SRC_DIR                        = ./src:./src/core:./src/http:./src/http/v1:./src/http/ssl:./third_party/rapidjson:./third_party/utf8
OBJ_DIR                        = ./obj
BIN_DIR                        = ./bin

vpath %.cpp                    $(SRC_DIR)
.PHONY                         : clean

default                        : $(BIN_DIR)/mistral

$(BIN_DIR)/mistral             :$(OBJ_DIR)/mistral_config.o \
                                $(OBJ_DIR)/mistral_log.o \
                                $(OBJ_DIR)/mistral_listener.o \
                                $(OBJ_DIR)/mistral_router.o \
                                $(OBJ_DIR)/mistral_server.o \
                                $(OBJ_DIR)/mistral_request_v1.o \
                                $(OBJ_DIR)/mistral_response_v1.o \
                                $(OBJ_DIR)/mistral_session_v1.o \
                                $(OBJ_DIR)/main.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o               : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean :
	-rm -rf $(OBJ_DIR)/*
	-rm -rf $(BIN_DIR)/*

