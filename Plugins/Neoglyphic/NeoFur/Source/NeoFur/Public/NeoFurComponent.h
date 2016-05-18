#pragma once

#include "NeoFur.h"
#include "NeoFurComponentSceneProxy.h"
#include "NeoFurComponent.generated.h"

UCLASS(
    Blueprintable,
    BlueprintType,
    meta=(BlueprintSpawnableComponent),
    ClassGroup=(Neoglyphic), EditInlineNew)
class UNeoFurComponent : public UPrimitiveComponent
{
	GENERATED_UCLASS_BODY()
public:

	virtual FPrimitiveSceneProxy *CreateSceneProxy() override;

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NeoFur")
	UMaterialInterface *Material;

	UPROPERTY(EditAnywhere, Category = "NeoFur")
	UNeoFurAsset *FurAsset;

	// Note: Do not make ShellCount and ShellDistance writable by Blueprints.
	// Make Blueprint-accessible functions for writing to them so we can
	// properly adjust the shells on the proxy as a result of the change.

	// Number of shell levels to use. Higher numbers will incur performance and
	// memory costs.
	UPROPERTY(EditAnywhere, Category = "NeoFur", BlueprintReadOnly)
	int32 ShellCount;

	UPROPERTY(EditAnywhere, Category = "NeoFur", BlueprintReadOnly)
	float ShellDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"), Category = "NeoFur")
	float LODStartDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"), Category = "NeoFur")
	float LODEndDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"), Category = "NeoFur")
	int32 LODMinimumShellCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"), Category = "NeoFur")
	float MaximumDistanceFromCamera;

    UPROPERTY(EditAnywhere, Category = "NeoFur", BlueprintReadOnly)
    float VisibleLengthScale;

	// TODO: Hook this up to the scene proxy. Make a value that represents "not
	// using it" or using some vertex color channel instead.
	UPROPERTY()
	int32 ShellOffsetTextureCoordinateIndex;

	// We can use this any time we want to teleport around and freeze the state
	// of the fur so it doesn't stretch a long distance. Updating the current
	// transform effectively cuts off any physics changes as a result of world
	// movement that have happened since last frame.
	void UpdateLastFrameTransform();

	// TODO: Make a modification function for this that sends it off to the scene proxy.
	UPROPERTY(EditAnywhere, Category = "NeoFur")
	FNeoFurPhysicsParameters FurPhysicsParameters;

	// Realtime physics sim modification (without causing a mesh rebuild).
	// ------------------------------------------------------------------------

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NeoFurPhysics")
	const FNeoFurPhysicsParameters GetFurPhysicsParameters() const;

	UFUNCTION(BlueprintCallable, Category = "NeoFurPhysics")
	void SetFurPhysicsParameters(const FNeoFurPhysicsParameters &Parameters);

	void UpdatePhysicsParametersInProxy();

	UFUNCTION(BlueprintCallable, Category = "NeoFurPhysics")
	void SetShellDistance(float NewDistance);

	UFUNCTION(BlueprintCallable, Category = "NeoFurPhysics")
	void SetVisibleLengthScale(float NewVisibleLengthScale);

	UPROPERTY(EditAnywhere, Category = "NeoFur")
    float ActiveShellCountScale;

	// Debugging features
	// ------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, Category = "NeoFurDebug")
	bool bForceCPUSimulation;

	UPROPERTY(EditAnywhere, Category = "NeoFurDebug")
	bool bSkipSimulation;

	UPROPERTY(EditAnywhere, Category = "NeoFurDebug")
	bool bSkipRendering;

	UPROPERTY(EditAnywhere, Category = "NeoFurDebug")
	bool bDrawSplines;

	// USceneComponent stuff
	// ------------------------------------------------------------------------

	// FIXME: Maybe we should use PostPhysicsTick() instead?
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void AddRadialForce(FVector Origin, float Radius, float Strength, enum ERadialImpulseFalloff Falloff, bool bAccelChange = false) override;
	virtual void AddRadialImpulse(FVector Origin, float Radius, float Strength, enum ERadialImpulseFalloff Falloff, bool bAccelChange = false) override;
	virtual class UBodySetup* GetBodySetup() override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif

	UPROPERTY(Transient)
	class UBodySetup *BodySetup;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "NeoFur")
	int32 ActiveShellCount;

	UFUNCTION(BlueprintCallable, Category = "NeoFurDebug", meta = (WorldContext = "WorldContextObject"))
	static int32 GetTotalActiveShellCount(UObject *WorldContextObject);

private:

	USkinnedMeshComponent *FindSkinnedMeshParent() const;
	UStaticMeshComponent *FindStaticMeshParent() const;
	FTransform LastFrameTransform;

	FNeoFurFramePhysicsInputs AccumulatedForces;


};
