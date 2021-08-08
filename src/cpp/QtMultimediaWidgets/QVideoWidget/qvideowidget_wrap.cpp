#include "qvideowidget_wrap.h"

#include <napi.h>

#include <QVideoWidget>
#include <QUrl>

#include "nodegui/Extras/Utils/nutils.h"
#include "nodegui/QtCore/QObject/qobject_macro.h"
#include "nodegui/QtCore/QUrl/qurl_wrap.h"
#include "QtWidgets/QWidget/qwidget_wrap.h"
#include "QtCore/QVariant/qvariant_wrap.h"

Napi::FunctionReference QVideoWidgetWrap::constructor;

Napi::Object QVideoWidgetWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QVideoWidget";
  Napi::Function func = DefineClass(env, CLASSNAME, {
    InstanceMethod("aspectRatioMode", &QVideoWidgetWrap::aspectRatioMode),
    InstanceMethod("brightness", &QVideoWidgetWrap::brightness),
    // InstanceMethod("contrast", &QVideoWidgetWrap::contrast),
    // InstanceMethod("hue", &QVideoWidgetWrap::hue),
    // InstanceMethod("isFullScreen", &QVideoWidgetWrap::isFullScreen),
    // InstanceMethod("saturation", &QVideoWidgetWrap::saturation),
    // InstanceMethod("videoSurface", &QVideoWidgetWrap::videoSurface),
    QWIDGET_WRAPPED_METHODS_EXPORT_DEFINE(QVideoWidgetWrap)
  });
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

QVideoWidgetWrap::QVideoWidgetWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<QVideoWidgetWrap>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() == 1) {
    Napi::Object parentObject = info[0].As<Napi::Object>();
    NodeWidgetWrap* parentWidgetWrap =
        Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);
    this->instance = new NVideoWidget(parentWidgetWrap->getInternalInstance());
  } else if (info.Length() == 0) {
    this->instance = new NVideoWidget();
  } else {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
  }
  // auto flexNode = this->getInternalInstance()->getFlexNode();
  // YGNodeSetNodeType(flexNode, YGNodeType::YGNodeTypeDefault);
  // this->rawData =
  //   extrautils::configureQWidget(this->getInternalInstance(), flexNode, true);

  this->rawData = extrautils::configureQWidget(
    this->getInternalInstance(),
    this->getInternalInstance()->getFlexNode(),
    false
  );
}

QVideoWidgetWrap::~QVideoWidgetWrap() { extrautils::safeDelete(this->instance); }

NVideoWidget* QVideoWidgetWrap::getInternalInstance() { return this->instance; }

Napi::Value QVideoWidgetWrap::aspectRatioMode(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  return Napi::Number::New(env, this->instance->aspectRatioMode());
}

Napi::Value QVideoWidgetWrap::brightness(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  return Napi::Number::New(env, this->instance->brightness());
}
