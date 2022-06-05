#include "LyraLogChannels.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY(LogLyra);
DEFINE_LOG_CATEGORY(LogLyraExperience);

LYRAGAME_API FString GetClientServerContextString(UObject* ContextObject /*= nullptr*/)
{
	ENetRole Role = ROLE_None;

	if (AActor* Actor = Cast<AActor>(ContextObject))
	{
		Role = Actor->GetLocalRole();
	}
	else if (UActorComponent* Component = Cast<UActorComponent>(ContextObject))
	{
		Role = Component->GetOwnerRole();
	}

	if (Role != ROLE_None)
	{
		return (Role == ROLE_Authority) ? TEXT("Server") : TEXT("Client");
	}
	else
	{

	}

	return TEXT("[]");
}
