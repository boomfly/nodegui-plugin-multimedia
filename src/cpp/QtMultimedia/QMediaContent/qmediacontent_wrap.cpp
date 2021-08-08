#include "qmediacontent_wrap.h"

#include <napi.h>

#include <QMediaContent>

#include "nodegui/Extras/Utils/nutils.h"

Napi::FunctionReference QMediaContentWrap::constructor;

Napi::Object QMediaContentWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QMediaContent";
  Napi::Function func =
      DefineClass(env, CLASSNAME,
                  {InstanceMethod("isNull", &QMediaContentWrap::isNull),
                   COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaContentWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

QMediaContentWrap::QMediaContentWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QMediaContentWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() == 0) {
    this->instance = std::make_unique<QMediaContent>();
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureComponent(this->getInternalInstance());
}

QMediaContentWrap::~QMediaContentWrap() { this->instance.reset(); }

QMediaContent* QMediaContentWrap::getInternalInstance() {
  return this->instance.get();
}

Napi::Value QMediaContentWrap::isNull(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  return Napi::Value::From(env, this->instance->isNull());
}