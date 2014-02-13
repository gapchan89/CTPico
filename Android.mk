LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/Cats/CatsManager.cpp \
				   ../../Classes/Cats/BaseCat.cpp \
				   ../../Classes/Character/Character.cpp \
				   ../../Classes/Character/CharacterAI.cpp \
				   ../../Classes/Levels/CatSpawnScript.cpp \
				   ../../Classes/Levels/CatSpawnSet.cpp \
				   ../../Classes/Levels/CutScene.cpp \
				   ../../Classes/Levels/Level.cpp \
				   ../../Classes/Levels/LevelLoader.cpp \
				   ../../Classes/Map/GameMap.cpp \
				   ../../Classes/Supporting/CCBlade.cpp \
				   ../../Classes/GameManager.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/NinjaCat.cpp \
				   
			   
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
