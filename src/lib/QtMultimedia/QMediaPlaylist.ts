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

export class QMediaPlaylist extends NodeWidget<any> {
  native: NativeElement;
  constructor();
  constructor(parent: NodeWidget<any>);
  constructor(parent?: NativeElement | NodeWidget<any>) {
      let native;
      if (checkIfNativeElement(parent)) {
          native = parent as NativeElement;
      } else if (parent) {
          native = new addon.QMediaPlaylist(parent.native);
      } else {
          native = new addon.QMediaPlaylist();
      }
      super(native);
      this.native = native;
  }

  addMedia(content: any): boolean {
    return this.native.addMedia(content);
  }

  setCurrentIndex(playlistPosition: number): void {
    return this.native.setCurrentIndex(playlistPosition);
  }
}
