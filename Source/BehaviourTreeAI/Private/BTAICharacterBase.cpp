#include "BTAICharacterBase.h"

#include "TaggedWidget.h"
#include "BehaviourTreeAI/Const.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


ABTAICharacterBase::ABTAICharacterBase() :
	RightFistColBox{CreateDefaultSubobject<UBoxComponent>(TEXT("RightFistColBox"))}
{
	PrimaryActorTick.bCanEverTick = true;

	if (RightFistColBox)
	{
		RightFistColBox->SetBoxExtent(defs::RightFistColBoxSize);
		FAttachmentTransformRules const Rules{
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		false};
		RightFistColBox->AttachToComponent(GetMesh(), Rules, defs::RightFistSocketName);
		RightFistColBox->SetRelativeLocation(defs::RightFistColBoxPos);
	}
}
void ABTAICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	RightFistColBox->SetCollisionProfileName("Fist");
	RightFistColBox->OnComponentBeginOverlap.AddDynamic(this, &ABTAICharacterBase::OnTagOverlapBegin);
	RightFistColBox->OnComponentEndOverlap.AddDynamic(this, &ABTAICharacterBase::OnTagOverlapEnd);
}

void ABTAICharacterBase::OnTagOverlapBegin(UPrimitiveComponent* const OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* const OtherComp, int32 const OtherBodyIndex, bool const bFromSweep,
	FHitResult const& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}
	if (auto const enemy = Cast<ABTAICharacterBase>(OtherActor))
	{
		this->SetIsTagged(false);
		enemy->SetIsTagged(true);
	}
}

void ABTAICharacterBase::OnTagOverlapEnd(UPrimitiveComponent* const OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* const OtherComp, int32 const OtherBodyIndex)
{
}

void ABTAICharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (TaggedWidgetInstance)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			FVector HeadLocation = this->GetActorLocation() + FVector(0.f, 0.f, 90.f); // Adjust Z as needed
			FVector2D ScreenPosition;
			bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(PC, HeadLocation, ScreenPosition);
			if (bIsOnScreen)

				ScreenPosition.Y -= 50.0f;

				TaggedWidgetInstance->SetPositionInViewport(ScreenPosition);

				TaggedWidgetInstance->SetAlignmentInViewport(FVector2D(.5f, 1.0f));
			}
			else
			{

			}
		}
	}
void ABTAICharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ABTAICharacterBase::GetIsTagged() const
{
		return bIsTagged;
}

void ABTAICharacterBase::SetIsTagged(bool isTagged)
{
	bIsTagged = isTagged;
	if (isTagged){ ShowTaggedWidget();}
	else { HideTaggedWidget(); }
}
void ABTAICharacterBase::ShowTaggedWidget(){
	if (!WidgetClass || TaggedWidgetInstance)
		return;

	TaggedWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	if (TaggedWidgetInstance)
	{
		TaggedWidgetInstance->AddToViewport();
	}

}

void ABTAICharacterBase::HideTaggedWidget()
{
	if (TaggedWidgetInstance)
	{
		TaggedWidgetInstance->RemoveFromParent();
		TaggedWidgetInstance = nullptr;
	}
}

void ABTAICharacterBase::AttackStart() const
{
	RightFistColBox->SetNotifyRigidBodyCollision(true);
}

void ABTAICharacterBase::AttackEnd() const
{
	RightFistColBox->SetNotifyRigidBodyCollision(false);
}

