LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := gtthread.c
LOCAL_MODULE := libgtthread
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)