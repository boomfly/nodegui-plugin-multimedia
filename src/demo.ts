import { QMainWindow, QUrl, FlexLayout, QWidget, QLabel } from "@nodegui/nodegui";
import { QMediaContent } from "./lib/QtMultimedia/QMediaContent";
import { QMediaPlayer } from "./lib/QtMultimedia/QMediaPlayer";
import { QMediaPlaylist } from "./lib/QtMultimedia/QMediaPlaylist";
import { QVideoWidget } from "./lib/QtMultimediaWidgets/QVideoWidget";

const win = new QMainWindow();
// const centralWidget = new QWidget(win);
// const rootLayout = new FlexLayout();
// centralWidget.setLayout(rootLayout);
// const mcontent = new QMediaContent();

// const label = new QLabel();
// label.setObjectName('mylabel');
// label.setText('Hello');

// rootLayout.addWidget(label);

// const playlist = new QMediaPlaylist();
// playlist.addMedia(QUrl.fromLocalFile("/Users/boomfly/Downloads/Big_Buck_Bunny_720_10s_5MB.mp4"));
// playlist.setCurrentIndex(1);
const remoteUrl = new QUrl("http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4");
// console.log(remoteUrl.toString());
const mediaContent = new QMediaContent(remoteUrl);

const mediaContent2 = new QMediaContent(mediaContent);

// console.log("isNull", mediaContent.isNull());

const player = new QMediaPlayer();
player.addEventListener("error", (e: any) => {
  console.log('player error', e);
});
player.addEventListener("mediaStatusChanged", (e: any) => {
  console.log('player mediaStatusChanged', e);
});
player.addEventListener("currentMediaChanged", (e: any) => {
  console.log('player currentMediaChanged', e);
  // if (e) {
  //   try {
  //     console.log('player currentMediaChanged', e.isNull());
  //   } catch (e) {
  //     console.error(e)
  //   }
  // }
});

// player.setMedia(QUrl.fromLocalFile("/Users/boomfly/Downloads/Big_Buck_Bunny_720_10s_5MB.mp4"));
// player.setMedia(new QUrl("http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4"));
// player.setPlaylist(playlist);
player.setMedia(mediaContent2);

const videoWidget = new QVideoWidget();
player.setVideoOutput(videoWidget);

videoWidget.addEventListener("error", (e: any) => {
  console.log('videoWidget error', e)
});

// rootLayout.addWidget(videoWidget);

win.setCentralWidget(videoWidget);
// videoWidget.show();

setTimeout(() => {
  player.play();
}, 2000);
win.show();

(global as any).win = win; // To prevent win from being garbage collected.
