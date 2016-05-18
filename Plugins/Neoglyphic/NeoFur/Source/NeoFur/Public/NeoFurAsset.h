#pragma once

#include "NeoFur.h"
#include "NeoFurComponentSceneProxy.h"
#include "NeoFurAsset.generated.h"

UCLASS()
class NEOFUR_API UNeoFurAsset : public UObject
{
    GENERATED_UCLASS_BODY()

public:

    // Skeletal Mesh to use as Fur's Growth Mesh.
    UPROPERTY(
        EditAnywhere,
        Category = "Fur",
        meta = (DisplayName = "Growth Mesh Skeletal"))
    USkeletalMesh *SkeletalMesh;

    // Static Mesh to use as Fur's Growth Mesh.
    UPROPERTY(
        EditAnywhere,
        Category = "Fur",
        meta = (DisplayName = "Growth Mesh Static"))
    UStaticMesh *StaticMesh;

    // TODO: Remove me. Replaced with SplineDataFbxFilePath.
    UPROPERTY()
    FString FbxSourceFilePath;

    // This is the path to the FBX spline data, relative to the game directory.
    UPROPERTY(
        VisibleAnywhere,
        BlueprintReadOnly, Category = "Fur", meta = (DisplayName = "Spline Data FBX Path Relative"))
    FString FbxSourceFilePathRelative;

    // Material ID to limit the Growth Mesh's usage to.
    UPROPERTY(
        EditAnywhere,
        Category = "Fur",
        BlueprintReadOnly, meta = (DisplayName = "Growth Mesh Material ID"))
    int32 MaterialId;

    UPROPERTY()
    int32 Version;

    // Transformation to apply to incoming fur spline data, in case it doesn't
    // line up correctly at first.
    UPROPERTY(
        EditAnywhere,
        BlueprintReadOnly, Category = "Fur")
    FTransform SplineTransform;

    // Path to an FBX file containing spline data to affect the shape of the
    // fur.
    UPROPERTY(
        EditAnywhere,
        BlueprintReadOnly, Category = "Fur", meta=(RelativeToGameContentDir, FilePathFilter="fbx"))
    FFilePath SplineDataFbxFilePath;

    // Morph target to use for the position of the outer shell layer.
    UPROPERTY(
        EditAnywhere,
        BlueprintReadOnly, Category = "Fur")
    FString MorphTargetName;

    // Generated from SkeletalMesh.
    TArray<FNeoFurComponentSceneProxy::VertexType> Vertices;
    TArray<uint32> Indices;

    // Generated from spline data in the FBX file.
    TArray< TArray<FVector> > SplineLines;

    void Serialize(FArchive &Ar) override;

#if WITH_EDITOR
    void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif

private:

    void RegenerateFromSkeletalMesh();

};
