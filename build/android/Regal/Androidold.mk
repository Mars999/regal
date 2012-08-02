LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Regal
LOCAL_ARM_MODE  := arm
LOCAL_CFLAGS    := -DANDROID=1 -Werror

REGAL_PATH      := $(LOCAL_PATH)/../../..

# src_files should not include LOCAL_PATH
REGAL_SRC_FILES := $(wildcard $(REGAL_PATH)/src/regal/*.cpp) $(REGAL_PATH)/src/mongoose/mongoose.c
REGAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%,%,$(REGAL_SRC_FILES))

REGAL_C_INCLUDES := $(REGAL_PATH)/include $(REGAL_PATH)/src/regal $(REGAL_PATH)/src/boost $(REGAL_PATH)/src/mongoose 

LOCAL_EXPORT_C_INCLUDES := $(REGAL_PATH)/include

LOCAL_C_INCLUDES := $(REGAL_C_INCLUDES)
LOCAL_SRC_FILES := $(REGAL_SRC_FILES)

#$(warning local-path= $(LOCAL_PATH) src= $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
