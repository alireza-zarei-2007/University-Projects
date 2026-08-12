# 🔐 String Decoder

A recursive program that decodes encoded strings using a specific pattern where substrings inside brackets are repeated a specified number of times.

---

## Description

The program decodes an encoded string where:
- Characters outside brackets are displayed directly
- Substrings inside brackets `[S]` are repeated `k` times (where `k` is the number before the bracket)
- Encoding format: `k[S]` where `S` is a substring and `k` is a positive integer

---

## Input Format

- Single line containing the encoded string

**Constraints:**
- 1 ≤ S.length ≤ 30
- Contains English letters, brackets (`[` and `]`), and positive integers
- Valid encoding format is guaranteed

---

## Output Format

- Single line containing the decoded string

---

## Sample Input 1
3[a]2[bc]

## Sample Output 1
aaabcbc

---

## Sample Input 2
b3[a2[c]]

## Sample Output 2
baccaccacc

---

## How It Works

**Example 1:** `3[a]2[bc]`
- `3[a]` → `a` repeated 3 times = `aaa`
- `2[bc]` → `bc` repeated 2 times = `bcbc`
- Result: `aaabcbc`

**Example 2:** `b3[a2[c]]`
- `3[a2[c]]` → `2[c]` = `cc`, then `a` + `cc` = `acc`, repeated 3 times = `accaccacc`
- `b` + `accaccacc` = `baccaccacc`

---

## Rules

1. **Recursive approach required** – The solution must use recursion
2. **Nested patterns supported** – Decode inner brackets first
3. **Decode format:** `k[S]` → repeat substring `S` exactly `k` times

---

## Installation & Execution

1. Save `Q2.cpp` in a folder.
2. Compile: `g++ Q2.cpp -o decoder`
3. Run: `./decoder`

---

## Decoding Process

1. Find innermost bracket pair
2. Extract the number `k` before the `[`
3. Extract the substring inside `[` and `]`
4. Replace `k[substring]` with `substring` repeated `k` times
5. Repeat until all brackets are processed

---

## Important Notes

- Only use recursion – loops are not allowed for the main decoding logic
- Input length is at most 30 characters
- Numbers are always positive integers (1 or greater)
- All brackets are properly matched and nested

---
