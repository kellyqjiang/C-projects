# C-projects
Projects done in C for my classes

1. PA2: This project was about bit manipulations and was made up into three parts:
    <p>a. Part one: In this part I had to write three methods, set(x, n, v), comp (x, n), and get(x, n). Where n represents the <i>nth</i> bit and n and v are represented by numbers. In the method set(x, n, v), we set the <i>nth</i> bit of x to the variable v and outputs the resulting value of x. In comp(x, n) we find the compliment of the <i>nth</i> bit of x and set it and returns the resulting value of x. For get(x, n), we return the value of the <i>nth</i> bit of x and outputs the value of the specific bit. For input, this method takes in a file that can has a number for x on the first line and then the methods to call. For set(x, n, v), in the input file it might look like <b>set 1 1</b>, which equates to set(x, 1, 1). For comp(x, n) in the input file it might look like <b>comp 0 0</b>, where the second value is always 0 and is ignored and the method call looks like comp(x, 0). For get(x, n) in the input file it might look like <b?get 0 0</b>, where the second value is always 0 and it ignored and the method call looks like get(x, 0).
    <p>b. Part two: In this part, I had to write a method that figures out the parity of the number given (for example 7 in binary is 111 and has an Odd parity), and output the amount of pairs of 1s there are without overlap (for example, for 7 there is 1 pair of 1s). For input, a value is put in the command line (for example, ./second 7). For output, the program will display whether it was even or odd parity (Even-Parity or Odd-Parity) and the number of pairs of 1s without overlap exists.
    <p>c. Part three: In this part I had to figure out if a given number is a palindrome in bit form. We consider all values to be 16-bits in this method (so a value like 5 is a palindrome normally, 101, but in 16-bits it's not). This method uses the get(x, n) method created in part 1. The input is done in the command line, and the user should input the number they want to check. The output outputs either "Is-Palindrome" or "Not-Palindrome". 
2. PA4: For this project, I was tasked with writing a circuit simulator that takes in a file input of different directives and outputs the result. Here are the directives:
        <p>- INPUTVAR: To input variables into the circuit, users will use INPUTVAR which takes a number, representing the number of variables to input, and then the names of the variables after that number. The names of the variable have to start with at least one character (A-Z) and is followed by characters (A-Z) or digits (0-9).
						<p><i>Example: INPUTVAR 3 IN1 IN2 IN3</i>
        <p>- OUTPUTVAR: The outputs that are produced in the circuit is made from OUTPUTVAR and has similar conventions as INPUTVAR.
						<p><i>Example: OUTPUTVAR 1 OUT1</i>
   <p> The circuit will use NOT, AND, OR, NAND, NOR, and XOR as building blocks. Here is a list of examples:
            <p>- NOT: NOT IN1 OUT1
            <p>- AND: AND IN1 IN2 OUT1
            <p>- OR: OR IN1 IN2 OUT1
            <p>- NAND: NAND IN1 IN2 OUT1
            <p>- NOR: NOR IN1 IN2 OUT1
            <p>- XOR: XOR IN1 IN2 OUT1
