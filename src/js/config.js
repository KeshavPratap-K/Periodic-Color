// The editor is generated from one source of truth so every periodic entry has
// the same three-column treatment: name, card colour, and text colour.
var ELEMENTS = [
  '0 Nuetronium', 'H Hydrogen', 'He Helium', 'Li Lithium', 'Be Beryllium',
  'B Boron', 'C Carbon', 'N Nitrogen', 'O Oxygen', 'F Fluorine', 'Ne Neon',
  'Na Sodium', 'Mg Magnesium', 'Al Aluminium', 'Si Silicon', 'P Phosphorus',
  'S Sulfur', 'Cl Chlorine', 'Ar Argon', 'K Potassium', 'Ca Calcium',
  'Sc Scandium', 'Ti Titanium', 'V Vanadium', 'Cr Chromium', 'Mn Manganese',
  'Fe Iron', 'Co Cobalt', 'Ni Nickel', 'Cu Copper', 'Zn Zinc', 'Ga Gallium',
  'Ge Germanium', 'As Arsenic', 'Se Selenium', 'Br Bromine', 'Kr Krypton',
  'Rb Rubidium', 'Sr Strontium', 'Y Yttrium', 'Zr Zirconium', 'Nb Niobium',
  'Mo Molybdenum', 'Tc Technetium', 'Ru Ruthenium', 'Rh Rhodium',
  'Pd Palladium', 'Ag Silver', 'Cd Cadmium', 'In Indium', 'Sn Tin',
  'Sb Antimony', 'Te Tellurium', 'I Iodine', 'Xe Xenon', 'Cs Caesium',
  'Ba Barium', 'La Lanthanum', 'Ce Cerium', 'Pr Praseodymium'
];

// Exact nearest Pebble palette entries for the original chemistry-cue preset.
var DEFAULT_CARD = [
  '333333','5599aa','ffffff','aa0000','5599aa','559900','333333','5599aa',
  '5599aa','ffcc00','aa5500','ffcc00','ffffff','5599aa','5599aa','aa0000',
  'ffcc00','559900','5544aa','5544aa','aa5500','5599aa','5599aa','559900',
  '5599aa','5544aa','aa0000','5599aa','559900','aa5500','5599aa','5599aa',
  '5544aa','559900','aa0000','aa0000','5544aa','5544aa','aa0000','aa0000',
  '5599aa','5599aa','559900','5599aa','5599aa','5544aa','559900','559900',
  'ffcc00','5599aa','5599aa','aa5500','559900','5544aa','5599aa','5599aa',
  '559900','5599aa','aa5500','559900'
];
var LIGHT_TEXT_CARDS = { '333333': true, 'aa0000': true, '5599aa': true, '5544aa': true, '555500': true };
var DEFAULT_TEXT = DEFAULT_CARD.map(function(color) {
  return LIGHT_TEXT_CARDS[color] ? 'ffffff' : '000000';
});

// Five monochrome swatches. On B&W Pebbles the system maps these to its
// supported black/white/gray display values; colour watches receive all 64.
var BW_FIVE = [['000000', '555555', 'aaaaaa', 'dddddd', 'ffffff']];

function colorItem(id, key, label, value, colorLayout) {
  return {
    type: 'color', id: id, messageKey: key, label: label,
    defaultValue: value, sunlight: false, allowGray: true, layout: colorLayout
  };
}

function buildConfig(isColor) {
  var pickerLayout = isColor ? 'COLOR' : BW_FIVE;
  var page = [
    { type: 'heading', defaultValue: 'Periodic Color', size: 2 },
    { type: 'text', defaultValue: 'Choose a background, then set each element card and its text. The colour picker shows only the palette for the connected watch.' },
    { type: 'section', items: [
      colorItem('background-color', 'BACKGROUND_COLOR', 'Background', '000000', pickerLayout)
    ] },
    { type: 'heading', defaultValue: 'Element | Card | Text', size: 4 },
    { type: 'text', defaultValue: 'Each element has a card-colour selector and a text-colour selector.' }
  ];

  ELEMENTS.forEach(function(name, index) {
    page.push({ type: 'section', items: [
      { type: 'heading', defaultValue: name, size: 5 },
      colorItem('card-' + index, 1000 + index, 'Card colour', DEFAULT_CARD[index], pickerLayout),
      colorItem('text-' + index, 1100 + index, 'Text colour', DEFAULT_TEXT[index], pickerLayout)
    ] });
  });

  page.push({ type: 'button', id: 'reset-defaults', defaultValue: 'Reset to original preset colours' });
  page.push({ type: 'submit', defaultValue: 'Save settings' });
  return page;
}

module.exports = {
  elements: ELEMENTS,
  defaultCard: DEFAULT_CARD,
  defaultText: DEFAULT_TEXT,
  build: buildConfig
};
