#include "MyActor.h"
#include "Engine/Texture2D.h"
#include "Runtime/Core/Public/Misc/Base64.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Engine/Public/ImageUtils.h"
#include "Engine/Engine.h"

AMyActor::AMyActor()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    WebSocket = FWebSocketsModule::Get().CreateWebSocket(WebSocketUrl);

    if (WebSocket.IsValid())
    {
        WebSocket->OnConnected().AddLambda([]() {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("WebSocket Connected"));
            });

        WebSocket->OnConnectionError().AddLambda([](const FString& Error) {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("WebSocket Connection Error: ") + Error);
            });

        WebSocket->OnMessage().AddUObject(this, &AMyActor::OnReceiveImage);

        WebSocket->Connect();
    }
    else
    {
        DisplayMessageOnScreen(TEXT("WebSocket is not valid"), FColor::Red, 5.0f);
    }
    if (BaseMaterial)
    {
        DynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
        if (MeshComponent)
        {
            MeshComponent->SetMaterial(0, DynamicMaterialInstance);
        }
    }
}

void AMyActor::OnReceiveImage(const FString& Base64ImageData)
{
    DisplayMessageOnScreen(TEXT("Received Image Data"), FColor::Green, 5.0f);

    DynamicTexture = Base64_ToImage(Base64ImageData);

    if (DynamicMaterialInstance && DynamicTexture)
    {
        DynamicMaterialInstance->SetTextureParameterValue(TEXT("VideoTexture"), DynamicTexture);
        DisplayMessageOnScreen(TEXT("Applied Texture to Material"), FColor::Green, 1.0f);
    }
    else
    {
        DisplayMessageOnScreen(TEXT("Failed to Apply Texture to Material"), FColor::Red, 1.0f);
    }
}

UTexture2D* AMyActor::Base64_ToImage(const FString& Source)
{
    TArray<uint8> DataBuffer;
    FString Left, Right;

    // Attempt to split the data URL prefix
    bool bHasPrefix = Source.Split(TEXT(","), &Left, &Right);
    if (!bHasPrefix)
    {
        Right = Source;  // If no prefix, use the whole string
    }

    bool bIsDecode = FBase64::Decode(Right, DataBuffer);
    if (bIsDecode)
    {
        return CreateBitTextureAtRuntime(DataBuffer);
    }
    else
    {
        DisplayMessageOnScreen(TEXT("Failed to Decode Base64 String"), FColor::Red, 1.0f);
        return nullptr;
    }
}

UTexture2D* AMyActor::CreateBitTextureAtRuntime(const TArray<uint8>& BGRA8PixelData)
{
    UTexture2D* Texture = FImageUtils::ImportBufferAsTexture2D(BGRA8PixelData);
    if (Texture)
    {
        Texture->MipGenSettings = TMGS_NoMipmaps;
        Texture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
        Texture->SRGB = false;
        Texture->Filter = TextureFilter::TF_Nearest;
        Texture->UpdateResource();
        DisplayMessageOnScreen(TEXT("Texture Created Successfully"), FColor::Green, 1.0f);
    }
    else
    {
        DisplayMessageOnScreen(TEXT("Failed to Create Texture"), FColor::Red, 1.0f);
    }
    return Texture;
}

void AMyActor::DisplayMessageOnScreen(const FString& Message, FColor Color, float Duration)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
    }
}
