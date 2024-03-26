function isPrime(num) {
  if (num <= 1) {
    return false;
  }
  for (let i = 2; i <= num / 2; i++) {
    if (num % i === 0) {
      return false;
    }
  }
  return true;
}

function findPrime(num) {
  let largestPrime = 0;
  for (let j = 2; j <= num; j++) {
    if (isPrime(j)) {
      largestPrime = j;
    }
  }

  return largestPrime;
}

module.exports = findPrime;
