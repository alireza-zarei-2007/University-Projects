# 🔄 Palindrome Checker

A recursive program that determines whether a given sentence is a palindrome, ignoring non-alphabetic characters and case sensitivity.

---

## Description

The program checks if a string can be read the same way forward and backward. Only English letters are considered; all other characters (spaces, punctuation, numbers, symbols) are ignored. The comparison is case-insensitive.

---

## Input Format

- First line: Number of test cases
- Next N lines: Each line contains a string to check

**Constraints:**
- Strings may contain any characters (letters, spaces, numbers, symbols)
- Only English letters are considered for palindrome checking
- Case sensitivity is ignored

---

## Output Format

- `yes` – The string is a palindrome
- `no` – The string is not a palindrome

---

## Sample Input
5
never odd or even
A man, a plan, a canal: Panama!
salmano
Hello, World!
123??@#abcCBA

## Sample Output
yes
yes
no
no
yes

---

## Rules

1. **Only English letters matter** – Ignore spaces, numbers, symbols, and punctuation
2. **Case insensitive** – 'A' equals 'a'
3. **No string modification allowed** – You cannot create a new filtered string; must handle characters recursively in place
4. **Recursive approach required** – The solution must use recursion

---

## Installation & Execution

1. Save `Q1.cpp` in a folder.
2. Compile: `g++ Q1.cpp -o palindrome`
3. Run: `./palindrome`

---

## Important Notes

- Input strings may contain spaces – use `getline()` to read them
- Recursion must handle non-alphabetic characters without modifying the original string
- Only lowercase letters are compared (convert both to lowercase)

---

## Example Explanation

| Input | Processed String | Result |
|-------|------------------|--------|
| `never odd or even` | `neveroddoreven` | yes |
| `A man, a plan, a canal: Panama!` | `amanaplanacanalpanama` | yes |
| `salmano` | `salmano` | no |
| `Hello, World!` | `helloworld` | no |
| `123??@#abcCBA` | `abccba` | yes |

---
