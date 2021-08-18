#include <QCoreApplication>

#include "CPPLibrary/function_file.hpp"
#include "CPPLibrary/function_string.hpp"
#include "function_interface.hpp"

#include "object_event.hpp"

ObjectEvent::ObjectEvent(QObject *parent) : QObject(parent) {
  this->setObjectName("ObjectEvent");
  qRegisterMetaType<Event_Type>("Event_Type");
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
void ObjectEvent::initConnect(const std::vector<QObject*> vector_connect) {
  for (const QObject* object_connect : vector_connect) {
      QObject::connect(this, SIGNAL(signalMessage(std::string)), object_connect, SLOT(slotMessage(std::string)), Qt::QueuedConnection);
    }
}

bool ObjectEvent::initConfig() {
  slotEvent(Event_Type::Default, this->objectName().toStdString(), stringFuncInfo(this, __func__),
            this->objectName().toStdString() + " configuration finished");
  return true;
}

/*================================================================*/
/*Private Methods*/
/*================================================================*/

/*================================================================*/
/*Private Slots*/
/*================================================================*/
void ObjectEvent::slotEvent(Event_Type event_in, std::string object_in, std::string function_in, std::string text_in) {
  /*Format text_in for display & log*/
  std::string string_log = "[" + object_in + "]\t";
  function_in = stringReplace(function_in, "*", "");
  switch (event_in) {
    case Event_Type::Debug: {
        if (Flag_Debug) {
            Q_EMIT signalMessage(stringHTML(text_in, stringColorHSL(HUE_BLUE, SAT_COLOR, LUM_COLOR), true));
          }
        break;
      }
    case Event_Type::Error: {
        string_log += "ERROR - " + function_in + ":\t";
        Q_EMIT signalMessage(stringHTML("[" + object_in + "]", stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT), true) + "\t" +
                             stringHTML("ERROR:\t" + text_in, stringColorHSL(HUE_RED, SAT_COLOR, LUM_COLOR), true));
        break;
      }
    case Event_Type::Warning: {
        Q_EMIT signalMessage(stringHTML("Warning:\t" + text_in, stringColorHSL(HUE_YELLOW, SAT_COLOR, LUM_COLOR), true));
        break;
      }
    case Event_Type::Success: {
        Q_EMIT signalMessage(stringHTML(text_in, stringColorHSL(HUE_GREEN, SAT_COLOR, LUM_COLOR), true));
        break;
      }
    default: {
        Q_EMIT signalMessage(stringHTML(text_in, stringColorHSL(HUE_BASE, SAT_GRAY, LUM_TEXT), false));
      }
    }
  string_log.append(text_in);

  /*Log string_log*/
  fileAppend("Log/" + stringDateTime("%Y/%Y-%m-%d") + "_" + qApp->objectName().toStdString() + FILE_LOG,
             "[" + stringDateTime("%H:%M:%S") + "]\t" + string_log);
}

void ObjectEvent::slotModeDebug(bool mode_in) {
  Flag_Debug = mode_in;
}
