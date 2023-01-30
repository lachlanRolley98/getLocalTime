COMP1511 18s1 (webcms)
Assignment 1 - Time To Code
COMP1511 18s1 (flask)
spec version: 1.2.1 | last updated: 2018-03-28 12:00:00 +1100

Summary
Your task for the first assignment is to write a program that will work out what the local time is in your town so when phoning home you don't call too early or too late and wake your family.

To do this, you will write a function to calculate the local time in a given town (in Australia or New Zealand), given the current time in UTC.

You will also be required to write a series of tests for this function.

Requirements
The main task in this assignment to write a function, get_local_time, which, given as input a town in Australia or New Zealand and a date and time in UTC, returns the local time in that town.

The town will be one of these 14 towns: Adelaide, Brisbane, Broken Hill, Canberra, Darwin, Eucla, Hobart, Lord Howe Island, Melbourne, Perth, Sydney, Auckland, Christchurch, Wellington.

The date will be in 2018.

You are also required to write a function, run_unit_tests, which tests get_local_time on valid and invalid inputs.

Note: it is a requirement that you create your own additional functions for this assignment. See the "Clarifications/Assumptions/Restrictions" section below for details.

The assignment is due on Tuesday 10 April 23:59:59.

Background
As local time varies between regions, computers typically maintain time in UTC. This, for example, allows time to be used across the internet without ambiguity. However, times in UTC must be converted to local time to be convenient for humans.

Your task is to write a function to do this conversion.

For example, your function might be asked to convert the UTC time of Saturday March 24 06:30 2018 to the local time in Sydney.

In March 2018, Sydney uses Australian Eastern Daylight Time which is UTC+11, so your function should return 1730.

Note that your function only returns the corresponding local time. The local date could be different to the UTC date. Your function does need not to return the local date.

You will need to research time in Australia and New Zealand, including how time zones and daylight savings work. This is an important and useful part of this assignment. Exploring and clarifying the specification of a problem is a normal part of a coding task. Also, any good programmer needs a precise understanding of time.

Planning
Start by thinking about the problem, and making sure you understand it well. Do examples on pen and paper. Draw diagrams. Don't be in a rush to start typing.

If there are things you don't understand, you can ask questions on the course forum.

The C features needed for this assignment are deliberately simple - essentially: ints, arithmetic, if statements and functions. You are not permitted to use C features such as loops and arrays. These wouldn't be particularly helpful and we want you to focus on analysing the problem, designing a solution and testing your solution.

You should allow at least two weeks to get it all working perfectly. Start at once and set some time aside to work on it regularly. You will not solve it well in one long intense session. Instead, plan regular periods. It will take much more time to do it than you expect if it is your first coding assignment. There is a lot to learn about tackling a problem like this.

Representation
We represent all values in this assignment as integers.

The 14 towns will be represented by the integers 0..13. You are given #defines for these values which you must use.

Months will be represented by the integers 1..12.

Days will be represented by the integers 1..31.

Times will be represented as hours * 100 + minutes. For example, 6:45am will be represented by the integer 645 and 7:20pm will be represented by the integer 1920. 12:00am (midnight) will be represented by the integer 0.

Hence times will be represented by integers in the range 0..2359 but not all integers in the range 0..2359 are valid times, for example, 1567 is not a valid time.

The seconds value in the time is always assumed to be zero in this assignment. The year in UTC dates is always assumed to be 2018.

Initial Code
Here is the code to start the assignment.

Read this file carefully. You must use this file to start the assignment.

Add your code to this file in the indicated places.

Do not change other parts of the file.

Implementing get_local_time
get_local_time is the most important function in the assignment.
get_local_time is given as 4 parameters: a town and a UTC month, day and time. All use the representations described above.

If any of get_local_time parameters are invalid it should return the constant INVALID_INPUT which is #defined in time2code.c Otherwise get_local_time should return the local time in the town, using the representation described above.

You are given this code for get_local_time.

int get_local_time(int town, int utc_month, int utc_day, int utc_time) {
    // CHANGE THIS FUNCTION
    // YOU ARE NOT PERMITTED TO USE ARRAYS, LOOPS, PRINTF OR SCANF
    // SEE THE ASSIGNMENT SPECIFICATION FOR MORE RESTRICTIONS
    return utc_time + TIMEZONE_AEDT_OFFSET;
}
Add your code to this function. You will have to change the return statement. The return is included only so the function compiles. It only returns the correct value in a few cases.
You should define your own functions and call them from get_local_time.

Implementing run_unit_tests
You are given this code for run_unit_tests.

void run_unit_tests(void) {
    // 2 example unit tests

    // UTC midnight on 20th March -> time in Sydney: 11am AEDT
    assert(get_local_time(TOWN_SYDNEY, 3, 20, 0) == 1100);

    // 42 is not a valid month
    assert(get_local_time(TOWN_SYDNEY, 42, 0, 0) == INVALID_INPUT);

    // ADD YOUR ASSERT STATEMENTS HERE

    // you should add at least 40 more assert statements to this function
    // with a comment for each test explaining it

    // there should be comment before this function
    // explaining your overall testing strategy
}
run_unit_tests includes two unit tests. Add your own unit tests for inputs to run_unit_tests. Implement them in exactly the same way as the example unit tests using assert statements.

Do not take the inputs autotest uses and add them to run_unit_tests - invent your own tests.

Autotest
A major part of the assignment is developing your own testing.

Autotest is also available and runs a few tests to ensure you have understood the structure of the assignment.

1511 autotest time2code
Autotest will only test a small part of your code. You will have to do most of the testing.

Clarifications/Assumptions/Restrictions
Clarifications
8am is often written as "0800". Don't worry about the leading zero. In this assignment, we represent 8am as the integer 800.

You cannot assume that the input to get_local_time will be valid.

You can assume the UTC date is in 2018.

Requirements
Using #defines
You must use the provided #defines in time2code.c such as TOWN_ADELAIDE and TIMEZONE_ACDT_OFFSET.


// You must use the provided #defines.

// This is valid:
if (town == TOWN_ADELAIDE)

// This is INVALID:
if (town == 0)
You may add your own #defines (and we encourage you to do so).

You must not treat the town #defines as numbers.

This means you cannot check whether something is less than or greater than a town #define.

You can only check that something is equal to the town #defines.


// You must not treat the #defines as numbers.

// This is INVALID
if (town < TOWN_AUCKLAND)

// This is valid:
if (town == TOWN_AUCKLAND)

// For example, this is NOT a valid way to check if a town is in New Zealand:

// This is INVALID:
if (town > 11 && town <= 13)

// This is INVALID:
if (town > TOWN_AUCKLAND && town <= TOWN_WELLINGTON)
Note that it is fine to check that the town you've been given is within the overall valid range of towns:


// This is valid
#define N_TOWNS 14
if (town < 0 || town >= N_TOWNS)
Additional Functions
Note: it is a requirement that you create your own additional functions for this assignment.

You must make a "non-token" effort at splitting your solution up sensibly into functions that improve the code's readability; simply creating a second function and shifting a large chunk of your code into it wouldn't satisfy this requirement.

If you have any concerns about what this means or whether your code meets this requirement, you can talk to your tutor who will be happy to give you advice and feedback.

Invalid Input
Your get_local_time function must check that its parameters are valid and return INVALID_INPUT if they are not. Your function will be tested on invalid inputs. For example, it might be tested by being given February 31 as the month and day.

You are required to use assert in run_unit_tests and are permitted to use it elsewhere.

Restrictions
You should use only int variables in this assignment.

You are not permitted to use arrays in this assignment. You are also not permitted to use structs or unions in this assignment.

You are not permitted to use loops. You are not permitted to use while, for, do or goto statements in this assignment.

You are not permitted to use switch statements in this assignment.

The functions you write are not permitted to call functions from the standard C library or any other library.

The functions you write must only call other functions you write.

Your functions must not call scanf.

Your functions must not call printf.

One exception: during debugging you may need to add calls to printf to your functions. Make sure you remove these calls to printf before your final submission. Your code will fail all automarking tests if calls to printf are left in your functions.

Note, the main function you have been given calls printf and scanf to help you in debugging your functions. Do not change this main function.

Changelog
v1.1
(2018-03-24 18:25:55 +1100)
added explicit requirement for using functionsadded clarification about daylight savingsadded clarification about using the provided #defines correctlyrestructured clarifications/assumptions/restrictions section into multiple sections
v1.1.1
(2018-03-24 19:40:18 +1100)
further clarification about using provided #defines
v1.2
(2018-03-26 17:56:10 +1100)
further clarification about using the provided #definesadded more examples of valid / invalid uses of the provided #defines
v1.2.1
(2018-03-28 12:00:00 +1100)
further clarification about using the provided #definesadded more examples of valid / invalid uses of the provided #defines
Attribution of Work
This is an individual assignment. The work you submit must be your own work and only your work apart from these exceptions. Joint work is not permitted.
You are not permitted to request help with the assignment apart from in the course forum, help sessions or from course lecturers or tutors.

Do not provide or show your assignment work to any other person (including by posting it on the forum) apart from the teaching staff of COMP1511.

The work you submit must otherwise be entirely your own work. Submission of work partially or completely derived from any other person or jointly written with any other person is not permitted. The penalties for such an offence may include negative marks, automatic failure of the course and possibly other academic discipline. Assignment submissions will be examined both automatically and manually for such submissions.

Relevant scholarship authorities will be informed if students holding scholarships are involved in an incident of plagiarism or other misconduct. If you knowingly provide or show your assignment work to another person for any reason, and work derived from it is submitted you may be penalized, even if the work was submitted without your knowledge or consent. This may apply even if your work is submitted by a third party unknown to you.

Note, you will not be penalized if your work is taken without your consent or knowledge.

Submission of Work
You are required to submit intermediate versions of your assignment.
Every time you work on the assignment and make some progress you should copy your work to your CSE account and submit it using the give command below.

It is fine if intermediate versions do not compile or otherwise fail submission tests.

Only the final submitted version of your assignment will be marked.

All these intermediate versions of your work will be placed in a git repo and made available to you via a web interface at this URL, replace z5555555 with your zpass. https://gitlab.cse.unsw.edu.au/z5555555/18s1-comp1511-ass1/commits/master

This will allow you to retrieve earlier versions of your code if needed.

You submit your work like this:

give cs1511 ass1 time2code.c
Assessment
This assignment will contribute 6% to your final mark.

75% of the marks for this assignment will be based on correctness of your get_local_time function. This will be assessed by automated testing on inputs that you will not be shown before the assignment is due. You will need to write your own extensive set of unit tests, so that you can catch any bugs in your program before you submit it.

15% of the marks for assignment 1 will come from hand marking of the readability of the C you have written. These marks will be awarded on the basis of clarity, commenting, elegance and style. In other words, your tutor will assess how easy it is for a human to read and understand your program.

10% of the marks for assignment 1 will come from hand marking of the unit tests you add to run_unit_tests. Here is an indicative marking scheme.

100%	works on all inputs, comprehensive well-explained unit tests, beautiful code
75%	works on most inputs, many unit tests added, code is readable
55%	works on some inputs, some unit tests added, code is sort of readable
-70%	Knowingly providing your work to anyone and it is subsequently submitted (by anyone).
-70%	Submitting any other person's work. This includes joint work.
0 FL for COMP1511	Paying another person to complete work. Submitting another person's work without their consent.
The lecturer may vary the assessment scheme after inspecting the assignment submissions but it will remain broadly similar to the description above.

Due Date
This assignment is tentatively due Tuesday 10 April 23:59:59
If your assignment is submitted after this date, each hour it is late reduces the maximum mark it can achieve by 2%. For example if an assignment worth 74% was submitted 10 hours late, the late submission would have no effect. If the same assignment was submitted 15 hours late it would be awarded 70%, the maximum mark it can achieve at that time.

COMP1511 18s1: Programming Fundamentals is brought to you by
the School of Computer Science and Engineering at the University of New South Wales, Sydney.
For all enquiries, please email the class account at cs1511@cse.unsw.edu.au
CRICOS Provider 00098G
