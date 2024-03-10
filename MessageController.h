#ifndef MESSAGE_CONTROLLER_H
#define MESSAGE_CONTROLLER_H

#include "IObserver.h"
#include "IProducer.h"
#include <vector>
#include <iostream>

class MessageController
{
public:
	~MessageController() {};
	static MessageController* instance();
	void addReceiver(std::pair<PackageReceiver, IObserver*>* newReceiver)
	{
		m_receivers.push_back(*newReceiver);
		for (auto& object : m_receivers)
		{
			std::cout << object.first << std::endl;

		}
	}
	void addProducer(std::pair<PackageProducer, IProducer*>* newProducer)
	{
		m_producers.push_back(*newProducer);
	}

protected:
	MessageController() {};

	std::vector<std::pair<PackageReceiver, IObserver*>> m_receivers;
	std::vector<std::pair<PackageProducer, IProducer*>> m_producers;
	static MessageController* m_ptrMessageController;
};

#endif //MESSAGE_CONTROLLER_H