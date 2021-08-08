#pragma once
#include <napi.h>

#include <QVideoWidget>

#include "Extras/Export/export.h"
#include "QtCore/QObject/qobject_macro.h"
#include "core/Events/eventwidget.h"
#include "core/Events/eventwidget_macro.h"
#include "QtWidgets/QWidget/qwidget_macro.h"

class DLL_EXPORT NVideoWidget : public QVideoWidget, public NodeWidget {
 public:
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(QVideoWidget)
  using QVideoWidget::QVideoWidget;

  void connectSignalsToEventEmitter() {
    QWIDGET_SIGNALS
    // QWIDGET_SIGNALS
    QObject::connect(this, &QVideoWidget::brightnessChanged, [=](int brightness) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "brightnessChanged"),
        Napi::Number::From(env, brightness)
      });
    });
    QObject::connect(this, &QVideoWidget::contrastChanged, [=](int contrast) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "contrastChanged"),
        Napi::Number::From(env, contrast)
      });
    });
    QObject::connect(this, &QVideoWidget::fullScreenChanged, [=](bool fullScreen) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "fullScreenChanged"),
        Napi::Boolean::From(env, fullScreen)
      });
    });
    QObject::connect(this, &QVideoWidget::hueChanged, [=](int hue) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "hueChanged"),
        Napi::Number::From(env, hue)
      });
    });
    QObject::connect(this, &QVideoWidget::saturationChanged, [=](int saturation) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "saturationChanged"),
        Napi::Number::From(env, saturation)
      });
    });
  }
};