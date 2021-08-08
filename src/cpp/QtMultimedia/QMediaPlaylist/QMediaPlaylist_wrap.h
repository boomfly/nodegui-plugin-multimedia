#pragma once
#include <napi.h>

#include <QMediaPlaylist>
#include <QPointer>

#include "nmediaplaylist.hpp"
#include "QtCore/QObject/qobject_macro.h"
#include "nodegui/Extras/Utils/nutils.h"

class DLL_EXPORT QMediaPlaylistWrap : public Napi::ObjectWrap<QMediaPlaylistWrap> {
  QOBJECT_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<NMediaPlaylist> instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QMediaPlaylistWrap(const Napi::CallbackInfo& info);
  ~QMediaPlaylistWrap();
  NMediaPlaylist* getInternalInstance();
  // Wrapped methods
  Napi::Value addMedia(const Napi::CallbackInfo& info);
  Napi::Value clear(const Napi::CallbackInfo& info);
  Napi::Value currentIndex(const Napi::CallbackInfo& info);
  Napi::Value currentMedia(const Napi::CallbackInfo& info);
  Napi::Value error(const Napi::CallbackInfo& info);
  Napi::Value errorString(const Napi::CallbackInfo& info);
  Napi::Value insertMedia(const Napi::CallbackInfo& info);
  Napi::Value isEmpty(const Napi::CallbackInfo& info);
  Napi::Value isReadOnly(const Napi::CallbackInfo& info);
  Napi::Value load(const Napi::CallbackInfo& info);
  Napi::Value media(const Napi::CallbackInfo& info);
  Napi::Value mediaCount(const Napi::CallbackInfo& info);
  Napi::Value moveMedia(const Napi::CallbackInfo& info);
  Napi::Value nextIndex(const Napi::CallbackInfo& info);
  Napi::Value playbackMode(const Napi::CallbackInfo& info);
  Napi::Value previousIndex(const Napi::CallbackInfo& info);
  Napi::Value removeMedia(const Napi::CallbackInfo& info);
  Napi::Value save(const Napi::CallbackInfo& info);
  Napi::Value setPlaybackMode(const Napi::CallbackInfo& info);

  // Reimplemented
  Napi::Value mediaObject(const Napi::CallbackInfo& info);

  // Slots
  Napi::Value next(const Napi::CallbackInfo& info);
  Napi::Value previous(const Napi::CallbackInfo& info);
  Napi::Value setCurrentIndex(const Napi::CallbackInfo& info);
  Napi::Value suffle(const Napi::CallbackInfo& info);
};
