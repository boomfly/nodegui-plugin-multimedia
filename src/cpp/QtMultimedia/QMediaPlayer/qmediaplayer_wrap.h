#pragma once
#include <napi.h>

#include <QMediaPlayer>
#include <QPointer>

#include "../QMediaObject/qmediaobject_macro.h"
#include "nmediaplayer.hpp"
#include "nodegui/Extras/Utils/nutils.h"
#include "nodegui/core/Component/component_macro.h"

class DLL_EXPORT QMediaPlayerWrap : public Napi::ObjectWrap<QMediaPlayerWrap> {
  QMEDIAOBJECT_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<NMediaPlayer> instance;

 public:
  static Napi::FunctionReference constructor;
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  QMediaPlayerWrap(const Napi::CallbackInfo& info);
  ~QMediaPlayerWrap();
  NMediaPlayer* getInternalInstance();
  // Wrapped methods
  Napi::Value play(const Napi::CallbackInfo& info);
  Napi::Value setMedia(const Napi::CallbackInfo& info);
  Napi::Value setPlaylist(const Napi::CallbackInfo& info);
  Napi::Value setVideoOutput(const Napi::CallbackInfo& info);
};
