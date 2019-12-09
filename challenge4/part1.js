const number = [271973, 785961];

/* However, they do remember a few key facts about the password:
 *
 * It is a six-digit number.
 * The value is within the range given in your puzzle input.
 * Two adjacent digits are the same (like 22 in 122345).
 * Going from left to right, the digits never decrease; they only ever increase
   or stay the same (like 111123 or 135679).
*/
function isElfPassword(num) {
  // The value is within the range given in your puzzle input. This makes it a
  // six-digit number, too.
  let str = num.toString();
  let prev2 = -1
  let prev = -1;
  let seenRepeat = Array(10);
  for(let i = 0; i < 6; i++) {
    let cur = Number(str[i])
    if (cur == prev) seenRepeat[cur] = cur != prev2;
    if (cur < prev) return false;
    [prev, prev2] = [cur, prev];
  }

  // If return the value of the statement: "not EVERY value in seenRepeat is false"
  return !seenRepeat.every((i) => !i)
}

var answers = 0;
for(let n = number[0]; n <= number[1]; n++) {
  if(isElfPassword(n)) answers++
}
console.log(answers);
