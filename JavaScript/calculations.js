'use strict';

const scoreCalculation = (arr) => {
  for (let i = 1; i < 21; i++) {
    arr.sort(((a, b) => +b[i] - +a[i]));
    arr[0][i] = 12;
    arr[1][i] = 10;
    for (let j = 2; j < 10; j++) {
      arr[j][i] = 10 - j;
    }
    for (let j = 10; j < 20; j++) {
      arr[j][i] = 0;
    }
  }
  count(arr);
  return arr.sort((a, b) => b[1] - a[1]);
};

const count = (arr) => {
  let res;
  for (let i = 0; i < 20; i++){
    res = 0;
    for(let j = 1; j < 21; j++){
      res += +arr[i].pop();
    }
    arr[i][1] = res;
  }
};
module.exports.scoreCalculation = scoreCalculation;