# Mark Calculator (Coursework Grading System)

**Author:** MUHAMMAD ARIF AFIQ BIN KAMARULZAIDI (22303865)

**Course:** CPT111 - Programming Principles

-----

## 📖 Project Overview

The **Mark Calculator** is a C++ console application designed to assist educators in automating the grading process for large numbers of students.

Instead of manually calculating weighted scores and grades, this program reads raw student data from a text file, applies user-defined weightages (for tests and assignments), and generates a structured output file containing the final coursework marks, percentage scores, and letter grades.

## 🚀 Key Features

  * **Automated Calculation:** Instantly computes weighted marks for Test 1, Test 2, Assignment 1, and Assignment 2.
  * **Dynamic Weighting:** Allows the user to define the percentage contribution of each assessment component during runtime.
  * **File I/O Processing:**
      * **Input:** Reads student matric numbers and raw scores from `CPT111_CWMarks.txt`.
      * **Output:** Writes a detailed report to `CPT111_CWMarks_Output.txt`.
  * **Grading Logic:** Automatically assigns letter grades (A, B, C, D, F) based on the calculated percentage.

-----

## 🛠 Technical Implementation

This project demonstrates fundamental C++ programming concepts:

  * **Modular Programming:** Logic is separated into specific functions (`Weightage`, `DetermineGrade`, `readFile`, `writeFile`).
  * **File Streams:** Uses `<fstream>` for reading input and writing output.
  * **Parallel Arrays:** Stores student data across multiple synchronized arrays:
      * `MatricNo[]`: Stores student IDs.
      * `studentData[][]`: Stores raw and calculated scores.
      * `Grade[]`: Stores final letter grades.

-----

## 📂 Project Structure

| File Name | Description |
| :--- | :--- |
| **`assignment2.cpp`** | The main source code containing the logic and menu system. |
| **`CPT111_CWMarks.txt`** | The **required** input file containing raw student scores. |
| **`CPT111_CWMarks_Output.txt`** | The generated output file with final grades (created by the program). |

### Input File Format (`CPT111_CWMarks.txt`)

The input file must follow this CSV-like format:

```text
Matric Number,Test 1,Test 2,Assignment 1,Assignment 2
123456,78,80,85,90
123457,65,55,60,54
...
```

-----

## 💻 How to Compile and Run

[Colab Notebook](https://colab.research.google.com/drive/1wa1O71Gq8gFwn_TLTP0CA57wQXHxxzAr?usp=sharing)

### Prerequisites

  * A C++ Compiler (e.g., G++, Clang, MSVC).

### 1\. Compilation

Open your terminal or command prompt and run:

```bash
g++ assignment2.cpp -o assignment2.elf
```

### 2\. Execution

Run the compiled executable:

```bash
./assignment2.elf
```

-----

## 🎮 Usage Guide

1.  **Prepare the Data:** Ensure `CPT111_CWMarks.txt` exists in the same directory as the program.
2.  **Start the Program:** You will see the "Mark Calculator" menu.
3.  **Enter Configuration:**
      * **Total Coursework Mark:** (e.g., 50 or 100)
      * **Number of Students:** (Must match the number of rows in your text file)
      * **Weightages:** Enter the % value for Test 1, Test 2, Assignment 1, and Assignment 2.
4.  **Confirm Settings:** Type `Y` to proceed or `N` to re-enter details.
5.  **View Results:** The program will generate `CPT111_CWMarks_Output.txt`. Open this file to see the final grades.

### Example Run

```text
===========================================================
|                      Mark Calculator                    |
===========================================================
Setting is empty, filling...

Enter the total coursework mark: 50
Enter the number of student: 15
Enter the percentage for:
1. Test 1: 10
2. Test 2: 10
3. Assignment 1: 15
4. Assignment 2: 15

Is the setting correct? Y or N. y

Creating file...

File created successfully.
```

-----

## 📊 Grading Scale

The program uses the following logic to determine grades:

| Percentage | Grade |
| :--- | :---: |
| ≥ 80 | A |
| 70 - 79 | B |
| 60 - 69 | C |
| 50 - 59 | D |
| \< 50 | F |
