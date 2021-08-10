import addon from "../utils/addon";
import {
  NativeElement,
  Component,
  QUrl,
  NodeObject,
  QObjectSignals,
  NodeWidget,
  checkIfNativeElement
} from "@nodegui/nodegui";
import { QVideoWidget } from "../QtMultimediaWidgets/QVideoWidget";
import { QMediaPlaylist } from "../QtMultimedia/QMediaPlaylist";
import { QMediaContent } from "./QMediaContent";

/**
 
> The QMediaContent class provides access to the resource relating to a media content.

* **This class is a JS wrapper around Qt's [QMediaContent class](https://doc.qt.io/qt-5/qmediacontent.html)**

A `QMediaContent` provides ability to store an image in the memory.

### Example

```javascript
const { QMediaContent } = require("nodegui-plugin-qtmultimedia");

const mediaContent = new QMediaContent();
```
 */

enum Error {
  NoError = 0,
  ResourceError = 1,
  FormatError = 2,
  NetworkError = 3,
  AccessDeniedError = 4,
  ServiceMissingError = 5
}

enum MediaStatus {
  UnknownMediaStatus = 0,
  NoMedia = 1,
  LoadingMedia = 2,
  LoadedMedia = 3,
  StalledMedia = 4,
  BufferingMedia = 5,
  BufferedMedia = 6,
  EndOfMedia = 7,
  InvalidMedia = 8
}

enum Flags {
  LowLatency = 0x01,
  StreamPlayback = 0x02,
  VideoSurface = 0x04
}

enum State {
  StoppedState = 0,
  PlayingState = 1,
  PausedState = 2
}

export class QMediaPlayer extends NodeObject<any> {
  static readonly Error = Error;
  static readonly Flags = Flags;
  static readonly MediaStatus = MediaStatus;
  static readonly State = State;

  native: NativeElement;

  constructor();
  constructor(parent: NodeWidget<any>);
  constructor(parent?: NativeElement | NodeWidget<any>) {
      let native;
      if (checkIfNativeElement(parent)) {
          native = parent as NativeElement;
      } else if (parent) {
          native = new addon.QMediaPlayer(parent.native);
      } else {
          native = new addon.QMediaPlayer();
      }
      super(native);
      this.native = native;
  }

  play(): void {
    return this.native.play();
  }

  setPlaylist(playlist: QMediaPlaylist) {
    return this.native.setPlaylist(playlist.native);
  }

  setMedia(url: QUrl | QMediaContent): void {
    return this.native.setMedia(url.native);
  }

  setVideoOutput(videoWidget: QVideoWidget) {
    return this.native.setVideoOutput(videoWidget);
  }
}