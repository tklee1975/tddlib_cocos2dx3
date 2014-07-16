LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPPFLAGS := -DENABLE_TDD

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

# define LOCAL_SRC_FILES & LOCAL_C_INCLUDES
CLASS_PATH :=../../Classes
include $(LOCAL_PATH)/Sources.mk

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# ??? 
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/Classes

include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,extensions)
$(call import-module,audio/android)
