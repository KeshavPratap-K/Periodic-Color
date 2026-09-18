module.exports = function(minified) {
  var clayConfig = this;

  function addClass(element, className) {
    if ((' ' + element.className + ' ').indexOf(' ' + className + ' ') === -1) {
      element.className += (element.className ? ' ' : '') + className;
    }
  }

  function installTableStyles() {
    if (document.getElementById('periodic-color-table-styles')) {
      return;
    }

    var style = document.createElement('style');
    style.id = 'periodic-color-table-styles';
    style.type = 'text/css';
    style.appendChild(document.createTextNode(
      '.periodic-table-header {' +
        'display:table;width:100%;table-layout:fixed;margin:0.8rem 0 0.25rem;' +
        'color:#b3b3b3;font-size:0.75rem;text-transform:uppercase;' +
      '}' +
      '.periodic-table-header span {display:table-cell;vertical-align:middle;}' +
      '.periodic-table-header span:first-child {padding-left:0.75rem;}' +
      '.periodic-table-header span:nth-child(2),' +
      '.periodic-table-header span:nth-child(3) {width:4.5rem;text-align:center;}' +
      '.periodic-element-row {' +
        'display:table;width:100%;table-layout:fixed;margin-top:0.35rem;' +
      '}' +
      '.periodic-element-row > .component {' +
        'display:table-cell;vertical-align:middle;margin:0!important;padding:0!important;' +
      '}' +
      '.periodic-element-row > .component:after {display:none!important;}' +
      '.periodic-element-row .component-heading {padding-left:0.75rem!important;}' +
      '.periodic-element-row .component-heading h5 {margin:0;font-size:0.85rem;}' +
      '.periodic-element-row .component-color {width:4.5rem;}' +
      '.periodic-element-row .component-color label {' +
        'justify-content:center;padding:0.45rem 0.2rem;' +
      '}' +
      '.periodic-element-row .component-color .label {display:none;}' +
      '.periodic-element-row .component-color .value {' +
        'width:2.35rem;height:2.35rem;border-radius:0.3rem;' +
      '}' +
      '.periodic-extra-row {display:none!important;}' +
      '.periodic-expanded .periodic-extra-row {display:table!important;}' +
      '.periodic-expand-button {display:block;width:100%;min-width:0;margin:0.7rem 0;}'
    ));
    document.head.appendChild(style);
  }

  function buildElementTable() {
    var root = clayConfig.$rootContainer[0];
    var rows = [];
    var index;

    installTableStyles();

    for (index = 0; index < clayConfig.meta.userData.elements.length; index++) {
      var card = clayConfig.getItemById('card-' + index);
      var row = card.$element[0].parentNode;
      addClass(row, 'periodic-element-row');
      if (index >= 4) {
        addClass(row, 'periodic-extra-row');
      }
      rows.push(row);
    }

    var header = document.createElement('div');
    header.className = 'periodic-table-header';
    header.innerHTML = '<span>Element Name</span><span>Background Color</span><span>Text Color</span>';
    rows[0].parentNode.insertBefore(header, rows[0]);

    var expand = document.createElement('button');
    var expanded = false;
    expand.type = 'button';
    expand.className = 'periodic-expand-button';
    expand.innerHTML = 'Show all elements';
    expand.onclick = function() {
      expanded = !expanded;
      if (expanded) {
        addClass(root, 'periodic-expanded');
        expand.innerHTML = 'Show fewer elements';
      } else {
        root.className = root.className.replace(/(^|\s)periodic-expanded(?=\s|$)/g, ' ').replace(/^\s+|\s+$/g, '');
        expand.innerHTML = 'Show all elements';
      }
    };
    rows[4].parentNode.insertBefore(expand, rows[4]);
  }

  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {
    buildElementTable();

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
