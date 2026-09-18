module.exports = function(minified) {
  var clayConfig = this;
  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {
    var reset = clayConfig.getItemById('reset-defaults');
    reset.on('click', function() {
      clayConfig.getItemById('background-color').set('000000');
      clayConfig.meta.userData.elements.forEach(function(unused, index) {
        clayConfig.getItemById('card-' + index).set(clayConfig.meta.userData.defaultCard[index]);
        clayConfig.getItemById('text-' + index).set(clayConfig.meta.userData.defaultText[index]);
      });
    });
  });
};
