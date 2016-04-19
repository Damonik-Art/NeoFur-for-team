// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!     DO NOT EDIT THIS FILE UNLESS YOU KNOW WHAT YOU'RE DOING      !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//   It is generated from this file:
//     Source_Before_Replacements/./NeoFur/Public/NeoFur.h
//   Changes to this file will be overwritten. To change this file,
//   modify the file specified above and re-run RunPreprocessor.bsh.
//
//   Generation parameters:
//     NEO_FULLVERSION=1
//     NEO_FBX=1
//

// Some copyright should be here...

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

class FNeoFurModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(NeoFur, Log, All);
