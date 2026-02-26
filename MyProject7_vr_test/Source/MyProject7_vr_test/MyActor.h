#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Core/Public/Misc/Base64.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MyActor.generated.h"

UCLASS()
class MYPROJECT7_VR_TEST_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    AMyActor();

protected:
    virtual void BeginPlay() override;

private:
    TSharedPtr<IWebSocket> WebSocket;
    UTexture2D* DynamicTexture;
    UPROPERTY(EditAnywhere, Category = "WebSocket")
    FString WebSocketUrl = TEXT("ws://localhost:8765");
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* MeshComponent;
    UPROPERTY(EditAnywhere)
    UMaterialInterface* BaseMaterial;
    UMaterialInstanceDynamic* DynamicMaterialInstance;

    void OnReceiveImage(const FString& Base64ImageData);
    UTexture2D* Base64_ToImage(const FString& Source);
    UTexture2D* CreateBitTextureAtRuntime(const TArray<uint8>& BGRA8PixelData);
    void DisplayMessageOnScreen(const FString& Message, FColor Color, float Duration);
};
