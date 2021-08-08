#pragma once

#include "../Utils/map_qstringlist.h"
#include "nodegui/QtCore/QObject/qobject_macro.h"

/*
  This macro adds common QMediaObject exported methods
  The exported methods are taken into this macro to avoid writing them in each
  and every widget we export.
 */
#ifndef QMEDIAOBJECT_WRAPPED_METHODS_DECLARATION
#define QMEDIAOBJECT_WRAPPED_METHODS_DECLARATION                           \
                                                                           \
  QOBJECT_WRAPPED_METHODS_DECLARATION                                      \
                                                                           \
  Napi::Array availableMetadata(const Napi::CallbackInfo& info) {          \
    Napi::Env env = info.Env();                                            \
    Napi::HandleScope scope(env);                                          \
    QStringList availMD = this->instance->availableMetaData();             \
    return mapQStringListToNapiArray(env, availMD);                        \
  }                                                                        \
                                                                           \
  Napi::Boolean isMetaDataAvailable(const Napi::CallbackInfo& info) {      \
    Napi::Env env = info.Env();                                            \
    Napi::HandleScope scope(env);                                          \
    return Napi::Boolean::New(env, this->instance->isMetaDataAvailable()); \
  }                                                                        \
                                                                           \
  Napi::Value metaData(const Napi::CallbackInfo& info) {                   \
    Napi::Env env = info.Env();                                            \
    Napi::HandleScope scope(env);                                          \
    /* QVariant	metaData(const QString &key) const */                      \
    Napi::TypeError::New(env, "Not implemented yet")                       \
        .ThrowAsJavaScriptException();                                     \
    return env.Undefined();                                                \
  }                                                                        \
                                                                           \
  Napi::Number notifyInterval(const Napi::CallbackInfo& info) {            \
    Napi::Env env = info.Env();                                            \
    Napi::HandleScope scope(env);                                          \
    return Napi::Number::New(env, this->instance->notifyInterval());       \
  }                                                                        \
                                                                           \
  Napi::Value setNotifyInterval(const Napi::CallbackInfo& info) {          \
    Napi::Env env = info.Env();                                            \
    Napi::HandleScope scope(env);                                          \
    if (info.Length() == 0) {                                              \
      Napi::TypeError::New(env, "Wrong number of arguments")               \
          .ThrowAsJavaScriptException();                                   \
    } else if (!info[0].IsNumber()) {                                      \
      Napi::TypeError::New(env, "Expected first argument to be a number")  \
          .ThrowAsJavaScriptException();                                   \
    }                                                                      \
    Napi::Number milliseconds = info[0].As<Napi::Number>();                \
    this->instance->setNotifyInterval(milliseconds.Int32Value());          \
    return env.Undefined();                                                \
  }                                                                        \
                                                                           \
  Napi::Value unbind(const Napi::CallbackInfo& info) {                     \
    Napi::Env env = info.Env();                                            \
    Napi::HandleScope scope(env);                                          \
    /* virtual void	unbind(QObject *object) */                             \
    return env.Undefined();                                                \
  }

#endif  // QMEDIAOBJECT_WRAPPED_METHODS_DECLARATION

#ifndef QMEDIAOBJECT_WRAPPED_METHODS_EXPORT_DEFINE
#define QMEDIAOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(WidgetWrapName)             \
                                                                               \
  QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(WidgetWrapName)                        \
  InstanceMethod("availableMetaData", &WidgetWrapName::availableMetaData),     \
      InstanceMethod("isMetaDataAvailable",                                    \
                     &WidgetWrapName::isMetaDataAvailable),                    \
      InstanceMethod("metaData", &WidgetWrapName::metaData),                   \
      InstanceMethod("notifyInterval", &WidgetWrapName::notifyInterval),       \
      InstanceMethod("setNotifyInterval", &WidgetWrapName::setNotifyInterval), \
      InstanceMethod("unbind", &WidgetWrapName::unbind),

#endif  // QMEDIAOBJECT_WRAPPED_METHODS_EXPORT_DEFINE

#ifndef QMEDIAOBJECT_SIGNALS
#define QMEDIAOBJECT_SIGNALS                                                   \
  QOBJECT_SIGNALS                                                              \
  QObject::connect(this, &QMediaObject::notifyIntervalChanged,                 \
                   [=](int milliSeconds) {                                     \
                     Napi::Env env = this->emitOnNode.Env();                   \
                     Napi::HandleScope scope(env);                             \
                     this->emitOnNode.Call(                                    \
                         {Napi::String::New(env, "notifyIntervalChanged"),     \
                          Napi::Number::New(env, milliSeconds)});              \
                   });                                                         \
  /*QObject::connect(this, &QMediaObject::metaDataChanged, [=]() {             \
    Napi::Env env = this->emitOnNode.Env();                                    \
    Napi::HandleScope scope(env);                                              \
    this->emitOnNode.Call({Napi::String::New(env, "metaDataChanged")});        \
  });      */                                                                  \
/*  QObject::connect(this, &QWidget::windowIconChanged, [=](const QIcon& icon) \
  { Napi::Env env = this->emitOnNode.Env(); Napi::HandleScope scope(env); auto \
  instance = QIconWrap::constructor.New( {Napi::External<QIcon>::New(env, new  \
  QIcon(icon))}); this->emitOnNode.Call( {Napi::String::New(env,               \
  "windowIconChanged"), instance});                                            \
  });                                                                          \
  QObject::connect(                                                            \
      this, &QWidget::customContextMenuRequested, [=](const QPoint& pos) {     \
        Napi::Env env = this->emitOnNode.Env();                                \
        Napi::HandleScope scope(env);                                          \
        auto instance = Napi::Object::New(env);                                \
        instance.Set("x", Napi::Number::New(env, pos.x()));                    \
        instance.Set("y", Napi::Number::New(env, pos.y()));                    \
        this->emitOnNode.Call(                                                 \
            {Napi::String::New(env, "customContextMenuRequested"), instance}); \
      });                                                                      \
*/
#endif  // QMEDIAOBJECT_SIGNALS