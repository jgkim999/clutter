#ifndef _ISESSION_
#define _ISESSION_

class ISession
{
public:
  ISession() {}
  virtual ~ISession() {}
  virtual void start() = 0;
  virtual void stop() = 0;
};

#endif // _ISESSION_
