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
export class QVideoWidget extends NodeWidget<any> {
  native: NativeElement;
  constructor();
  constructor(parent: NodeWidget<any>);
  constructor(parent?: NativeElement | NodeWidget<any>) {
      let native;
      if (checkIfNativeElement(parent)) {
          native = parent as NativeElement;
      } else if (parent) {
          native = new addon.QVideoWidget(parent.native);
      } else {
          native = new addon.QVideoWidget();
      }
      super(native);
      this.native = native;
  }
  // constructor() {
  //   super();
  //   this.native = new addon.QVideoWidget();
  // }

  play(): void {
    return this.native.play();
  }

  show(): void {
    return this.native.show();
  }

  setMedia(url: QUrl): void {
    return this.native.setMedia(url);
  }
}
