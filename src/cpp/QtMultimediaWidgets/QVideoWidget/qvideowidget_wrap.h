#pragma once
#include <napi.h>

// #include <QVideoWidget>
#include <QPointer>

// #include "../QMediaObject/qmediaobject_macro.h"
#include "nvideowidget.hpp"
#include "nodegui/Extras/Utils/nutils.h"
// #include "nodegui/core/Component/component_macro.h"
#include "QtWidgets/QWidget/qwidget_macro.h"

class DLL_EXPORT QVideoWidgetWrap : public Napi::ObjectWrap<QVideoWidgetWrap> {
  QWIDGET_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<NVideoWidget> instance;
 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QVideoWidgetWrap(const Napi::CallbackInfo& info);
  ~QVideoWidgetWrap();
  NVideoWidget* getInternalInstance();
  // Wrapped methods
  Napi::Value aspectRatioMode(const Napi::CallbackInfo& info);
  Napi::Value brightness(const Napi::CallbackInfo& info);
  Napi::Value contrast(const Napi::CallbackInfo& info);
  Napi::Value hue(const Napi::CallbackInfo& info);
  Napi::Value isFullScreen(const Napi::CallbackInfo& info);
  Napi::Value saturation(const Napi::CallbackInfo& info);
  Napi::Value videoSurface(const Napi::CallbackInfo& info);
};
