#ifndef IPRODUCER_H
#define IPRODUCER_H

class IProducer
{
public:
	virtual ~IProducer() {};
	virtual void Attach(observer) = 0;
	virtual void Detach(observer) = 0;
	virtual void Notify() = 0;
};
#endif //IPRODUCER_H