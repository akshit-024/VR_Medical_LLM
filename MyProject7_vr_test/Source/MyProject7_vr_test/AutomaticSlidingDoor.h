#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutomaticSlidingDoor.generated.h"

UCLASS()
class MYPROJECT7_VR_TEST_API AAutomaticSlidingDoor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AAutomaticSlidingDoor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerVolume;

    UPROPERTY(EditAnywhere)
    FVector SlideOffset;

    UPROPERTY(EditAnywhere)
    float SlideSpeed;

    UPROPERTY(EditAnywhere)
    float DoorCloseDelay;

private:
    FVector ClosedPosition;
    FVector OpenPosition;
    bool bDoorIsOpen;
    bool bIsSliding;
    bool bPlayerInTrigger;
    float LastDoorOpenTime;

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
