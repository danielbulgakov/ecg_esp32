import anothertest from "./another-test.js";

function test(list) {
  anothertest()
  console.log('Добрый день, я функция test, из другого модуля!', list);
}

export {
  test
}