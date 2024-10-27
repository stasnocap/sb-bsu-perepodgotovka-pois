/*
  1. На основе примера с часами, минутами и секундами сделать программу, которая раскладывает общее количество секунд в секунды, минуты, часы, сутки и недели.
 */
function getDate(s) {
  const sec = s % 60;
  const m = (s - sec) / 60;

  const min = m % 60;
  const h = (m - min) / 60;

  const hour = h % 24;
  const d = (h - hour) / 24;

  const day = d % 7;
  const w = (d - day) / 7;

  return {
    sec,
    min,
    hour,
    day,
    w
  }
}

/*
  2. Имеется угол в радианах. Перевести его в градусы, минуты и секунды. Вывести результат на страницу. (180 градусов =  Пи радиан). Все выводимые значения должны быть целыми.
 */
function getDegrees(rad) {
  const deg = rad / (Math.PI / 180);

  const min2 = deg % 1;
  const degrees = deg - min2;

  const m2 = min2 * 60;
  const minutes = m2 - (m2 % 1);

  const s2 = m2 % 1;
  const sec2 = s2 * 60;
  const seconds = sec2 - (sec2 % 1);

  return {
    degrees,
    minutes,
    seconds
  }
}