LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Regal
LOCAL_CFLAGS    := -Werror
LOCAL_ARM_MODE  := arm

REGAL_DIR       := ../../..
REGAL_SRC       := $(REGAL_DIR)/src

REGAL_SRC_FILES := $(wildcard $(LOCAL_PATH)/$(REGAL_SRC)/regal/*.cpp) $(LOCAL_PATH)/$(REGAL_SRC)/mongoose/mongoose.c
REGAL_C_INCLUDES := $(REGAL_DIR)/include $(REGAL_SRC)/regal $(REGAL_SRC)/boost $(REGAL_SRC)/mongoose 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(REGAL_DIR)/include

LOCAL_C_INCLUDES := $(patsubst %,$(LOCAL_PATH)/%, $(REGAL_C_INCLUDES))
LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%,%,$(REGAL_SRC_FILES))
LOCAL_CFLAGS    := -DANDROID=1 

$(warning local-path= $(LOCAL_PATH) src= $(LOCAL_SRC_FILES))

include $(BUILD_STATIC_LIBRARY)
