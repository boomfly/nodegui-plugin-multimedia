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
    Napi::Object napiObject = info[0].As<Napi::Object>();

    if (info[0].IsObject()) {
      printf("QMediaContentWrap: IsObject true\n");
      // Napi::Array napiArray = napiObject.GetPropertyNames();
      // for (int i = 0; i < napiArray.Length(); i++) {
      //   Napi::Value val = napiArray[i];
      //   printf("QMediaContentWrap constructor props: %s \n", val.ToString().Utf8Value().c_str());
      // }
      // Check instanceof wrappers
      if (napiObject.InstanceOf(QUrlWrap::constructor.Value())) {
        printf("QMediaContentWrap: QUrlWrap instance\n");
        QUrlWrap* urlWrap = Napi::ObjectWrap<QUrlWrap>::Unwrap(napiObject);
        this->instance = std::make_unique<QMediaContent>(*urlWrap->getInternalInstance());
      } else if (napiObject.InstanceOf(QMediaContentWrap::constructor.Value())) {
        printf("QMediaContentWrap: QMediaContentWrap instance\n");
        QMediaContentWrap* mediaContentWrap =
          Napi::ObjectWrap<QMediaContentWrap>::Unwrap(napiObject);
        this->instance = std::make_unique<QMediaContent>(
          *mediaContentWrap->getInternalInstance()
        );
      }
    } else if (info[0].IsExternal()) {
      printf("QMediaContentWrap: IsExternal true\n");
      if (napiObject.InstanceOf(QMediaContentWrap::constructor.Value())) {
        printf("QMediaContentWrap: QMediaContentWrap instance\n");
        QMediaContentWrap* mediaContentWrap =
          Napi::ObjectWrap<QMediaContentWrap>::Unwrap(napiObject);
        this->instance = std::make_unique<QMediaContent>(
          *mediaContentWrap->getInternalInstance()
        );
      }
    } else {
      Napi::TypeError::New(env, "Wrong arguments")
        .ThrowAsJavaScriptException();
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