#pragma once
#include <napi.h>

#include <QMediaPlayer>

#include "../QMediaObject/qmediaobject_macro.h"
#include "Extras/Export/export.h"
#include "QtCore/QObject/qobject_macro.h"
#include "core/Events/eventwidget.h"
#include "core/Events/eventwidget_macro.h"

class DLL_EXPORT NMediaPlayer : public QMediaPlayer, public EventWidget {
  Q_OBJECT
  EVENTWIDGET_IMPLEMENTATIONS(QMediaPlayer)
 public:
  using QMediaPlayer::QMediaPlayer;

  void connectSignalsToEventEmitter() {
    QMEDIAOBJECT_SIGNALS
    QObject::connect(this, &QMediaPlayer::mutedChanged, [=](bool muted) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "mutedChanged"),
                             Napi::Boolean::From(env, muted)});
    });
  }
};