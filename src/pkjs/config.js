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

var BW_FIVE = [['000000', '555555', 'aaaaaa', 'dddddd', 'ffffff']];

function buildConfig(isColor) {
  var pickerLayout = isColor ? 'COLOR' : BW_FIVE;

  // Build element options for select dropdown
  var elementOptions = ELEMENTS.map(function(name, index) {
    return { label: name, value: index };
  });

  return [
    { type: 'heading', defaultValue: 'Periodic Color', size: 2 },
    { type: 'section', items: [
      {
        type: 'color',
        id: 'background-color',
        messageKey: 'BACKGROUND_COLOR',
        label: 'Background Color',
        defaultValue: '000000',
        sunlight: false,
        allowGray: true,
        layout: pickerLayout
      }
    ] },
    { type: 'heading', defaultValue: 'Element Color Customizer', size: 4 },
    { type: 'section', items: [
      {
        type: 'select',
        id: 'selected-element',
        label: 'Select Element',
        defaultValue: 0,
        options: elementOptions
      },
      {
        type: 'color',
        id: 'card-color',
        label: 'Card Color',
        defaultValue: DEFAULT_CARD[0],
        sunlight: false,
        allowGray: true,
        layout: pickerLayout
      },
      {
        type: 'color',
        id: 'text-color',
        label: 'Text Color',
        defaultValue: DEFAULT_TEXT[0],
        sunlight: false,
        allowGray: true,
        layout: pickerLayout
      }
    ] },
    { type: 'submit', defaultValue: 'Save Settings' }
  ];
}

module.exports = {
  elements: ELEMENTS,
  defaultCard: DEFAULT_CARD,
  defaultText: DEFAULT_TEXT,
  build: buildConfig
};