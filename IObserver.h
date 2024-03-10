#ifndef IOBSERVER_H
#define IOBSERVER_H


class IObserver
{
public:
	virtual ~IObserver() {};
	virtual void Update(int input) = 0;
};
#endif //IOBSERVER_H