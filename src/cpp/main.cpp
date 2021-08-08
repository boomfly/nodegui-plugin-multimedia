#include <napi.h>

#include "src/cpp/QtMultimedia/QMediaContent/qmediacontent_wrap.h"
#include "src/cpp/QtMultimedia/QMediaPlayer/qmediaplayer_wrap.h"
#include "src/cpp/QtMultimedia/QMediaPlaylist/qmediaplaylist_wrap.h"
#include "src/cpp/QtMultimediaWidgets/QVideoWidget/qvideowidget_wrap.h"

Napi::Object Main(Napi::Env env, Napi::Object exports) {
  QMediaContentWrap::init(env, exports);
  QMediaPlayerWrap::init(env, exports);
  QMediaPlaylistWrap::init(env, exports);
  QVideoWidgetWrap::init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)
