#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "IPackageElement.h"

enum PackageReceiver
{
	PackageReceiver_Player,
	PackageReceiver_Enemy
};

class IObserver
{
public:
	IObserver(PackageReceiver type)
	{
		MessageController::instance()->addReceiver(&std::make_pair(type, this));
	}
	virtual ~IObserver() = default;
};
#endif //IOBSERVER_H