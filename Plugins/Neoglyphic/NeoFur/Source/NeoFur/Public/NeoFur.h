#pragma once

#include "Engine.h"
#include "ModuleManager.h"

#if PLATFORM_HTML5
#define NO_COMPUTE_SHADERS 1
#endif

#if PLATFORM_ANDROID
#define NO_COMPUTE_SHADERS 1
#endif

#if PLATFORM_IOS
#define NO_COMPUTE_SHADERS 1
#endif

#if PLATFORM_MAC
#define NO_COMPUTE_SHADERS 1
#endif

#ifndef NEOFUR_FBX
#define NEOFUR_FBX 0
#endif

class FNeoFurModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(NeoFur, Log, All);
