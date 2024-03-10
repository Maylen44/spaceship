#include "MessageController.h"

MessageController* MessageController::m_ptrMessageController = nullptr;


MessageController* MessageController::instance()
{
	m_ptrMessageController = new MessageController();
	return m_ptrMessageController;
}

/*

virtual void Attach(observer) = 0;
virtual void Detach(observer) = 0;
virtual void Notify() = 0;

#include "Observer.h"
#include "Logger.h"

Observer::Observer(Subject& subject)
	: m_subject(subject)
	, m_messageFromSubject()
	, m_number()
{
	m_subject.Attach(this);
	++s_numberOfObservers;
	LOGGER->Log("Hi, I'm the Observer " + s_numberOfObservers);
	m_number = s_numberOfObservers;
}

Observer::~Observer()
{
	LOGGER->Log("Goodbye, I was the Observer " + m_number);
}

void Observer::Update(const std::string& message_from_subject)
{
	m_messageFromSubject = message_from_subject;
	PrintInfo();
}

void Observer::RemoveMeFromTheList()
{
	m_subject.Detach(this);
	std::cout << "Observer " << m_number << " removed from the list." << std::endl;
}

void Observer::PrintInfo()
{
	std::cout << "Observer " << m_number << ": a new message is available --> "
		<< m_messageFromSubject << std::endl;
}

*/
