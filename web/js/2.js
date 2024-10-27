/*
  1. Ввести целое число, проверить заканчивается ли оно на семерку
 */
function endsWith7(num) {
  return num % 10 === 7;
}

/*
  2. Ввести целое число - сумму в рублях, вывести это число и слово рублей в нужном падеже. (проверьте полученный результат на числах 101, 111, 3012, 3002)
 */
function formatSum(sum) {
  const remainderOfTen = sum % 10;
  const remainderOfHundred = sum % 100;

  if (remainderOfTen === 1 && remainderOfHundred !== 11) {
    return sum + " рубль";
  } else if (remainderOfTen >= 2 && remainderOfTen <= 4 && remainderOfHundred !== 12) {
    return sum + " рубля";
  } else {
    return sum + " рублей";
  }
}

/*
  3. Ввести три целых числа - день месяц и год, вывести в виде трех чисел дату следующего дня. (не использовать стандартные функции и объекты для работы с датой)
 */
function getNextDate(day, month, year) {
  day = parseInt(day);
  month = parseInt(month);
  year = parseInt(year);
  
  if ((day > 0 && day <= 30) && (month === 1 || month === 3 || month === 5 || month === 7 || month === 8 || month === 10) && year > 0) {
    day++;
  } else if ((day > 0 && day <= 29) && (month === 4 || month === 6 || month === 9 || month === 11) && year > 0) {
    day++;
  } else if ((day > 0 && day <= 28) && month === 2 && (year > 0 && year % 4 === 0)) {
    if (year % 100 === 0) {
      if (year % 400 === 0) {
        day++;
      } else {
        day = 1;
        month++;
      }
    } else {
      day++;
    }
  } else if ((day > 0 && day <= 27) && month === 2 && year > 0) {
    day++;
  } else if (day === 29 && month === 2 && (year > 0 && year % 4 === 0)) {
    if (year % 100 === 0) {
      if (year % 400 === 0) {
        day = 1;
        month++;
      } else {
        incorrectInput();
      }
    } else {
      day = 1;
      month++;
    }
  } else if (day === 28 && month === 2 && (year > 0 && year % 4 !== 0)) {
    day = 1;
    month++;
  } else if ((day === 31) && (month === 1 || month === 3 || month === 5 || month === 7 || month === 8 || month === 10) && year > 0) {
    day = 1;
    month++;
  } else if ((day === 30) && (month === 4 || month === 6 || month === 9 || month === 11) && year > 0) {
    day = 1;
    month++;
  } else if (day === 31 && month === 12 && year > 0) {
    day = 1;
    month = 1;
    year++;
  } else {
    incorrectInput();
  }
  
  return `${day}.${month}.${year}`

  function incorrectInput() {
    day = 0;
    month = 0;
    year = 0;
  }
}