'use strict';
const csv = require('./csv');
const calculation = require('./calculations');

csv.create(calculation.scoreCalculation(csv.parse('../eurovision.csv')));


