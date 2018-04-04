'use strict';

const fs = require('fs');

const create = (arr, path = '../results.csv') => {
  fs.writeFileSync(path,'');
  for (let i = 0;i < 10; i++){
    let insert = arr[i].join(',') + '\n';
    fs.appendFileSync(path,insert);
  }

};

const parse = (path) =>{
  let file = fs.readFileSync(path,'utf8');
  const arr = file.split('\n');
  const fieldsCount = +arr[0];
  const result = [];
  for(let i = 1; i < fieldsCount + 1; i++){
    result.push(arr[i].split(','));
  }
  return result;
};

module.exports.parse = parse;
module.exports.create = create;
