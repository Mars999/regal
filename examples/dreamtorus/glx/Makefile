
all: dreamtorus

clean:
	rm -f dreamtorus
	rm -rf obj

REGAL_DIR := ../../../../regal
REGAL_SRC := $(wildcard $(REGAL_DIR)/gen/*.cpp $(REGAL_DIR)/src/*.cpp)
REGAL_INC := $(REGAL_DIR)/gen $(REGAL_DIR)/src

SHARED_DIR := ../src
SHARED_SRC := $(wildcard $(SHARED_DIR)/*.cpp)
SHARED_INC := $(SHARED_DIR)

LOCAL_SRC := $(wildcard *.cpp) 

MY_SRC := $(REGAL_SRC) $(LOCAL_SRC) $(SHARED_SRC)
MY_SRC_DIRS := $(sort $(dir $(MY_SRC)))

MY_OBJ := $(MY_SRC)
MY_OBJ := $(patsubst %.cpp, obj$(CURDIR)/%.o, $(MY_OBJ))
MY_OBJ := $(patsubst %.c, obj$(CURDIR)/%.o, $(MY_OBJ))
MY_OBJ_DIRS := $(sort $(dir $(MY_OBJ)))

MY_INC := $(REGAL_INC) $(SHARED_INC)
MY_CMD_INC := $(patsubst %, -I %, $(MY_INC))

obj$(CURDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	g++ -g -c -o $@ $(MY_CMD_INC) $<
	@echo $@ ---- $<

dreamtorus: $(MY_OBJ)
	g++ -g -o $@ $(MY_OBJ) -lX11 -lpthread

