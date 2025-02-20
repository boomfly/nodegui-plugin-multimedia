#include "qmediaplayer_wrap.h"

#include <napi.h>

#include <QMediaPlayer>
#include <QUrl>

#include "nodegui/Extras/Utils/nutils.h"
#include "nodegui/QtCore/QObject/qobject_macro.h"
#include "nodegui/QtCore/QUrl/qurl_wrap.h"
#include "QtWidgets/QWidget/qwidget_wrap.h"
#include "src/cpp/QtMultimediaWidgets/QVideoWidget/qvideowidget_wrap.h"
#include "src/cpp/QtMultimedia/QMediaPlaylist/qmediaplaylist_wrap.h"

Napi::FunctionReference QMediaPlayerWrap::constructor;

Napi::Object QMediaPlayerWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QMediaPlayer";
  Napi::Function func =
      DefineClass(env, CLASSNAME,
                  {InstanceMethod("play", &QMediaPlayerWrap::play),
                   InstanceMethod("setMedia", &QMediaPlayerWrap::setMedia),
                   InstanceMethod("setPlaylist", &QMediaPlayerWrap::setPlaylist),
                   InstanceMethod("setVideoOutput", &QMediaPlayerWrap::setVideoOutput),
                   QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaPlayerWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

QMediaPlayerWrap::QMediaPlayerWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QMediaPlayerWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() == 1) {
    Napi::Object parentObject = info[0].As<Napi::Object>();
    NodeWidgetWrap* parentWidgetWrap =
        Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);
    this->instance = new NMediaPlayer(
        parentWidgetWrap
            ->getInternalInstance());  // this sets the parent to current widget
  } else if (info.Length() == 0) {
    this->instance = new NMediaPlayer();
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureQObject(this->getInternalInstance());
}

QMediaPlayerWrap::~QMediaPlayerWrap() { extrautils::safeDelete(this->instance); }

NMediaPlayer* QMediaPlayerWrap::getInternalInstance() { return this->instance; }

Napi::Value QMediaPlayerWrap::play(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  this->instance->play();
  return env.Undefined();
}

Napi::Value QMediaPlayerWrap::setMedia(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  if (info.Length() == 0) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
  }
  Napi::Object napiObject = info[0].As<Napi::Object>();
  if (napiObject.InstanceOf(QUrlWrap::constructor.Value())) {
    printf("QMediaPlayerWrap.setMedia: QUrlWrap instance\n");
    QUrlWrap* urlWrap = Napi::ObjectWrap<QUrlWrap>::Unwrap(napiObject);
    this->instance->setMedia(*urlWrap->getInternalInstance());
  } else if (napiObject.InstanceOf(QMediaContentWrap::constructor.Value())) {
    printf("QMediaPlayerWrap.setMedia: QMediaContentWrap instance\n");
    QMediaContentWrap* mediaContentWrap =
      Napi::ObjectWrap<QMediaContentWrap>::Unwrap(napiObject);
    this->instance->setMedia(*mediaContentWrap->getInternalInstance());
  } else {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
  }
  printf("QMediaPlayerWrap.setMedia success\n");
  return env.Undefined();
}

Napi::Value QMediaPlayerWrap::setPlaylist(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  if (info.Length() == 0) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
  }
  Napi::Object objectNapi = info[0].As<Napi::Object>();
  QMediaPlaylistWrap* objectWrap =
    Napi::ObjectWrap<QMediaPlaylistWrap>::Unwrap(objectNapi);
  this->instance->setPlaylist(objectWrap->getInternalInstance());
  return env.Undefined();
}

Napi::Value QMediaPlayerWrap::setVideoOutput(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  if (info.Length() == 0) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
  }
  auto napiObj = info[0].As<Napi::Object>().Get("native").As<Napi::Object>();
  auto qVideoWidgetWrap = Napi::ObjectWrap<QVideoWidgetWrap>::Unwrap(napiObj);
  this->instance->setVideoOutput(qVideoWidgetWrap->getInternalInstance());
  return env.Undefined();
}
