#include "LyraAssetManagerStartupJob.h"
#include "LyraLogChannels.h"

TSharedPtr<FStreamableHandle> FLyraAssetManagerStartupJob::DoJob() const
{
	TSharedPtr<FStreamableHandle> Handle;

	JobFunc(*this, Handle);

	if (Handle.IsValid())
	{
		// 一些代理,先不处理
	}

	return Handle;
}

