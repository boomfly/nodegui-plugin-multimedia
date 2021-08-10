import addon from "../utils/addon";
import {
  NativeElement,
  Component,
  QUrl
} from "@nodegui/nodegui";
import { QMediaPlaylist } from "./QMediaPlaylist";

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
export class QMediaContent extends Component {
  native: NativeElement;
  constructor();
  // constructor(request: QNetworkRequest);
  constructor(playlist: QMediaPlaylist, contentUrl: QUrl, takeOwnership: boolean);
  constructor(other: QMediaContent);
  constructor(url: QUrl);
  constructor(...params: any[]) {
    super();
    if (params[0] instanceof QUrl) {
      console.log('params[0] instanceof QUrl');
      this.native = new addon.QMediaContent(params[0].native);
    } else if (params[0] instanceof QMediaPlaylist) {
      const [playlist, contentUrl, takeOwnership] = params;
      this.native = new addon.QMediaContent(playlist.native, contentUrl.native, takeOwnership);
    } else if (params[0] instanceof QMediaContent) {
      const [other] = params;
      this.native = new addon.QMediaContent(other.native);
    } else if (params.length > 0) {
      throw new Error('Wrong constructor params');
    } else {
      this.native = new addon.QMediaContent();
    }
  }
  isNull(): boolean {
    return this.native.isNull();
  }
}
