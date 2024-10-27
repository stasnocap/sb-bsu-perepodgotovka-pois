function getRandomArray(length = 10) {
  const array = [];
  for (let i = 0; i < length; i++) {
    array[i] = Math.floor(Math.random() * length);
  }
  console.log(`Random array of length ${length} was created: ${array}`)
  return array;
}

/*
  1. Создать массив и найти в нем номер наибольшего элемента
 */
function getMaxIndexOfRandomArray(length) {
  const array = getRandomArray(length);

  let maxIndex = 0;
  for (let i = 0; i < array.length; i++) {
    if (maxIndex < array[i]) {
      maxIndex = i;
    }
  }

  return maxIndex;
}

/*
  2. Создать массив с целочисленными значениями, и посчитать сумму элементов кратных трем
 */
function getNumbersSumThatDividesByThreeOfRandomArray(length) {
  const array = getRandomArray(length);

  let sum = 0;
  for (let i = 0; i < array.length; i++) {
    if (array[i] % 3 === 0) {
      sum += array[i];
    }
  }

  return sum;
}

/*
  3. Создать массив с целочисленными значениями, и посчитать сумму элементов между максимальным и минимальным элементами массива
 */
function getSumBetweenMaxAndMinOfRandomArray(length) {
  const array = getRandomArray(length)

  let min = 0;
  let max = 0;
  for (let i = 0; i < array.length; i++) {
    if (array[min] > array[i]) {
      min = i;
    }
    if (array[max] < array[i]) {
      max = i;
    }
  }

  let sum = 0;
  if (max > min) {
    for (let i = min; i < max - 1; i++)
      sum += array[i + 1];
  } else {
    for (let i = max; i < min - 1; i++)
      sum += array[i + 1];
  }

  return sum;
}

/*
  4. Создать массив, распечатать его, перевернуть и снова распечатать. Не следует использовать дополнительные массивы, и стандартные функции типа reverse
 */
function reverseRandomArray(length) {
  const array = getRandomArray(length);
  
  for (let i = 0; i < array.length / 2; i++) {
    const temp = array[array.length - 1 - i];
    array[array.length - 1 - i] = array[i];
    array[i] = temp;
  }
  
  console.log(`Reversed array: ${array}`);
}