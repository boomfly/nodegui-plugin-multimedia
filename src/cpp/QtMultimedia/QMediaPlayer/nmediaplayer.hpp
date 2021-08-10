#pragma once
#include <napi.h>

#include <QMediaPlayer>
#include <QMediaContent>

#include "../QMediaObject/qmediaobject_macro.h"
#include "../QMediaContent/qmediacontent_wrap.h"
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
    QObject::connect(this, &QMediaPlayer::audioAvailableChanged, [=](bool available) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "audioAvailableChanged"),
        Napi::Boolean::From(env, available)
      });
    });
    QObject::connect(this, &QMediaPlayer::audioRoleChanged, [=](QAudio::Role role) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "audioRoleChanged"),
        Napi::Number::From(env, static_cast<int>(role))
      });
    });
    QObject::connect(this, &QMediaPlayer::bufferStatusChanged, [=](int percentFilled) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "bufferStatusChanged"),
        Napi::Number::From(env, percentFilled)
      });
    });
    QObject::connect(this, &QMediaPlayer::currentMediaChanged, [=](const QMediaContent &media) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);

      Napi::Value mediaWrap = QMediaContentWrap::constructor.New({
        Napi::External<QMediaContent>::New(env, new QMediaContent(media))
      });

      this->emitOnNode.Call({
        Napi::String::New(env, "currentMediaChanged"),
        mediaWrap
      });
    });
    QObject::connect(this, &QMediaPlayer::customAudioRoleChanged, [=](const QString &role) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "customAudioRoleChanged"),
        Napi::String::From(env, role.toStdString())
      });
    });
    QObject::connect(this, &QMediaPlayer::durationChanged, [=](qint64 duration) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "durationChanged"),
        Napi::Number::From(env, static_cast<long>(duration))
      });
    });
    QObject::connect(
      this,
      QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
      [=](QMediaPlayer::Error error
    ) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "error"),
        Napi::Number::From(env, static_cast<int>(error))
      });
    });
    QObject::connect(this, &QMediaPlayer::mediaChanged, [=](const QMediaContent &media) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);

      Napi::Value mediaWrap = QMediaContentWrap::constructor.New({
        Napi::External<QMediaContent>::New(env, new QMediaContent(media))
      });

      this->emitOnNode.Call({
        Napi::String::New(env, "mediaChanged"),
        mediaWrap
      });
    });
    QObject::connect(
      this,
      &QMediaPlayer::mediaStatusChanged,
      [=](QMediaPlayer::MediaStatus status
    ) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "mediaStatusChanged"),
        Napi::Number::From(env, static_cast<int>(status))
      });
    });
    QObject::connect(this, &QMediaPlayer::mutedChanged, [=](bool muted) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "mutedChanged"),
        Napi::Boolean::From(env, muted)
      });
    });
    QObject::connect(this, &QMediaPlayer::playbackRateChanged, [=](qreal rate) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "playbackRateChanged"),
        Napi::Number::From(env, static_cast<float>(rate))
      });
    });
    QObject::connect(this, &QMediaPlayer::positionChanged, [=](qint64 position) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "positionChanged"),
        Napi::Number::From(env, static_cast<long>(position))
      });
    });
    QObject::connect(this, &QMediaPlayer::seekableChanged, [=](qint64 seekable) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "seekableChanged"),
        Napi::Number::From(env, static_cast<long>(seekable))
      });
    });
    QObject::connect(this, &QMediaPlayer::stateChanged, [=](QMediaPlayer::State state) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "stateChanged"),
        Napi::Number::From(env, static_cast<int>(state))
      });
    });
    QObject::connect(this, &QMediaPlayer::videoAvailableChanged, [=](bool videoAvailable) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "videoAvailableChanged"),
        Napi::Boolean::From(env, videoAvailable)
      });
    });
    QObject::connect(this, &QMediaPlayer::volumeChanged, [=](int volume) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({
        Napi::String::New(env, "volumeChanged"),
        Napi::Boolean::From(env, volume)
      });
    });
  }
};