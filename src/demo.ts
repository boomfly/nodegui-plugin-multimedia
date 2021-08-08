import { QMainWindow, QUrl, FlexLayout, QWidget, QLabel } from "@nodegui/nodegui";
import { QMediaContent } from "./lib/QtMultimedia/QMediaContent";
import { QMediaPlayer } from "./lib/QtMultimedia/QMediaPlayer";
import { QMediaPlaylist } from "./lib/QtMultimedia/QMediaPlaylist";
import { QVideoWidget } from "./lib/QtMultimediaWidgets/QVideoWidget";

const win = new QMainWindow();
const centralWidget = new QWidget(win);
const rootLayout = new FlexLayout();
centralWidget.setLayout(rootLayout);
const mcontent = new QMediaContent();

const label = new QLabel();
label.setObjectName('mylabel');
label.setText('Hello');

rootLayout.addWidget(label);

const playlist = new QMediaPlaylist();
playlist.addMedia(QUrl.fromLocalFile("file:///Users/boomfly/Downloads/Big_Buck_Bunny_720_10s_5MB.mp4"));
playlist.setCurrentIndex(1);

const player = new QMediaPlayer(centralWidget);
player.addEventListener("error", (e: any) => {
  console.log(e)
});
// player.setMedia(QUrl.fromLocalFile("file:///Users/boomfly/Downloads/Big_Buck_Bunny_720_10s_5MB.mp4"));
player.setPlaylist(playlist);

const videoWidget = new QVideoWidget(centralWidget);
player.setVideoOutput(videoWidget);

videoWidget.addEventListener("error", (e: any) => {
  console.log(e)
});

rootLayout.addWidget(videoWidget);

console.log("isNull", mcontent.isNull());
win.setCentralWidget(centralWidget);
videoWidget.show();
win.show();
player.play();

(global as any).win = win; // To prevent win from being garbage collected.
