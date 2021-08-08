#pragma once
#include <napi.h>

#include <QMediaPlaylist>

#include "../QMediaObject/qmediaobject_macro.h"
#include "Extras/Export/export.h"
#include "QtCore/QObject/qobject_macro.h"
#include "core/Events/eventwidget.h"
#include "core/Events/eventwidget_macro.h"

class DLL_EXPORT NMediaPlaylist : public QMediaPlaylist, public EventWidget {
  Q_OBJECT
  EVENTWIDGET_IMPLEMENTATIONS(QMediaPlaylist)
 public:
  using QMediaPlaylist::QMediaPlaylist;

  void connectSignalsToEventEmitter() {
    QOBJECT_SIGNALS
    QObject::connect(this, &QMediaPlaylist::currentIndexChanged, [=](int position) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "currentIndexChanged"),
        Napi::Number::From(env, position)
      });
    });
    // TODO:
    // QObject::connect(this, &QMediaPlaylist::currentMediaChanged, [=](QMediaContent &content) {
    //   Napi::Env env = this->emitOnNode.Env();
    //   Napi::HandleScope scope(env);
    //   this->emitOnNode.Call({
    //     Napi::String::New(env, "currentMediaChanged"),
    //     Napi::Value::From(env, content)
    //   });
    // });
    QObject::connect(this, &QMediaPlaylist::loadFailed, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "loadFailed")
      });
    });
    QObject::connect(this, &QMediaPlaylist::loaded, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "loaded")
      });
    });
    QObject::connect(this, &QMediaPlaylist::mediaAboutToBeInserted, [=](int start, int end) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "mediaAboutToBeInserted"),
        Napi::Number::From(env, start),
        Napi::Number::From(env, end)
      });
    });
    QObject::connect(this, &QMediaPlaylist::mediaAboutToBeRemoved, [=](int start, int end) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "mediaAboutToBeRemoved"),
        Napi::Number::From(env, start),
        Napi::Number::From(env, end)
      });
    });
    QObject::connect(this, &QMediaPlaylist::mediaChanged, [=](int start, int end) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "mediaChanged"),
        Napi::Number::From(env, start),
        Napi::Number::From(env, end)
      });
    });
    QObject::connect(this, &QMediaPlaylist::mediaInserted, [=](int start, int end) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "mediaInserted"),
        Napi::Number::From(env, start),
        Napi::Number::From(env, end)
      });
    });
    QObject::connect(this, &QMediaPlaylist::mediaRemoved, [=](int start, int end) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "mediaRemoved"),
        Napi::Number::From(env, start),
        Napi::Number::From(env, end)
      });
    });
    QObject::connect(this, &QMediaPlaylist::playbackModeChanged, [=](int mode) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "playbackModeChanged"),
        Napi::Number::From(env, mode)
      });
    });
  }
};