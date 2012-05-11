LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Regal
LOCAL_CFLAGS    := -Werror
LOCAL_ARM_MODE  := arm

REGAL_DIR       := ../../..
REGAL_GEN       := $(REGAL_DIR)/gen
REGAL_SRC       := $(REGAL_DIR)/src

REGAL_SRC_FILES := $(wildcard $(REGAL_SRC)/*.cpp) $(wildcard $(REGAL_GEN)/*.cpp)

LOCAL_C_INCLUDES := $(REGAL_GEN) $(REGAL_SRC)
LOCAL_SRC_FILES := $(REGAL_SRC_FILES)
LOCAL_CFLAGS    := -DANDROID=1 

include $(BUILD_STATIC_LIBRARY)
