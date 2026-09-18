var Clay = require('pebble-clay');
var settings = require('./config');
var customClay = require('./custom-clay');

function activeWatchIsColor() {
  var info = clay.meta.activeWatchInfo || {};
  return info.platform !== 'aplite' && info.platform !== 'diorite';
}

function rgbToPebbleArgb(rgb) {
  return 0xC0 | (((rgb >> 16) & 0xFF) >> 6) << 4 |
      ((((rgb >> 8) & 0xFF) >> 6) << 2) | ((rgb & 0xFF) >> 6);
}

var clay = new Clay(settings.build(true), customClay, {
  autoHandleEvents: false,
  userData: settings
});

Pebble.addEventListener('showConfiguration', function() {
  clay.config = settings.build(activeWatchIsColor());
  Pebble.openURL(clay.generateUrl());
});

Pebble.addEventListener('webviewclosed', function(event) {
  if (!event || !event.response) {
    return;
  }
  var chosen = clay.getSettings(event.response);
  var cardColors = [];
  var textColors = [];
  for (var index = 0; index < settings.elements.length; index++) {
    cardColors.push(rgbToPebbleArgb(chosen[1000 + index]));
    textColors.push(rgbToPebbleArgb(chosen[1100 + index]));
  }
  Pebble.sendAppMessage({
    BACKGROUND_COLOR: chosen.BACKGROUND_COLOR,
    CARD_COLORS: cardColors,
    TEXT_COLORS: textColors
  });
});
