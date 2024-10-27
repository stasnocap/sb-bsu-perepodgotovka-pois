/*
  1. Найти в строке не только запятые, но и другие знаки препинания. Подсчитать общее их количество
 */
function getCountOfNonWordCharacters(str) {
  if (!str) {
    return 0;
  }

  const nonWordCharacters = [',', '.', '!', '?', ';', ':']

  let sum = 0;
  for (let i = 0; i < str.length; i++) {
    if (nonWordCharacters.includes(str[i])) {
      sum++;
    }
  }

  return sum;
}

/*
  2. Имеется строка с текстом. Подсчитать количество слов в тексте.
  Желательно учесть, что слова могут разделяться несколькими пробелами, в
  начале и конце текста также могут быть пробелы, но могут и отсутствовать.
 */
function getCountOfWords(str) {
  if (!str) {
    return 0;
  }

  let temp = "";
  let words = 0;

  for (let i = 0; i < str.length; i++) {
    if ((str.charAt(i) >= 'а' && str.charAt(i) <= 'я') || (str.charAt(i) >= 'А' && str.charAt(i) <= 'Я')
      || (str.charAt(i) >= 'a' && str.charAt(i) <= 'z') || (str.charAt(i) >= 'A' && str.charAt(i) <= 'Z')) {
      temp += str.charAt(i);
    } else {
      if (temp !== "") {
        temp = "";
        words++;
      }
    }
  }

  return words;
}

/*
  3. Имеется строка с текстом. Вывести текст, составленный из последних букв всех слов.
 */
function getLastCharactersWord(str) {
  if (!str) {
    return '';
  }

  let temp = "";
  let result = "";
  for (let i = 0; i < str.length; i++) {
    if ((str.charAt(i) >= 'а' && str.charAt(i) <= 'я') || (str.charAt(i) >= 'А' && str.charAt(i) <= 'Я')
      || (str.charAt(i) >= 'a' && str.charAt(i) <= 'z') || (str.charAt(i) >= 'A' && str.charAt(i) <= 'Z')) {
      temp += str.charAt(i);
    } else {
      if (temp !== "") {
        result += temp.substring(temp.length - 1);
        temp = "";
      }
    }
  }

  return result;
}