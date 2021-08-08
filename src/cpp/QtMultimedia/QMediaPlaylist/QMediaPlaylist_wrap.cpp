#include "QMediaPlaylist_wrap.h"

#include <napi.h>

#include <QMediaPlaylist>
#include <QUrl>

#include "nodegui/Extras/Utils/nutils.h"
#include "nodegui/QtCore/QObject/qobject_macro.h"
#include "nodegui/QtCore/QUrl/qurl_wrap.h"
#include "QtWidgets/QWidget/qwidget_wrap.h"
#include "src/cpp/QtMultimediaWidgets/QVideoWidget/qvideowidget_wrap.h"

Napi::FunctionReference QMediaPlaylistWrap::constructor;

Napi::Object QMediaPlaylistWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QMediaPlaylist";
  Napi::Function func = DefineClass(env, CLASSNAME, {
    InstanceMethod("addMedia", &QMediaPlaylistWrap::addMedia),
    // InstanceMethod("clear", &QMediaPlaylistWrap::clear),
    // InstanceMethod("currentIndex", &QMediaPlaylistWrap::currentIndex),
    // InstanceMethod("currentMedia", &QMediaPlaylistWrap::currentMedia),
    // InstanceMethod("error", &QMediaPlaylistWrap::error),
    // InstanceMethod("errorString", &QMediaPlaylistWrap::errorString),
    // InstanceMethod("insertMedia", &QMediaPlaylistWrap::insertMedia),
    // InstanceMethod("isEmpty", &QMediaPlaylistWrap::isEmpty),
    // InstanceMethod("isReadOnly", &QMediaPlaylistWrap::isReadOnly),
    // InstanceMethod("load", &QMediaPlaylistWrap::load),
    // InstanceMethod("media", &QMediaPlaylistWrap::media),
    // InstanceMethod("mediaCount", &QMediaPlaylistWrap::mediaCount),
    // InstanceMethod("moveMedia", &QMediaPlaylistWrap::moveMedia),
    // InstanceMethod("playbackMode", &QMediaPlaylistWrap::playbackMode),
    // InstanceMethod("previousIndex", &QMediaPlaylistWrap::previousIndex),
    // InstanceMethod("removeMedia", &QMediaPlaylistWrap::removeMedia),
    // InstanceMethod("save", &QMediaPlaylistWrap::save),
    // InstanceMethod("setPlaybackMode", &QMediaPlaylistWrap::setPlaybackMode),

    // Slots
    // InstanceMethod("next", &QMediaPlaylistWrap::next),
    // InstanceMethod("previous", &QMediaPlaylistWrap::previous),
    InstanceMethod("setCurrentIndex", &QMediaPlaylistWrap::setCurrentIndex),
    // InstanceMethod("shuffle", &QMediaPlaylistWrap::shuffle),
    QOBJECT_WRAPPED_METHODS_EXPORT_DEFINE(QMediaPlaylistWrap)
  });
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

QMediaPlaylistWrap::QMediaPlaylistWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QMediaPlaylistWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() == 1) {
    Napi::Object parentObject = info[0].As<Napi::Object>();
    NodeWidgetWrap* parentWidgetWrap =
      Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);
    this->instance = new NMediaPlaylist(
      parentWidgetWrap->getInternalInstance()
    );  // this sets the parent to current widget
  } else if (info.Length() == 0) {
    this->instance = new NMediaPlaylist();
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
  }
  this->rawData = extrautils::configureQObject(this->getInternalInstance());
}

QMediaPlaylistWrap::~QMediaPlaylistWrap() { extrautils::safeDelete(this->instance); }

NMediaPlaylist* QMediaPlaylistWrap::getInternalInstance() { return this->instance; }

Napi::Value QMediaPlaylistWrap::addMedia(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  if (info.Length() == 0) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
  }
  auto napiObj = info[0].As<Napi::Object>().Get("native").As<Napi::Object>();
  auto qUrlWrap = Napi::ObjectWrap<QUrlWrap>::Unwrap(napiObj);
  bool result = this->instance->addMedia(*qUrlWrap->getInternalInstance());
  return Napi::Boolean::New(env, result);
}

Napi::Value QMediaPlaylistWrap::setCurrentIndex(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  if (info.Length() == 0) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
  }
  int playlistPosition = info[0].As<Napi::Number>().Int32Value();
  this->instance->setCurrentIndex(playlistPosition);
  return env.Undefined();
}
