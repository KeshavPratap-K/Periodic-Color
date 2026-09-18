var Clay = require('pebble-clay');
var messageKeys = require('message_keys');
var settings = require('./config');
var customClay = require('./custom-clay');

function activeWatchIsColor() {
  var info = clay.meta.activeWatchInfo || {};
  return info.platform !== 'aplite' && info.platform !== 'diorite';
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
  var payload = {};
  payload[messageKeys.BACKGROUND_COLOR] = chosen[messageKeys.BACKGROUND_COLOR];
  for (var index = 0; index < settings.elements.length; index++) {
    payload[messageKeys.CARD_COLOR + index] = chosen[messageKeys.CARD_COLOR + index];
    payload[messageKeys.TEXT_COLOR + index] = chosen[messageKeys.TEXT_COLOR + index];
  }
  Pebble.sendAppMessage(payload);
});
