
#ifndef kb_opendialog_H
#define kb_opendialog_H


#include "../kbshared/_opendialog.h"


#include "../kbrun/interpreter.h"

#define CLASS _opendialog

extern interpreter *EXTERN_myInterpreter;

class kb_opendialog : public _opendialog
{


public:kb_opendialog() : _opendialog(){ 

         setInterpreter(EXTERN_myInterpreter); 
       }


public: 
// set event handling related information, in which object to search for event methods for this object
void setKbId(memory_variable2 *sc, int n) 
{ 
  if (sc == 0 || kbScope == 0){ 
    kbScope = sc; kbId = n; 
  }
} 

void setInterpreter(interpreter *i){ setKbId(0, 0); myInterpreter = i;}



public:
#include "../kbasic_binding/_opendialog/interpreter_kbasic_binding_protected.h"

private: 

memory_variable2 *kbScope; int kbId; interpreter *myInterpreter; };//------------------------------------------------------------------------------------------------------------------------------------



#endif