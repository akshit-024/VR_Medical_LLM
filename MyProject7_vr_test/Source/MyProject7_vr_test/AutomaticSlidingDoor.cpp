#include "AutomaticSlidingDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"

// Sets default values
AAutomaticSlidingDoor::AAutomaticSlidingDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    TriggerVolume->SetupAttachment(RootComponent);
    TriggerVolume->SetBoxExtent(FVector(200.0f, 200.0f, 100.0f));

    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AAutomaticSlidingDoor::OnOverlapBegin);
    TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AAutomaticSlidingDoor::OnOverlapEnd);

    bDoorIsOpen = false;
    bIsSliding = false;
    bPlayerInTrigger = false;
    SlideSpeed = 200.0f;
    DoorCloseDelay = 2.0f;
    SlideOffset = FVector(200.0f, 0.0f, 0.0f); // Example offset, change as needed
}

// Called when the game starts or when spawned
void AAutomaticSlidingDoor::BeginPlay()
{
    Super::BeginPlay();

    ClosedPosition = GetActorLocation();
    OpenPosition = ClosedPosition + SlideOffset;
}

// Called every frame
void AAutomaticSlidingDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsSliding)
    {
        FVector TargetPosition = bDoorIsOpen ? OpenPosition : ClosedPosition;
        FVector CurrentPosition = GetActorLocation();
        FVector NewPosition = FMath::VInterpConstantTo(CurrentPosition, TargetPosition, DeltaTime, SlideSpeed);

        if (FVector::Dist(NewPosition, TargetPosition) < 1.0f)
        {
            NewPosition = TargetPosition;
            bIsSliding = false;
        }

        SetActorLocation(NewPosition);
    }

    if (!bPlayerInTrigger && bDoorIsOpen && (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay))
    {
        bDoorIsOpen = false;
        bIsSliding = true;
    }
}

void AAutomaticSlidingDoor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        bPlayerInTrigger = true;
        if (!bDoorIsOpen)
        {
            bDoorIsOpen = true;
            bIsSliding = true;
        }
    }
}

void AAutomaticSlidingDoor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this))
    {
        bPlayerInTrigger = false;
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
}
