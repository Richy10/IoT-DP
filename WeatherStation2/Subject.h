#ifndef ISUBJECT_h
#define ISUBJECT_h

class ISubject 
{
 public:
  virtual void registerObserver( IObserver *o ) = 0;
  virtual void removeObserver( IObserver *o ) = 0;
  virtual void notifyObservers() = 0;
};

#endif
