int mcd(int unNum, int otroNum) {
  if (otroNum == 0) {
    return unNum;
  } else {
    return mcd(otroNum, unNum % otroNum);
  }
}
