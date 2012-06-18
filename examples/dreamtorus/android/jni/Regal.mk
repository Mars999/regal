LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Regal
LOCAL_CFLAGS    := -Werror
LOCAL_ARM_MODE  := arm

REGAL_DIR       := ../../..
REGAL_SRC       := $(REGAL_DIR)/src/regal

REGAL_SRC_FILES := $(wildcard $(REGAL_SRC)/*.cpp) 

LOCAL_C_INCLUDES := $(REGAL_DIR)/include $(REGAL_DIR)/src/boost $(REGAL_SRC)
LOCAL_SRC_FILES := $(REGAL_SRC_FILES)
LOCAL_CFLAGS    := -DANDROID=1 

include $(BUILD_STATIC_LIBRARY)
