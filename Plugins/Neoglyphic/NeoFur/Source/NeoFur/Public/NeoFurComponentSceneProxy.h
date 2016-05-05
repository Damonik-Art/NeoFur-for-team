#pragma once

#include "NeoFur.h"

#include "LocalVertexFactory.h"

#include "NeoFurComputeShader.h"
#include "NeoFurComponentSceneProxy.generated.h"

class UNeoFurAsset;

const float NeoFurPhysicsParameters_Default_VelocityInfluence            = 1.0f;
const float NeoFurPhysicsParameters_Default_SpringLengthStiffness        = 250.0f;
const float NeoFurPhysicsParameters_Default_SpringAngleStiffness         = 1200.0f;
const float NeoFurPhysicsParameters_Default_SpringDampeningMultiplier    = 0.8f;
const float NeoFurPhysicsParameters_Default_GravityInfluence             = 0.8f;
const float NeoFurPhysicsParameters_Default_AirResistanceMultiplier      = 0.75f;
const float NeoFurPhysicsParameters_Default_MaxStretchDistanceMultiplier = 2.0f;
const float NeoFurPhysicsParameters_Default_MaxRotationFromNormal        = 60.0f;
const float NeoFurPhysicsParameters_Default_RadialForceInfluence         = 1.0f;
const float NeoFurPhysicsParameters_Default_WindInfluence                = 1.0f;
const float NeoFurPhysicsParameters_Default_Bendiness                    = 1.0f;

struct FNeoFurProxyPrivateData;

USTRUCT()
struct FNeoFurPhysicsParameters
{
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!    IF ANY OF THIS STRUCTURE CHANGES, YOU MUST UPDATE THE OFFSETS IN NeoFurComputeShader.usf!        !!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta=(ClampMin = "0.0", ClampMax = "1.0"))
	float VelocityInfluence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta = (ClampMin = "0.0"))
	float SpringLengthStiffness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta = (ClampMin = "0.0"))
	float SpringAngleStiffness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float SpringDampeningMultiplier;

	// FIXME: Make this a vector, so we can have gravity point in whatever direction we want.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics")
	float GravityInfluence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AirResistanceMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta = (ClampMin = "1.0"))
	float MaxStretchDistanceMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float MaxRotationFromNormal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta = (ClampMin = "0.0"))
	float RadialForceInfluence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta = (ClampMin = "0.0"))
	float WindInfluence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur Physics", meta = (ClampMin = "0.0", DisplayName = "Bend Exponent"))
	float Bendiness;

	FNeoFurPhysicsParameters() :
		VelocityInfluence            (NeoFurPhysicsParameters_Default_VelocityInfluence),
		SpringLengthStiffness        (NeoFurPhysicsParameters_Default_SpringLengthStiffness),
		SpringAngleStiffness         (NeoFurPhysicsParameters_Default_SpringAngleStiffness),
		SpringDampeningMultiplier    (NeoFurPhysicsParameters_Default_SpringDampeningMultiplier),
		GravityInfluence             (NeoFurPhysicsParameters_Default_GravityInfluence),
		AirResistanceMultiplier      (NeoFurPhysicsParameters_Default_AirResistanceMultiplier),
		MaxStretchDistanceMultiplier (NeoFurPhysicsParameters_Default_MaxStretchDistanceMultiplier),
		MaxRotationFromNormal        (NeoFurPhysicsParameters_Default_MaxRotationFromNormal),
		RadialForceInfluence         (NeoFurPhysicsParameters_Default_RadialForceInfluence),
		WindInfluence                (NeoFurPhysicsParameters_Default_WindInfluence),
		Bendiness                    (NeoFurPhysicsParameters_Default_Bendiness)
	{
	}

	const FNeoFurPhysicsParameters &operator=(const FNeoFurPhysicsParameters &Other)
	{
		VelocityInfluence            = Other.VelocityInfluence;
		SpringLengthStiffness        = Other.SpringLengthStiffness;
		SpringAngleStiffness         = Other.SpringAngleStiffness;
		SpringDampeningMultiplier    = Other.SpringDampeningMultiplier;
		GravityInfluence             = Other.GravityInfluence;
		AirResistanceMultiplier      = Other.AirResistanceMultiplier;
		MaxStretchDistanceMultiplier = Other.MaxStretchDistanceMultiplier;
		MaxRotationFromNormal        = Other.MaxRotationFromNormal;
		RadialForceInfluence         = Other.RadialForceInfluence;
		WindInfluence                = Other.WindInfluence;
		Bendiness                    = Other.Bendiness;
		return *this;
	}
};

const int32 NeoFurFramePhysicsInputsNumLocalForces = 4;
struct FNeoFurFramePhysicsInputs
{
	struct {
		FVector Origin;
		float Radius;
		float Strength;
	} LocalForces[NeoFurFramePhysicsInputsNumLocalForces];

	FVector WindVector;
	float WindGustsAmount;
	int32 NumForcesThisFrame;

	FNeoFurFramePhysicsInputs()
	{
		NumForcesThisFrame = 0;
		memset(LocalForces, 0, sizeof(LocalForces));
		WindVector = FVector(0.0f, 0.0f, 0.0f);
		WindGustsAmount = 0.0f;
	}
};

class FNeoFurComponentSceneProxy : public FPrimitiveSceneProxy
{
public:

	FNeoFurComponentSceneProxy(
		const UPrimitiveComponent* InComponent,
		FMaterialRenderProxy *InMaterialRenderProxy,
		int32 InShellCount,
		float InShellDistance,
		UNeoFurAsset *FurAsset,
		bool bForceCPU     = false,
		bool bSkipSim      = false,
		bool bSkipRender   = false,
		FName ResourceName = NAME_None,
		ERHIFeatureLevel::Type FeatureLevel = ERHIFeatureLevel::Type::SM5);

	virtual ~FNeoFurComponentSceneProxy();

	virtual uint32 GetMemoryFootprint(void) const override;

	virtual void GetDynamicMeshElements(
		const TArray<const FSceneView*>& Views,
		const FSceneViewFamily& ViewFamily,
		uint32 VisibilityMap,
		class FMeshElementCollector& Collector) const override;

	virtual void CreateRenderThreadResources() override;

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const /* override */ ;
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) /* override */ ;


	// These functions handle initial buffer creation, and copying of
	// skinning data from the parent skinned mesh's vertex buffer.
	typedef struct FNeoFurComponentSceneProxyGenerateCommand FNeoFurComponentSceneProxyGenerateCommand;
	void GenerateBuffers(UNeoFurAsset *FurAsset);

	void GenerateBuffers_Renderthread_CPU(
		FRHICommandListImmediate &RHICmdList,
		FNeoFurComponentSceneProxyGenerateCommand *Command);

	void SetActiveShellCount(int32 NewActiveShellCount, float ShellFade);
	void SetShellDistance(float InDistance);
    void SetVisibleLengthScale(float InVisibleLengthScale);

	struct MorphDataVertexType
	{
		FVector Offset;
		FVector Normal;
	};

	// Note: This takes ownership of BoneMats and delete[]s it in the render
	// thread.
	void RunSimulation(
		const FTransform &RelativeTransformSinceLastFrame,
		float DeltaTime,
		const FVector &LocalSpaceGravity,
		FMatrix *BoneMats, int32 NumBoneMats,
		MorphDataVertexType *IncomingMorphData);

	void RunSimulation_Renderthread(
		FRHICommandListImmediate &RHICmdList,
		const FTransform &RelativeTransformSinceLastFrame,
		float DeltaTime,
		const FVector &LocalSpaceGravity,
		FMatrix *BoneMats, int32 NumBoneMats,
		MorphDataVertexType *IncomingMorphData);

	void RunSimulation_Renderthread_CPU(
		const FTransform &RelativeTransformSinceLastFrame,
		float DeltaTime,
		const FVector &LocalSpaceGravity,
		FMatrix *BoneMats,
		MorphDataVertexType *IncomingMorphData);

#ifndef NO_COMPUTE_SHADERS
	void RunSimulation_Renderthread_GPU(
		const FTransform &RelativeTransformSinceLastFrame,
		float DeltaTime,
		const FVector &LocalSpaceGravity,
		FMatrix *BoneMats, int32 NumBoneMats,
		MorphDataVertexType *IncomingMorphData,
		FRHICommandListImmediate &RHICmdList);
#endif

	void SetPhysicsParameters(
		const FNeoFurPhysicsParameters &Params,
		const FNeoFurFramePhysicsInputs &AccumulatedForces);

    void SetMaterialProxy(FMaterialRenderProxy *MaterialProxy);

	bool GetForceSimulateOnCPU() const;

	// If this structure ever changes in any way ever, you must update the
	// ANIMVERTEXTYPE_OFFSET_* macros in NeoFurComputeShader.usf.
	// FIXME: Maybe move this type to UNeoFurAsset.
	struct VertexType
	{
		FVector Position;
		FVector TanX;
		FVector TanZ;
		FVector2D UVs[MAX_TEXCOORDS];

		uint8 InfluenceBones[4];
		uint8 InfluenceWeights[4];

		FVector CombedDirectionAndLength;

		friend FArchive& operator<<(FArchive& Ar, VertexType& V)
		{
			Ar << V.Position;
			Ar << V.TanX;
			Ar << V.TanZ;

			for(int32 i = 0; i < MAX_TEXCOORDS; i++) {
				Ar << V.UVs[i];
			}

			for(int32 i = 0; i < 4; i++) {
				Ar << V.InfluenceBones[i];
				Ar << V.InfluenceWeights[i];
			}

			Ar << V.CombedDirectionAndLength;

			return Ar;
		}
	};

	// This structure has decoding and encoding code in
	// NeoFurComputeShader.usf. If it ever changes, update those.
	struct ControlPointVertexType
	{
		FVector Position;
		FVector Velocity;
	};

private:

	bool ShouldUseGPUShader() const;

    FNeoFurProxyPrivateData *PrivateData;
};

