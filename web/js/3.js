/*
  1. Вычислить и распечатать факториал числа: произведение всех чисел от 1 и до него.
 */
function printFactorial(num) {
  if (num <= 0) {
    console.log('Некорректные входные данные');
    return;
  }

  let i = 1;
  let factorial = 1;

  while (i <= num) {
    factorial *= i;
    i++;
  }

  console.log(`Факториал равен: ${factorial}`);
}

/*
  2. На основе примера со средним арифметическим ввести последовательность чисел и найти наибольшее из них
 */
function getMax(array) {
  if (!array.length) {
    return;
  }

  let max = 0;

  for (let i = 0; i < array.length; i++) {
    if (max < array[i]) {
      max = array[i];
    }
  }

  return max;
}

/*
  3. Ввести число, посчитать сумму цифр в нем
 */
function getSumInNum(num) {
  const ten = 10;

  let sum = 0;
  while (num !== 0) {
    sum += num % ten;
    num = Math.floor(num / ten);
  }

  return sum;
}

/*
  4. Ввести число, определить является ли оно простым (т.е. делится без остатка только на 1 и себя)
 */
function isPrimeNumber(num) {
  if (num <= 1) {
    return false;
  }

  let counter = 0;
  for (let i = 2; i <= num; i++) {
    if (num % i === 0) {
      counter++;
    }
  }
  
  return counter <= 1;
}