#pragma once

#include "NeoFur.h"
#include "NeoFurComponentSceneProxy.h"
#include "GlobalShader.h"

#ifndef NO_COMPUTE_SHADERS


struct FNeoFurComputeShaderPerFrameData
{
    uint32_t ControlPointCount;
    uint32_t ShellCount;
    uint32_t TotalShellCount;
    float ShellDistance;
    float DeltaTime;
    float ShellFade;
    FVector LocalSpaceGravity;
    FMatrix TransformFromLastFrame;
    float VisibleLengthScale;
};

// FIXME: Redundant name.
class FNeoFurComputeShaderCS : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FNeoFurComputeShaderCS, Global);

public:

	// TODO: Make private?

	FShaderResourceParameter In_BoneMatrices;
	FShaderResourceParameter In_ControlPoints;
	FShaderResourceParameter In_OriginalMesh;
	FShaderResourceParameter In_MorphData;
	FShaderResourceParameter In_PhysicsProperties;

	FShaderResourceParameter Out_ControlPoints;
	FShaderResourceParameter Out_PostAnimVertexBuffer;

    FShaderResourceParameter In_PerFrameData;

	FNeoFurComputeShaderCS();
	explicit FNeoFurComputeShaderCS(const ShaderMetaType::CompiledShaderInitializerType &Initializer);

	static bool ShouldCache(EShaderPlatform Platform)
	{
		return RHISupportsComputeShaders(Platform);
	}

	virtual bool Serialize( FArchive& Ar ) override;

	static const TCHAR* GetSourceFilename();
	static const TCHAR* GetFunctionName();
};

#endif

