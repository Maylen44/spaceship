#ifndef IPRODUCER_H
#define IPRODUCER_H

#include "IPackageElement.h"

enum PackageProducer
{
	PackageProducer_AssetManager
};

class IProducer
{
public:
	IProducer(PackageProducer type)
	{
		MessageController::instance()->addProducer(&std::make_pair(type, this));
	}
	virtual ~IProducer() = default;
};
#endif //IPRODUCER_H