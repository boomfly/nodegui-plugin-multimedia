#include "qmediacontent_wrap.h"

#include <napi.h>

#include <QMediaContent>

#include "nodegui/Extras/Utils/nutils.h"
#include "nodegui/QtCore/QUrl/qurl_wrap.h"
#include "../QMediaPlaylist/qmediaplaylist_wrap.h"

Napi::FunctionReference QMediaContentWrap::constructor;

Napi::Object QMediaContentWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QMediaContent";
  Napi::Function func = DefineClass(env, CLASSNAME, {
    InstanceMethod("isNull", &QMediaContentWrap::isNull),
    InstanceMethod("playlist", &QMediaContentWrap::playlist),
    // InstanceMethod("request", &QMediaContentWrap::request),
    COMPONENT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaContentWrap)
  });
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
  } else if (info.Length() == 1) {
    if (info[0].IsObject()) {
      printf("IsExternal true\n");
      Napi::Object objectNapi = info[0].ToObject();
      Napi::Object napiObj = info[0].As<Napi::Object>();
      printf("QMediaContentWrap constructor\n");
      // QUrlWrap* urlWrap = Napi::ObjectWrap<QUrlWrap>::Unwrap(napiObj);
      QUrl* urlWrap = Napi::ObjectWrap<QUrl>::Unwrap(napiObj);
      printf("QMediaContentWrap constructor unwraped\n");
      // this->instance = std::make_unique<QMediaContent>(*urlWrap->getInternalInstance());
      // if (objectNapi.InstanceOf(QUrlWrap::constructor.Value())) {
      //   printf("QUrlWrap install\n");
      // // } else if (Napi::Object::InstanceOf(QUrl)) {
      // //   printf("QUrl install\n");
      // }
    }
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

Napi::Value QMediaContentWrap::playlist(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  Napi::Object value = QMediaPlaylistWrap::constructor.New({
    Napi::External<QMediaPlaylist>::New(env, new QMediaPlaylist(
      this->instance->playlist()
    ))
  });
  return Napi::Value::From(env, value);
}